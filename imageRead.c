//读取图像数据

#include "cips.h"

void ReadImageData(char *filename, unsigned char imageData[HEIGHT][WIDTH], int width, int height)
{
    FILE *fp;
    int i, j;
    unsigned char temp;
    int dataOffset;

    // 计算图像数据的起始位置
    dataOffset = 14 + 40 + CLRUSED * 4;

    // 打开文件
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Fail to open file! \n");
        exit(0);
    }

    // 移动到图像数据的起始位置
    fseek(fp, dataOffset, SEEK_SET);

    // 从文件中读取图像数据保存到数组中
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            fread(&temp, 1, 1, fp);
            imageData[i][j] = temp;
        }
    }

    // 关闭文件
    fclose(fp);

}