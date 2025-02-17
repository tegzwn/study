
#include "cips.h"

int main()
{
	FILE *fp;  // FILE���ͣ���stdio.hͷ�ļ��У�FILE����һ���ṹ�壬�����κ�һ���κ����͵��ļ��������ļ��Ķ�д������
	int i, j;
	unsigned char FileHeader[14];
	unsigned char InfoHeader[40];
	unsigned char rgbQuad[CLRUSED*4];
	unsigned char imArray[HEIGHT][WIDTH];

	char fileName_IN[]	= "lena_in.bmp";

	unsigned char temp;
	int dataOffset;  //���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���=λͼ�ļ�ͷ����+λͼ��Ϣͷ����+��ɫ�峤��

	read_bmpHeader(fileName_IN, FileHeader, InfoHeader, rgbQuad);

	//��ͼ������
	dataOffset = 14 + 40 + CLRUSED*4;

	if ((fp = fopen(fileName_IN, "rb")) == NULL)
    {
        printf("Failure to open file! \n");
        exit(0);
	}

	fseek(fp, dataOffset, SEEK_SET);  //����ͼ���ļ�ͷ���֣���ʼ��ͼ������

	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			fread(&temp, 1, 1, fp);
			imArray[i][j] = temp;
		}
	}

	fclose(fp);

	/*�����ʾBMPͼ����ļ�ͷ����Ϣͷ�͵�ɫ����������Ϣ*/
	//����ļ�ͷ��14�ֽ�
	printf("\n  BMP File Header\n");
	for (i = 0; i < 14; i++){
		printf("%d: %d\n", i+1, FileHeader[i]);
	}

	//�����Ϣͷ��40�ֽ�
	printf("\n  BMP Information Header\n");
	for (i = 0; i < 40; i++){
		printf("%d: %d\n", i+1, InfoHeader[i]);
	}

	//�����ɫ�壬4*256�ֽ�
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

