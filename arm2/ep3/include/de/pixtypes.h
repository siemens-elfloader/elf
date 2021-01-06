
#ifndef __PIXTYPES_H__
#define __PIXTYPES_H__

#include <inttypes.h>

typedef struct
{
    uint8_t r, g, b, a;
}Color;


typedef struct _color
{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color_t;


typedef uint32_t color32_t;
typedef uint16_t color16_t;
typedef uint8_t color8_t;

typedef struct
{
    unsigned short w, h;
    unsigned int bpnum;
    unsigned char *bitmap;
    unsigned char blend;
}image_t;


#endif
