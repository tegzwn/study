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

#define WIDTH 256   //ͼ����
#define HEIGHT 256  //ͼ��߶�
#define CLRUSED 256   // ��ɫ����ɫ����256ɫ�����8λ�Ҷ�ͼ

void read_bmpHeader(char *filename, unsigned char bmFileHeader[], unsigned char bmInfoHeader[], unsigned char bmClrMap[]);



/**************************************************
*
*   ���½ṹ�嶨��BMPͼ��λͼ���ļ��Ľṹ������3
*   ���֣�λͼ�ļ�ͷ��λͼ��Ϣͷ����ɫ�壻ͼ������
*   δ�������ò���������Ϊ��BMPͼ��ṹ���˽⡣
***************************************************/

//�ṹ�壬λͼ�ļ�ͷ������Ϊ14�ֽڡ�unsigned short-2 Bytes (WORD), unsigned long-4 Bytes (DWORD)
struct bmpfileheader{
   unsigned short  filetype;  //ָ���ļ�����,������ Ox424D�����ַ���"BM"�����С�.bmp���ļ���ͷ�����ֽڶ��ǡ�BM������
   unsigned long   filesize;  //ָ���ļ���С������λͼ�ļ�ͷ��14���ֽڡ�
   short  reserved1;
   short  reserved2;
   unsigned long   bitmapoffset;  //���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ�������λͼ�ļ�ͷ��λͼ��Ϣͷ�͵�ɫ���������ֵĳ���֮�͡�
};


//�ṹ�壬λͼ��Ϣͷ������Ϊ40�ֽڡ�
struct bitmapheader{
   unsigned long   size;  //ָ���ýṹ��ĳ��ȣ���40�ֽڡ�
   long   width;   //ָ��ͼ��Ŀ�ȣ���λ�����ء�
   long   height;  //ָ��ͼ��ĸ߶ȣ���λ�����ء�
   unsigned short  planes;  //������1��
   unsigned short  bitsperpixel; //ָ����ʾ��ɫʱҪ�õ���λ��������ֵΪ1���ڰ׶�ɫͼ����4��16ɫͼ����8��256ɫͼ����24�����ɫͼ�������Ĳ���8��
   unsigned long   compression;
   unsigned long   sizeofbitmap;  //ָ��ʵ�ʵ�λͼ����ռ�õ��ֽ�����sizeofbitmap=width'*height��
   unsigned long   horzres;
   unsigned long   vertres;
   unsigned long   colorsused;  //ָ����ͼ��ʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2��bitsperpixel���ݡ�
   unsigned long   colorsimp;
};


//�ṹ�壬��ɫ�壨���ɫͼ����Ҫ��ɫ�壩������Ϊ4�ֽڡ�
struct ctstruct{
   unsigned char blue;   //����ɫ����ɫ������
   unsigned char green;  //����ɫ����ɫ������
   unsigned char red;    //����ɫ�ĺ�ɫ������
   unsigned char rgbReserved; //����ֵ��
};
