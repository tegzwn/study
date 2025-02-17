// 写入图像数据到文件

#include "cips.h"

void SaveImage(const char *fileName, unsigned char imageData[HEIGHT][WIDTH], unsigned char *FileHeader, unsigned char *InfoHeader, unsigned char *rgbQuad) {
    FILE *fp;
    int i, j;
    int dataOffset = 14 + 40 + CLRUSED * 4;

    // 打开文件等待写入
    if ((fp = fopen(fileName, "wb")) == NULL) {
        printf("Failure to open file for writing! \n");
        exit(0);
    }

    // 写入BMP headers
    fwrite(FileHeader, 1, 14, fp);
    fwrite(InfoHeader, 1, 40, fp);
    fwrite(rgbQuad, 1, CLRUSED * 4, fp);

    // 写入图像数据
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            fwrite(&imageData[i][j], 1, 1, fp);
        }
    }

    // 关闭文件
    fclose(fp);
}