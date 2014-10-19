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
    * \brief Set Picture format
    * \param typ : 0  RGB42, not 0YUV420
    */
    void v4linux::Init(S32 typ)
    {
        if(typ==0)
        _type=RGB;
        else
        _type=YUV;
    }

    void v4linux::xioctl(int fh, int request, void *arg)
    {
        int r;

        do {
                r = v4l2_ioctl(fh, request, arg);
        } while (r == -1 && ((errno == EINTR) || (errno == EAGAIN)));

        if (r == -1) {
                fprintf(stderr, "error %d, %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
        }
    }
    void v4linux::SetTunnel(S32 index)
    {
        xioctl(fd,VIDIOC_S_INPUT,&index);
    }
    /**
    * \brief 打开摄像头
    * \param Width 图像宽度
    * \param Height 图像高度
    * \param BufferNum 缓冲区数量(如果>0则表示使用异步采集模式,否则为同步模式)
    */
    int v4linux::Open(U32 ID,S32 Width,S32 Height,S32 Buffer_Num)
    {
       _width=Width;
        _height=Height;
        _buffernum=2;

        char dev_name[20];
        sprintf(dev_name,"/dev/video%d",ID);

        fd = v4l2_open(dev_name, O_RDWR | O_NONBLOCK, 0);
        if (fd < 0)
        {
            perror("Cannot open device");
            exit(EXIT_FAILURE);
        }

        CLEAR(fmt);
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width       = _width;
        fmt.fmt.pix.height      = _height;
        if(_type==RGB)
            fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
        else
            if (_type==YUV)
            fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
            else
            {
                printf("picture type error! \n");
                exit(-1);
            }

        fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
        xioctl(fd, VIDIOC_S_FMT, &fmt);
        // if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_RGB24) {
        //         printf("Libv4l didn't accept RGB24 format. Can't proceed.\n");
        //         exit(EXIT_FAILURE);
        // }
        if ((fmt.fmt.pix.width != _width) || (fmt.fmt.pix.height != _height))
                printf("Warning: driver is sending image at %dx%d\n",
                        fmt.fmt.pix.width, fmt.fmt.pix.height);

        CLEAR(req);
        req.count =_buffernum;
        req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        req.memory = V4L2_MEMORY_MMAP;
        xioctl(fd, VIDIOC_REQBUFS, &req);

        buffers = (buffer*)calloc(req.count, sizeof(*buffers));
        for (S32 n_buffers = 0; n_buffers < req.count; ++n_buffers) {
                CLEAR(buf);
                buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory      = V4L2_MEMORY_MMAP;
                buf.index       = n_buffers;

                xioctl(fd, VIDIOC_QUERYBUF, &buf);

                buffers[n_buffers].length = buf.length;
                buffers[n_buffers].start = v4l2_mmap(NULL, buf.length,
                              PROT_READ | PROT_WRITE, MAP_SHARED,
                              fd, buf.m.offset);

                if (MAP_FAILED == buffers[n_buffers].start) {
                        perror("mmap");
                        exit(EXIT_FAILURE);
                }
        }

        for ( S32 i = 0; i <  req.count; ++i) {
                CLEAR(buf);
                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_MMAP;
                buf.index = i;
                xioctl(fd, VIDIOC_QBUF, &buf);
        }
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

        xioctl(fd, VIDIOC_STREAMON, &type);
    }


    /**
    * \brief 关闭摄像头
    */
    void v4linux::Close()
    {
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        xioctl(fd, VIDIOC_STREAMOFF, &type);
        for (S32 i = 0; i < _buffernum; ++i)
        v4l2_munmap(buffers[i].start, buffers[i].length);
        v4l2_close(fd);
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


    S32 v4linux::FetchFrame(U8 *Raw,S32 Length,void *ExInfo)
    {
            do {
                    FD_ZERO(&fds);
                    FD_SET(fd, &fds);

                    /* Timeout. */
                    tv.tv_sec = 2;
                    tv.tv_usec = 0;

                    r = select(fd + 1, &fds, NULL, NULL, &tv);
            } while ((r == -1 && (errno = EINTR)));
            if (r == -1) {
                    perror("select");
                    return errno;
            }

            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            xioctl(fd, VIDIOC_DQBUF, &buf);

            memcpy(Raw,buffers[buf.index].start,Length);

            xioctl(fd, VIDIOC_QBUF, &buf);
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
        {
            _callback=Callback;
        }
    }

    void v4linux::PushBufferBack(U8 *Raw)
    {

    }
}
