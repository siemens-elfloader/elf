#ifndef IMAGE_H
#define IMAGE_H
void DrwImg(IMGHDR *img, int x, int y);
void FreeImg(IMGHDR *img);
void IMGHDR_cpy(IMGHDR *dest, IMGHDR *src);
IMGHDR *CreateIMGHDRFromPng(char *file);
#endif