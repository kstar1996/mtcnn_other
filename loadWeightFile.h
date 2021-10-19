//
// Created by uxfac on 2021-09-06.
//

#ifndef MTCNN_LOADWEIGHTFILE_H
#define MTCNN_LOADWEIGHTFILE_H

#include "unionHeader.h"



typedef struct LoadFileStruct {
    int fileSize;
    uint8_t *fileBuffer;
} LoadFileStruct;

typedef struct PnetWeightValue {
    int filterNumberConv1;
    int filterOutChannels1;
    int8_t **conv1R;
    int8_t **conv1G;
    int8_t **conv1B;
    int8_t *bias1;
    int8_t *act1;
    int filterNumberConv2;
    int filterOutChannels2;
    int8_t **conv2;
    int8_t *bias2;
    int8_t *act2;
    int filterNumberConv3;
    int filterOutChannels3;
    int8_t **conv3;
    int8_t *bias3;
    int8_t *act3;
    int filterNumberConv4;
    int filterOutChannels4;
    int8_t *conv4;
    int8_t *bias4;
    int filterNumberConv5;
    int filterOutChannels5;
    int8_t *conv5;
    int8_t *bias5;
} PnetWeightValue;

typedef struct RnetWeightValue {
    int filterNumberConv1;
    int filterOutChannels1;
    int8_t **conv1R;
    int8_t **conv1G;
    int8_t **conv1B;
    int8_t *bias1;
    int8_t *act1;
    int filterNumberConv2;
    int filterOutChannels2;
    int8_t **conv2;
    int8_t *bias2;
    int8_t *act2;
    int filterNumberConv3;
    int filterOutChannels3;
    int8_t **conv3;
    int8_t *bias3;
    int8_t *act3;
    int fcNumber1;
    int fcOutChannels1;
    int8_t *fc1;
    int8_t *bias4;
    int8_t *act4;
    int fcNumber2;
    int fcOutChannels2;
    int8_t *fc2;
    int8_t *bias5;
    int fcNumber3;
    int fcOutChannels3;
    int8_t *fc3;
    int8_t *bias6;
} RnetWeightValue;

typedef struct WeightValue {
    PnetWeightValue *pnetWeightValue;
    RnetWeightValue *rnetWeightValue;

} WeightValue;


uint8_t swapValue(uint8_t value);

void reverseBuffer(uint8_t *buffer, int size);

LoadFileStruct loadWeightFile(char *filePath);

int8_t *mergeWeight(uint8_t *weightBuffer, int weightBufferSize);

void initPnetWeightMemory(WeightValue *weightValue);

void initRnetWeightMemory(WeightValue *weightValue);

WeightValue *initWeightMemory();

void freeWeightValue(WeightValue *weightValue);

void insertPnetValueWeightBuffer(int8_t **sramBuffer, WeightValue *weightValue, int *offset);

void insertRnetValueWeightBuffer(int8_t **sramBuffer, WeightValue *weightValue, int *offset);

void insertValueInWeightBuffer(int8_t **sramBuffer, WeightValue *weightValue);

int8_t *makeSramWeightFile(char *filePath);

int8_t **loadMySram();

void freeSramValue(int8_t **sramWeightBuffer);

#endif //MTCNN_LOADWEIGHTFILE_H