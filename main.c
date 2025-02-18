//#include "imageIO.c"
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

	long width,height,size;

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

	// 输出文件类型
	printf("\n FileType:\n");
	for (i = 0; i < 2; i++){
		printf("%c", FileHeader[i]);
	}

	// 输出文件大小
	size = *(int*)&FileHeader[2];  //将文件大小转换为字节数输出
	printf("\n FileSize: %d Byte\n", size);
	
	// 输出图像宽度
	width = *(int*)&InfoHeader[4]; //将宽度转换为10进制数输出
	printf("\n Width: %d Pixel\n", width);

	// 输出图像高度
	height = *(int*)&InfoHeader[8]; //将高度转换为10进制数输出
	printf("\n Height: %d Pixel\n", height);

	// 创建imageData[i][j]数组，存储图像数据
	unsigned char imageData[WIDTH][HEIGHT];

	ReadImageData(fileName_IN,imageData,width,height); // 读取图像数据

    char fileName_OUT1[] = "lena4_new.bmp"; // 输出图像文件名
	SaveImage(fileName_OUT1, imageData, FileHeader, InfoHeader, rgbQuad);  // 保存图像数据到文件

	// 涂黑四角部分
	SmearImage(imageData);  // 调用SmearImage函数，修改图像数据
    char fileName_OUT2[] = "lena5_black.bmp"; // 输出图像文件名
	SaveImage(fileName_OUT2, imageData, FileHeader, InfoHeader, rgbQuad);  // 保存图像数据到文件

	// 平移图像部分
    int shiftX = 10; // 水平平移
    int shiftY = 10; // 垂直平移
    ShiftImage(imageData, shiftX, shiftY);  // 移动图像
    char fileName_OUT3[] = "lena6_shift.bmp"; // 输出图像文件名
	SaveImage(fileName_OUT3, imageData, FileHeader, InfoHeader, rgbQuad);  // 保存图像数据到文件

	// 缩小图像部分
	unsigned char scaledImage[WIDTH][HEIGHT];	// 缩小后的图像数据
	DownsizeImage(imageData, scaledImage);// 缩小图像
    char fileName_OUT4[] = "lena7_scale.bmp"; // 输出图像文件名
	SaveImage(fileName_OUT4, scaledImage, FileHeader, InfoHeader, rgbQuad);  // 保存图像数据到文件

	// 旋转图像部分
	unsigned char rotatedImage[HEIGHT][WIDTH];	// 旋转后的图像数据
	RotateImage(imageData, rotatedImage); // 旋转图像
	char fileName_OUT5[] = "lena8_rotate.bmp"; // 输出图像文件名
	SaveImage(fileName_OUT5, rotatedImage, FileHeader, InfoHeader, rgbQuad);  // 保存图像数据到文件


	//debug区域
	printf("Debug: \n");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf("%d ", imageData[i][j]);
		}
		printf("\n");
	}

	return 0;
}

