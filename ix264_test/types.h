#ifndef _types__hh
#define _types__hh

// yuv
struct Picture
{
	unsigned char *data[4];
	int stride[4];
};
typedef struct Picture Picture;

#endif // types.h

