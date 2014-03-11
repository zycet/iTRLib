#ifndef V4LINUX_H
#define V4LINUX_H
#include "itrbase.h"
#include "asicamera.h"
namespace itr_device
{
class v4linux:public ICamera
{
    public:
        struct Picture
        {
            unsigned char *data[4];
            int stride[4];
        };
        typedef struct Picture Picture;

        v4linux();
        virtual ~v4linux();

        void *capture_open(const char *dev_name, int v_width, int v_height, RawFormat fmt);
        int capture_get_picture (void *id, Picture *pic);
        int capture_close (void *id);

        int capture_get_output_ptr (void *id, unsigned char ***ptr, int **stride);
    protected:
    private:
};
}
#endif // V4LINUX_H
