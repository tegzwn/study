#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <dos.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <sys\types.h>
#include <sys\stat.h>

#define WIDTH 256   //图像宽度
#define HEIGHT 256  //图像高度
#define CLRUSED 256   // 调色板颜色数：256色，针对8位灰度图

void read_bmpHeader(char *filename, unsigned char bmFileHeader[], unsigned char bmInfoHeader[], unsigned char bmClrMap[]);



/**************************************************
*
*   以下结构体定义BMP图像（位图）文件的结构，包含3
*   部分：位图文件头、位图信息头、调色板；图像数据
*   未包含。该部分内容作为对BMP图像结构的了解。
***************************************************/

//结构体，位图文件头，长度为14字节。unsigned short-2 Bytes (WORD), unsigned long-4 Bytes (DWORD)
struct bmpfileheader{
   unsigned short  filetype;  //指定文件类型,必须是 Ox424D，即字符串"BM"（所有“.bmp”文件的头两字字节都是“BM”）。
   unsigned long   filesize;  //指定文件大小，包括位图文件头的14个字节。
   short  reserved1;
   short  reserved2;
   unsigned long   bitmapoffset;  //从文件头到实际位图数据的偏移字节数，即位图文件头、位图信息头和调色板三个部分的长度之和。
};


//结构体，位图信息头，长度为40字节。
struct bitmapheader{
   unsigned long   size;  //指定该结构体的长度，即40字节。
   long   width;   //指定图像的宽度，单位是像素。
   long   height;  //指定图像的高度，单位是像素。
   unsigned short  planes;  //必须是1。
   unsigned short  bitsperpixel; //指定表示颜色时要用到的位数，常用值为1（黑白二色图）、4（16色图）、8（256色图）、24（真彩色图）；本文采用8。
   unsigned long   compression;
   unsigned long   sizeofbitmap;  //指定实际的位图数据占用的字节数，sizeofbitmap=width'*height。
   unsigned long   horzres;
   unsigned long   vertres;
   unsigned long   colorsused;  //指定本图像实际用到的颜色数，如果该值为零，则用到的颜色数为2的bitsperpixel次幂。
   unsigned long   colorsimp;
};


//结构体，调色板（真彩色图不需要调色板），长度为4字节。
struct ctstruct{
   unsigned char blue;   //该颜色的蓝色分量。
   unsigned char green;  //该颜色的绿色分量。
   unsigned char red;    //该颜色的红色分量。
   unsigned char rgbReserved; //保留值。
};
