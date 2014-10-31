#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>
extern "C" {
#   include <x264.h>
}
#include "itrbase.h"

namespace itrx264
{
    class ix264
    {
        private:
            int64_t curr();
            int64_t  next_pts ();

            S32  encode_nals (x264_nal_t *nals, S32 nal_cnt);
            void  dumpnal (x264_nal_t *nal);
            void  dumpnals (S32 type, x264_nal_t *nal, S32 nals);
            void  _save_pic (void *start, S32 len);
            struct Ctx
            {
                x264_t *x264;
                x264_picture_t picture;
                x264_param_t param;
                void *output;       // 用于保存编码后的完整帧
                S32 output_bufsize, output_datasize;
                int64_t pts;        // 输入 pts

                int64_t info_pts, info_dts;
                S32 info_key_frame;
                S32 info_valid;

                S32 force_keyframe;
            };
            Ctx  _ctx;

            S32 _Isfirst;
        public:
            ix264();
            ~ix264();

            // typedef Ctx Ctx;


            /** FIXME: vc_open 将需要增加很多入口参数, 用于设置编码属性 */
            void Open (S32 width, S32 height, F32 fps);
            //S32 vc_close (void *ctx);
            S32 Close ();
            /** 每当 返回 > 0, 说明得到一帧数据, 此时可以调用 vc_get_last_frame_info() 获取更多信息 */
//      S32 vc_compress (void *ctx, unsigned char *data[4], S32 stride[4], const void **buf, S32 *len);
//      S32 vc_get_last_frame_info (void *ctx, S32 *key_frame, int64_t *pts, int64_t *dts);
            S32 Compress ( unsigned char *data[4], S32 stride[4], const void **buf, S32 *len);
            S32 vc_get_last_frame_info ( S32 *key_frame, int64_t *pts, int64_t *dts);
            /** 强制尽快输出关键帧 */
            //S32 vc_force_keyframe (void *ctx);
            S32 vc_force_keyframe ();


    };
}
