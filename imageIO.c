

/*********************************************
*
*   功能：读BMP图像文件
*   注意事项：只适用于8位灰度图的操作。
*
************************************************/

#include "cips.h"

/*读BMP图像文件的文件头、信息头和调色板三部分信息*/
void read_bmpHeader(char *filename, unsigned char bmFileHeader[], unsigned char bmInfoHeader[], unsigned char bmClrMap[])
{
	FILE *fp;
	unsigned char temp;
	int i;

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Failure to open file! \n");
        exit(0);
	}

	for (i = 0; i < 14; i++)
	{
		fread(&temp, 1, 1, fp);
		bmFileHeader[i] = temp;
	}

	for (i = 0; i < 40; i++)
	{
		fread(&temp, 1, 1, fp);
		bmInfoHeader[i] = temp;
	}

	for (i = 0; i < CLRUSED*4; i++)
	{
		fread(&temp, 1, 1, fp);
		bmClrMap[i] = temp;
	}

	fclose(fp);
}


