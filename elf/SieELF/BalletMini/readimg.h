#ifndef _READ_IMG_H_
#define _READ_IMG_H_

IMGHDR *read_pngimg(const char *buf);

IMGHDR *read_jpgimg(const char *buf);

IMGHDR *ConvertRGBAToRGB8(const char *buf, int width, int height);

IMGHDR *CreateFrame(int width, int height, const char *color);

IMGHDR *CreateDelimiter(int width, int height, const char *color);

#endif /* _READ_IMG_H_ */
