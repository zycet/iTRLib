#include"ix264.h"

namespace itrx264
{
// return currsec * 90000
ix264::ix264()
{
}
ix264::~ix264()
{
}
int64_t ix264::curr()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	F32 n = tv.tv_sec + 0.000001*tv.tv_usec;
	n *= 90000.0;
	return (int64_t)n;
}

int64_t  ix264::next_pts()
{
	if(_Isfirst==0)
	{
		this->_ctx.pts = curr();
		_Isfirst=1;
		return 0;
	}
	else
	{
		int64_t now = curr();
		return now - this->_ctx.pts;
	}

}


void  ix264::vc_open (S32 width, S32 height, F32 fps)
{
//	Ctx *ctx = new Ctx;

	this->_ctx.force_keyframe = 0;

	// 设置编码属性
	//x264_param_default(&this->_ctx.param);
	x264_param_default_preset(&this->_ctx.param, "fast", "zerolatency");
	//x264_param_apply_profile(&this->_ctx.param, "baseline");

	this->_ctx.param.i_width = width;
	this->_ctx.param.i_height = height;
	this->_ctx.param.b_repeat_headers = 1;  // 重复SPS/PPS 放到关键帧前面
	this->_ctx.param.b_cabac = 1;
     	this->_ctx.param.i_threads = 1;

	// this->_ctx.param.b_intra_refresh = 1;

	this->_ctx.param.i_fps_num = (S32)fps;
	this->_ctx.param.i_fps_den = 1;
	//this->_ctx.param.b_vfr_input = 1;

	this->_ctx.param.i_keyint_max = this->_ctx.param.i_fps_num * 2;
	//this->_ctx.param.i_keyint_min = 1;

	// rc
	// this->_ctx.param.rc.i_rc_method = X264_RC_CRF;
	this->_ctx.param.rc.i_bitrate = 50;
	//this->_ctx.param.rc.f_rate_tolerance = 0.1;
	//this->_ctx.param.rc.i_vbv_max_bitrate = this->_ctx.param.rc.i_bitrate * 1.3;
	//this->_ctx.param.rc.f_rf_constant = 600;
	//this->_ctx.param.rc.f_rf_constant_max = this->_ctx.param.rc.f_rf_constant * 1.3;

#ifdef DEBUG
	this->_ctx.param.i_log_level = X264_LOG_WARNING;
#else
	this->_ctx.param.i_log_level = X264_LOG_NONE;
#endif // release

	this->_ctx.x264 = x264_encoder_open(&this->_ctx.param);
	if (!this->_ctx.x264) {
		fprintf(stderr, "%s: x264_encoder_open err\n", __func__);
	//	delete this->_ctx;
		//return 0;
	}

	x264_picture_init(&this->_ctx.picture);
	this->_ctx.picture.img.i_csp = X264_CSP_I420;
	this->_ctx.picture.img.i_plane = 3;

	this->_ctx.output = malloc(128*1024);
	this->_ctx.output_bufsize = 128*1024;
	this->_ctx.output_datasize = 0;

	//this->_ctx.get_pts = first_pts;
	this->_ctx.info_valid = 0;
    _Isfirst=0;
//	return this->_ctx;
}

S32 ix264::vc_close ()
{
	x264_encoder_close(this->_ctx.x264);
	free(this->_ctx.output);
	//delete this->_ctx;
	return 1;
}

S32 ix264::vc_get_last_frame_info (S32*key_frame, int64_t *pts, int64_t *dts)
{
	if (this->_ctx.info_valid) {
		*key_frame = this->_ctx.info_key_frame;
		*pts = this->_ctx.info_pts;
		*dts = this->_ctx.info_dts;
		return 1;
	}
	else {
		return -1;
	}
}

S32 ix264::encode_nals (x264_nal_t *nals, S32 nal_cnt)
{
	char *pout = (char*)this->_ctx.output;
	this->_ctx.output_datasize = 0;
	for (S32 i = 0; i < nal_cnt; i++) {
		if (this->_ctx.output_datasize + nals[i].i_payload > this->_ctx.output_bufsize) {
			// 扩展
			this->_ctx.output_bufsize = (this->_ctx.output_datasize+nals[i].i_payload+4095)/4096*4096;
			this->_ctx.output = realloc(this->_ctx.output, this->_ctx.output_bufsize);
		}
		memcpy(pout+this->_ctx.output_datasize, nals[i].p_payload, nals[i].i_payload);
		this->_ctx.output_datasize += nals[i].i_payload;
	}

	return this->_ctx.output_datasize;
}

void  ix264::dumpnal (x264_nal_t *nal)
{
	// 打印前面 10 个字节
	for (S32 i = 0; i < nal->i_payload && i < 20; i++) {
		fprintf(stderr, "%02x ", (unsigned char)nal->p_payload[i]);
	}
}

void  ix264::dumpnals (S32 type, x264_nal_t *nal, S32 nals)
{
	fprintf(stderr, "======= dump nals %d type=%d, ======\n", nals, type);
	for (S32 i = 0; i < nals; i++) {
		fprintf(stderr, "\t nal  #%d: %dbytes, nal type=%d ", i, nal[i].i_payload, nal[i].i_type);
		dumpnal(&nal[i]);
		fprintf(stderr, "\n");
	}
}

void  ix264::_save_pic (void *start, S32 len)
{
	static S32 num=0;
	char file[20];
	sprintf(file,"pic/data%d.pic",num++);
	FILE *fp = fopen(file, "wb");
	fwrite(start, 1, len, fp);
	fclose(fp);
}

S32 ix264::vc_compress (unsigned char *data[4], S32 stride[4], const void **out, S32*len)
{
	// _save_pic(data[0],480000+240000);
	// 设置 picture 数据
	for (S32 i = 0; i < 4; i++) {
		this->_ctx.picture.img.plane[i] = data[i];
		this->_ctx.picture.img.i_stride[i] = stride[i];
	}

	// encode
	x264_nal_t *nals;
	S32 nal_cnt;
	x264_picture_t pic_out;

	//this->_ctx.picture.i_pts = this->_ctx.get_pts();
	this->_ctx.picture.i_pts = next_pts();
	x264_picture_t *pic = &this->_ctx.picture;

	if (this->_ctx.force_keyframe) {
		this->_ctx.picture.i_type = X264_TYPE_IDR;
		this->_ctx.force_keyframe = 0;
	}
	else {
		this->_ctx.picture.i_type = X264_TYPE_AUTO;
	}

	do {
		// 这里努力消耗掉 delayed frames ???
		// 实际使用 zerolatency preset 时, 效果足够好了
		S32 rc = x264_encoder_encode(this->_ctx.x264, &nals, &nal_cnt, pic, &pic_out);
		if (rc < 0) return -1;
		if (pic_out.b_keyframe) {
			dumpnals(pic_out.i_type, nals, nal_cnt);
		}
		encode_nals( nals, nal_cnt);
	} while (0);

	*out = this->_ctx.output;
	*len = this->_ctx.output_datasize;

	if (nal_cnt > 0) {
		this->_ctx.info_valid = 1;
		this->_ctx.info_key_frame = pic_out.b_keyframe;
		this->_ctx.info_pts = pic_out.i_pts;
		this->_ctx.info_dts = pic_out.i_dts;
	}
	else {
		fprintf(stderr, ".");
		return 0; // 继续
	}

#ifdef DEBUG_MORE
	static S32 _last_pts = this->_ctx.info_pts;

	fprintf(stderr, "DBG: pts delta = %lld\n", this->_ctx.info_pts - _last_pts);
	_last_pts = this->_ctx.info_pts;
#endif //


#ifdef DEBUG_MORE
	static size_t _seq = 0;

	fprintf(stderr, "#%lu: [%c] frame type=%d, size=%d\n", _seq,
			pic_out.b_keyframe ? '*' : '.',
			pic_out.i_type, this->_ctx.output_datasize);

	_seq++;
#endif // debug

	return 1;
}

S32 ix264::vc_force_keyframe ()
{
	this->_ctx.force_keyframe = 1;
	return 1;
}
}
