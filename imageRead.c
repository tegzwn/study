//读取图像数据

#include "cips.h"

void ReadImageData(char *filename, unsigned char imageData[WIDTH][HEIGHT], int width, int height)
{
    FILE *fp;
    int i, j;
    unsigned char FileHeader[14];
    unsigned char InfoHeader[40];
    unsigned char rgbQuad[CLRUSED * 4];
    unsigned char temp;
    int dataOffset;

    // Read BMP headers
    read_bmpHeader(filename, FileHeader, InfoHeader, rgbQuad);

    // Calculate the offset to the image data
    dataOffset = 14 + 40 + CLRUSED * 4;

    // Open the BMP file for reading
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Failure to open file! \n");
        exit(0);
    }

    // Move the file pointer to the start of the image data
    fseek(fp, dataOffset, SEEK_SET);

    // Read the image data into the imageData array
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            fread(&temp, 1, 1, fp);
            imageData[i][j] = temp;
        }
    }

    // Close the BMP file
    fclose(fp);

}