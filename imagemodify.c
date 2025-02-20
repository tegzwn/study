//修改图像

#include "cips.h"

// 涂黑图像的四角
void SmearImage(unsigned char imageData[HEIGHT][WIDTH], unsigned char smearImage[HEIGHT][WIDTH]) {
    int i, j;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            smearImage[i][j] = imageData[i][j];
        }
    }

    // 将顶部左侧50x50区域涂黑
    for (i = 0; i < 50; i++) {
        for (j = 0; j < 50; j++) {
            smearImage[i][j] = 0;
        }
    }

    // 将底部左侧50x50区域涂黑
    for (i = HEIGHT - 50; i < HEIGHT; i++) {
        for (j = 0; j < 50; j++) {
            smearImage[i][j] = 0;
        }
    }

    // 将顶部右侧50x50区域涂黑
    for (i = 0; i < 50; i++) {
        for (j = WIDTH - 50; j < WIDTH; j++) {
            smearImage[i][j] = 0;
        }
    }

    // 将底部右侧50x50区域涂黑
    for (i = HEIGHT - 50; i < HEIGHT; i++) {
        for (j = WIDTH - 50; j < WIDTH; j++) {
            smearImage[i][j] = 0;
        }
    }
}

// 移动图像
void ShiftImage(unsigned char imageData[HEIGHT][WIDTH], int shiftX, int shiftY, unsigned char shiftedData[HEIGHT][WIDTH]) {
    unsigned char tempImage[HEIGHT][WIDTH] = {0};
    int i, j;

    // 确保移动值在有效范围内
    if (shiftX < -WIDTH || shiftX > WIDTH || shiftY < -HEIGHT || shiftY > HEIGHT) {
        printf("无效的移动值!\n");
        return;
    }

    // 平移图像
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            int newX = j + shiftX;
            int newY = i + shiftY;

            if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT) {
                tempImage[newY][newX] = imageData[i][j];
            }
        }
    }

    // 将平移后的图像复制回原始图像
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            shiftedData[i][j] = tempImage[i][j];
        }
    }
}

// 缩小图像
void DownsizeImage(unsigned char imageData[HEIGHT][WIDTH], unsigned char scaledImage[HEIGHT][WIDTH]) {
    int i, j;

    // 生成黑色底图
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            scaledImage[i][j] = 0;
        }
    }

    // 以2x2缩小图像并覆盖黑色底图
    for (i = 0; i < HEIGHT / 2; i++) {
        for (j = 0; j < WIDTH / 2; j++) {
            scaledImage[i][j] = imageData[i * 2][j * 2];
        }
    }
}

// 旋转图像
void RotateImage(unsigned char imageData[HEIGHT][WIDTH], unsigned char rotatedImage[WIDTH][HEIGHT]) {
    int i, j;

    // 逆时针旋转90度
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            rotatedImage[WIDTH - 1 - j][i] = imageData[i][j];
        }
    }
}

