#include "v4linux.h"

namespace itr_device
{
v4linux::v4linux()
{
    //ctor
//     _AqPara.AquaireFreq=100000;
}


v4linux::~v4linux()
{
//    //dtor

}

/**
* \brief 打开摄像头
* \param Width 图像宽度
* \param Height 图像高度
* \param BufferNum 缓冲区数量(如果>0则表示使用异步采集模式,否则为同步模式)
*/
void v4linux::Open(U32 ID,S32 Width,S32 Height,S32 Buffer_Num)
{
    _width=Width;
    _height=Height;
    _buffernum=2;

    char dev_name[20];
    sprintf(dev_name,"%s%d",_dev,ID);

    id = open(dev_name, O_RDWR);

    if (id < 0)
    {
        exit(0);
    }

    Ctx *ctx = new Ctx;
    ctx->vid = id;
    // to query caps
    v4l2_capability caps;
    ioctl(id, VIDIOC_QUERYCAP, &caps);

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
            bufs.count = _buffernum;
            bufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            bufs.memory = V4L2_MEMORY_MMAP;
            if (ioctl(id, VIDIOC_REQBUFS, &bufs) < 0)
            {

                close(id);
                delete ctx;

            }


            // mmap
            for (int i = 0; i < 2; i++)
            {
                v4l2_buffer buf;
                memset(&buf, 0, sizeof(buf));
                buf.type = bufs.type;
                buf.memory = bufs.memory;
                if (ioctl(id, VIDIOC_QUERYBUF, &buf) < 0)
                {
                    close(id);
                    delete ctx;
                    exit(0);
                }

                ctx->bufs[i].length = buf.length;
                ctx->bufs[i].start = mmap(0, buf.length, PROT_READ|PROT_WRITE,
                                          MAP_SHARED, id, buf.m.offset);
            }
        }
        else
        {
            close(id);
            delete ctx;
            exit(0);
        }
    }
    else
    {

        close(id);
        delete ctx;
        exit(0);
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
    }
    while (rc >= 0);
#endif // 0
    v4l2_format fmt;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    rc = ioctl(id, VIDIOC_G_FMT, &fmt);
    if (rc < 0)
    {
        exit(0);
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

        exit(0);
    }

    // 构造转换器

    ctx->width = _width;
    ctx->height = _height;
    ctx->sws = sws_getContext(fmt.fmt.pix.width, fmt.fmt.pix.height, pixfmt,
                              ctx->width, ctx->height, PIX_FMT_YUV420P, 	// PIX_FMT_YUV420P 对应 X264_CSP_I420
                              SWS_FAST_BILINEAR, 0, 0, 0);

    ctx->rows = fmt.fmt.pix.height;
    ctx->bytesperrow = fmt.fmt.pix.bytesperline;

    avpicture_alloc(&ctx->pic_target, PIX_FMT_YUV420P, ctx->width, ctx->height);

    // queue buf
    for (int i = 0; i < _buffernum; i++)
    {
        v4l2_buffer buf;
        memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (ioctl(id, VIDIOC_QBUF, &buf) < 0)
        {
            exit(-1);
        }
    }

    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(id, VIDIOC_STREAMON, &type) < 0)
    {
        exit(-1);
    }

    ctx->fmt = PIX_FMT_YUV420P;
    id_ctx=ctx;


}

/**
* \brief 关闭摄像头
*/
void v4linux::Close()
{

    Ctx *ctx = (Ctx*)id_ctx;
    for (int i = 0; i <_buffernum; i++)
    {
        munmap(ctx->bufs[i].start, ctx->bufs[i].length);
    }
    avpicture_free(&ctx->pic_target);
    sws_freeContext(ctx->sws);
    delete ctx;
}


S32 v4linux::GetWidth()
{
    return (_width);
}


S32 v4linux::GetHeight()
{
    return (_height);
}

v4linux::AquairePara v4linux::GetPara()
{
    return  (_AqPara);
}

void v4linux::SetPara(AquairePara Para)
{
    _AqPara.AquaireFreq=Para.AquaireFreq;
    _AqPara.Exposure=Para.Exposure;
    _AqPara.Format=Para.Format;
    _AqPara.Gain=Para.Gain;

}


S32 v4linux::FetchFrame(U8* Raw,S32 Length,void* ExInfo)
{
    Ctx *ctx = (Ctx*)id_ctx;
    v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (ioctl(ctx->vid, VIDIOC_DQBUF, &buf) < 0) {
		fprintf(stderr, "%s: VIDIOC_DQBUF err\n", __func__);
		return -1;
	}
    ctx->pic_src.data[0] = (unsigned char*)ctx->bufs[buf.index].start;
    ctx->pic_src.data[1] = ctx->pic_src.data[2] = ctx->pic_src.data[3] = 0;
    ctx->pic_src.linesize[0] = ctx->bytesperrow;
    ctx->pic_src.linesize[1] = ctx->pic_src.linesize[2] = ctx->pic_src.linesize[3] = 0;

    // sws_scale
    int rs = sws_scale( ctx->sws,
                        ctx->pic_src.data,
                        ctx->pic_src.linesize,
                        0,
                        ctx->rows,
                        ctx->pic_target.data,
                        ctx->pic_target.linesize
                      );

    // out
    for (int i = 0; i < 4; i++)
    {
        pic.data[i] = ctx->pic_target.data[i];
        pic.stride[i] = ctx->pic_target.linesize[i];
    }
    /// ///////////////// 输出图片。
	// re queue buf
	if (ioctl(ctx->vid, VIDIOC_QBUF, &buf) < 0) {
		fprintf(stderr, "%s: VIDIOC_QBUF err\n", __func__);
		return -1;
	}
    for(S32 i=0; i<Length; i++)
    {
        Raw[i]=(U8)(ctx->pic_target.data[0])[i];
    }

    return(0);

}



void v4linux::Start()
{

}

void v4linux::Stop()
{


}


void v4linux::RegCallBack(ReceiveFrameCallBack Callback)
{
    if(Callback!=NULL)
        _callback=Callback;
}


void v4linux::PushBufferBack(U8* Raw)
{

}
}
