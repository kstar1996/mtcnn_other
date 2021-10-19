//
// Created by uxfac on 2021-09-07.
//

#ifndef MTCNN_LOADIMAGEFILE_H
#define MTCNN_LOADIMAGEFILE_H

#include "unionHeader.h"

uint8_t ***loadImage(char *filePath, int width, int height, int channels);

uint8_t ****loadMyImage(char *imagePath);

void freeMyImage(uint8_t ***image, int width, int height, int channels);

uint8_t ****loadMyImageHalf(char *imagePath);

uint8_t ****loadMyImageTwoThird(char *imagePath);

uint8_t ***loadImageTwoThird(char *filePath, int width, int height, int channels);

#endif //MTCNN_LOADIMAGEFILE_H