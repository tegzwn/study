

/*********************************************
*
*   ���ܣ���BMPͼ���ļ�
*   ע�����ֻ������8λ�Ҷ�ͼ�Ĳ�����
*
************************************************/

#include "cips.h"

/*��BMPͼ���ļ����ļ�ͷ����Ϣͷ�͵�ɫ����������Ϣ*/
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


