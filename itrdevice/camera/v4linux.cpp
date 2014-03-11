#include "v4linux.h"

namespace itr_device
{
v4linux::v4linux()
{
    //ctor
     _AqPara.AquaireFreq=100000;
}


v4linux::~v4linux()
{
    //dtor
     delete[] p_base;
}

/**
* \brief 打开摄像头
* \param Width 图像宽度
* \param Height 图像高度
* \param BufferNum 缓冲区数量(如果>0则表示使用异步采集模式,否则为同步模式)
*/
void v4linux::Open(U32 ID,S32 Width,S32 Height,S32 BufferNum)
{
    _width=Width;
    _height=Height;
    _buffernum=BufferNum;

	id = open(dev_name, O_RDWR);
	if (id < 0)
    {
        exit(0);
    }
    if(id!=(S32)ID)
        exit(0);

	Ctx *ctx = new Ctx;
	ctx->vid = id;
	// to query caps
	v4l2_capability caps;
	ioctl(ID, VIDIOC_QUERYCAP, &caps);

	if (caps.capabilities & V4L2_CAP_VIDEO_CAPTURE)
	{
		if (caps.capabilities & V4L2_CAP_READWRITE)
		{
			// TODO: ...
		}
		if (caps.capabilities & V4L2_CAP_STREAMING)
		{
			// 检查是否支持 MMAP, 还是 USERPTR
			v4l2_requestbuffers bufs;
			memset(&bufs, 0, sizeof(bufs));
			bufs.count = BufferNum;
			bufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			bufs.memory = V4L2_MEMORY_MMAP;
			if (ioctl(id, VIDIOC_REQBUFS, &bufs) < 0)
			{
				fprintf(stderr, "%s: don't support MEMORY_MMAP mode!\n", __func__);
				close(id);
				delete ctx;

			}

			fprintf(stderr, "%s: using MEMORY_MMAP mode, buf cnt=%d\n", __func__, bufs.count);

			// mmap
			for (int i = 0; i < BufferNum; i++)
			{
				v4l2_buffer buf;
				memset(&buf, 0, sizeof(buf));
				buf.type = bufs.type;
				buf.memory = bufs.memory;
				if (ioctl(id, VIDIOC_QUERYBUF, &buf) < 0) {
					fprintf(stderr, "%s: VIDIOC_QUERYBUF ERR\n", __func__);
					close(id);
					delete ctx;
//					return 0;
				}

				ctx->bufs[i].length = buf.length;
				ctx->bufs[i].start = mmap(0, buf.length, PROT_READ|PROT_WRITE,
						MAP_SHARED, id, buf.m.offset);
			}
		}
		else
		{
			fprintf(stderr, "%s: can't support read()/write() mode and streaming mode\n", __func__);
			close(id);
			delete ctx;
//			return 0;
		}
	}
	else {
		fprintf(stderr, "%s: can't support video capture!\n", __func__);
		close(id);
		delete ctx;
//		return 0;
	}

	int rc;

	// enum all support image fmt
	v4l2_fmtdesc fmt_desc;
	uint32_t index = 0;

        // 看起来, 不支持 plane fmt, 直接使用 RGB 吧, 然后使用 libswscale 转换
#if 1
	do
	{
		fmt_desc.index = index;
		fmt_desc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		rc = ioctl(id, VIDIOC_ENUM_FMT, &fmt_desc);

		if (rc >= 0)
		{
			fprintf(stderr, "\t support %s\n", fmt_desc.description);
		}
		index++;
	} while (rc >= 0);
#endif // 0
	v4l2_format fmt;
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	rc = ioctl(id, VIDIOC_G_FMT, &fmt);
	if (rc < 0)
	{
		fprintf(stderr, "%s: can't VIDIOC_G_FMT...\n", __func__);
//		return 0;
	}

//RawFormat

	PixelFormat pixfmt = PIX_FMT_NONE;
//    RawFormat pixfmt = PIX_FMT_NONE;
	switch (fmt.fmt.pix.pixelformat)
	{
	case V4L2_PIX_FMT_YUYV:
		pixfmt = PIX_FMT_YUYV422;
		break;

	case V4L2_PIX_FMT_MJPEG:
		// pixfmt = PIX_FMT_YUVJ422P;
		// 使用 mjpeg 应该能够满足 640x480x25, 但是需要解码 mjpeg

		break;
	}

	if (pixfmt == PIX_FMT_NONE)
	{
		fprintf(stderr, "%s: can't support %4s\n", __func__, (char*)&fmt.fmt.pix.pixelformat);
//		return 0;
	}

	// 构造转换器
	fprintf(stderr, "capture_width=%d, height=%d, stride=%d\n", fmt.fmt.pix.width, fmt.fmt.pix.height,
			fmt.fmt.pix.bytesperline);
	ctx->width = _width;
	ctx->height = _height;
	ctx->sws = sws_getContext(fmt.fmt.pix.width, fmt.fmt.pix.height, pixfmt,
                        ctx->width, ctx->height, PIX_FMT_YUV420P, 	// PIX_FMT_YUV420P 对应 X264_CSP_I420
			SWS_FAST_BILINEAR, 0, 0, 0);

	ctx->rows = fmt.fmt.pix.height;
	ctx->bytesperrow = fmt.fmt.pix.bytesperline;

        avpicture_alloc(&ctx->pic_target, PIX_FMT_YUV420P, ctx->width, ctx->height);

	// queue buf
	for (int i = 0; i < BufferNum; i++)
	{
		v4l2_buffer buf;
		memset(&buf, 0, sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;

		if (ioctl(id, VIDIOC_QBUF, &buf) < 0)
		{
			fprintf(stderr, "%s: VIDIOC_QBUF err\n", __func__);
			exit(-1);
		}
	}

	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (ioctl(id, VIDIOC_STREAMON, &type) < 0)
	{
		fprintf(stderr, "%s: VIDIOC_STREAMON err\n", __func__);
		exit(-1);
	}

        ctx->fmt = PIX_FMT_YUV420P;

//	return ctx;
}

/**
* \brief 关闭摄像头
*/
void v4linux::Close()
{
//    closeCamera();
}

/**
* \brief 获得图像宽度
*/
S32 v4linux::GetWidth()
{
    return (_width);
}

/**
* \brief 获得图像高度
*/
S32 v4linux::GetHeight()
{
    return (_height);
}

/**
* \brief 获得采集参数
*/
v4linux::AquairePara v4linux::GetPara()
{
    return  (_AqPara);
}
/**
* \brief 设置采集参数
*/
void v4linux::SetPara(AquairePara Para)
{
    _AqPara.AquaireFreq=Para.AquaireFreq;
    _AqPara.Exposure=Para.Exposure;
    _AqPara.Format=Para.Format;
    _AqPara.Gain=Para.Gain;

//    setValue(CONTROL_GAIN,(int)_AqPara.Gain,false);
//    setValue(CONTROL_EXPOSURE, (int)_AqPara.Exposure, true); //auto exposure
//    setImageFormat(_width, _height, 1, IMG_RAW8);     //
   // setValue(CONTROL_GAMMA,2,false);
//    setValue(CONTROL_BRIGHTNESS,3,false);
//    setValue(CONTROL_BANDWIDTHOVERLOAD,4,false);
}

/**
* \brief 同步获取一帧图像
* \param Raw 输出图像用的缓冲区
* \param Length 输出图像用的缓冲区长度
* \param ExInfo 输出图像用附加信息的缓冲区
* \return 成功写入缓冲区的数据长度,无图像返回0,发生错误返回-1.
* \note 此函数用于同步模式下的图像获取,在Open函数调用时需使BufferNum=0.
*/
S32 v4linux::FetchFrame(U8* Raw,S32 Length,void* ExInfo)
{

    // 获取, 转换
    return(0);

}


/**
* \brief 异步捕获开始
* \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
*/
void v4linux::Start()
{
    Ctx *ctx = (Ctx*)id;
	v4l2_buffer buf;
	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;

	if (ioctl(ctx->vid, VIDIOC_DQBUF, &buf) < 0) {
		fprintf(stderr, "%s: VIDIOC_DQBUF err\n", __func__);
//		return -1;
	}

//	_save_pic(ctx->bufs[buf.index].start, buf.length);
//	__asm("int $3");
	ctx->pic_src.data[0] = (unsigned char*)ctx->bufs[buf.index].start;
	ctx->pic_src.data[1] = ctx->pic_src.data[2] = ctx->pic_src.data[3] = 0;
	ctx->pic_src.linesize[0] = ctx->bytesperrow;
	ctx->pic_src.linesize[1] = ctx->pic_src.linesize[2] = ctx->pic_src.linesize[3] = 0;

	// sws_scale
	int rs = sws_scale(ctx->sws, ctx->pic_src.data, ctx->pic_src.linesize,
			0, ctx->rows, ctx->pic_target.data, ctx->pic_target.linesize);

	// out
	for (int i = 0; i < 4; i++) {
		pic.data[i] = ctx->pic_target.data[i];
		pic.stride[i] = ctx->pic_target.linesize[i];
	}

	// re queue buf
	if (ioctl(ctx->vid, VIDIOC_QBUF, &buf) < 0) {
		fprintf(stderr, "%s: VIDIOC_QBUF err\n", __func__);
//		return -1;
	}

//	return 1;
}
/**
* \brief 异步捕获停止
* \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
*/
void v4linux::Stop()
{
    Ctx *ctx = (Ctx*)id;
	for (int i = 0; i <(int) sizeof(ctx->bufs)/sizeof(Buffer); i++) {
		munmap(ctx->bufs[i].start, ctx->bufs[i].length);
	}
	avpicture_free(&ctx->pic_target);
	sws_freeContext(ctx->sws);
	delete ctx;

//	return 1;
}

/**
* \brief 传入回调函数
* \param 当获得一张图片时调用的回调函数
*/
void v4linux::RegCallBack(ReceiveFrameCallBack Callback)
{
    if(Callback!=NULL)
        callback=Callback;
}

/**
* \brief 在图像处理完成后将缓冲区返回图像队列(如果无可用图像采集缓冲区会导致图像采集暂停)
* \param Raw 缓冲区地址
* \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
*/
void v4linux::PushBufferBack(U8* Raw)
{
//    for(S32 i=0; i<_buffernum; i++)
//    {
//        if(bufferlist[i]== Raw)
//        cycleQueue.Insert(Raw);
//    }
}
}
