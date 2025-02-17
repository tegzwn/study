
#include "cips.h"

int main()
{
	FILE *fp;  // FILE类型，在stdio.h头文件中，FILE类是一个结构体，代表任何一个任何类型的文件，用于文件的读写操作。
	int i, j;
	unsigned char FileHeader[14];
	unsigned char InfoHeader[40];
	unsigned char rgbQuad[CLRUSED*4];
	unsigned char imArray[HEIGHT][WIDTH];

	char fileName_IN[]	= "lena_in.bmp";

	unsigned char temp;
	int dataOffset;  //从文件头到实际位图数据的偏移字节数=位图文件头长度+位图信息头长度+调色板长度

	read_bmpHeader(fileName_IN, FileHeader, InfoHeader, rgbQuad);

	//读图像数据
	dataOffset = 14 + 40 + CLRUSED*4;

	if ((fp = fopen(fileName_IN, "rb")) == NULL)
    {
        printf("Failure to open file! \n");
        exit(0);
	}

	fseek(fp, dataOffset, SEEK_SET);  //跳过图像文件头部分，开始读图像数据

	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			fread(&temp, 1, 1, fp);
			imArray[i][j] = temp;
		}
	}

	fclose(fp);

	/*输出显示BMP图像的文件头、信息头和调色板三部分信息*/
	//输出文件头，14字节
	printf("\n  BMP File Header\n");
	for (i = 0; i < 14; i++){
		printf("%d: %d\n", i+1, FileHeader[i]);
	}

	//输出信息头，40字节
	printf("\n  BMP Information Header\n");
	for (i = 0; i < 40; i++){
		printf("%d: %d\n", i+1, InfoHeader[i]);
	}

	//输出调色板，4*256字节
    printf("\n  Color Map\n");
	for (i = 0; i < 256; i++){
		printf("%d: \t", i);
		for (j = 0; j < 4; j++){
		printf("%d\t", rgbQuad[i*4+j]);
		}
		printf("\n");
	}

	return 0;
}

