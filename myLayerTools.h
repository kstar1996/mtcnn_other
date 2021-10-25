//
// Created by uxfac on 2021-09-13.
//

#ifndef MTCNN_MYLAYERTOOLS_H
#define MTCNN_MYLAYERTOOLS_H

#include "unionHeader.h"

int16_t addOverflowCheck(int16_t *value, int16_t added);

int16_t newChangeBit(int32_t num, int shift);

int16_t latestChangeBit32(int32_t *num, int shift);

int16_t latestChangeBit64(int64_t *num, int shift);

int16_t **
my3x3Convolution(int8_t **weightValue, int16_t *featureBuffer, int width, int height, int filterSize, int stride,
                 int padding,
                 int outChannels, int featureOffset, int shiftBitCount);

int16_t **
fprintDecmy3x3Convolution(int8_t **weightValue, int16_t *featureBuffer, int width, int height, int filterSize, int stride,
                     int padding,
                     int outChannels, int featureOffset, int shiftBitCount, FILE *tfp, FILE *inputfp);

int16_t **
fprintHexmy3x3Convolution(int8_t **weightValue, int16_t *featureBuffer, int width, int height, int filterSize, int stride,
                     int padding,
                     int outChannels, int featureOffset, int shiftBitCount, FILE *tfp, FILE *inputfp);

int16_t **ReturnPnetTop32(int16_t **pNetResults);
int64_t **
my1x1Convolution(int8_t *weightValue, int16_t *featureBuffer, int outChannels, int featureOffset);

int64_t **
fprintDecmy1x1Convolution(int8_t *weightValue, int16_t *featureBuffer, int outChannels, int featureOffset, FILE *weightfp, FILE *inputfp);

int64_t **
fprintHexmy1x1Convolution(int8_t *weightValue, int16_t *featureBuffer, int outChannels, int featureOffset, FILE *weightfp, FILE *inputfp);

int16_t **
myBias(int16_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int bitShiftCount);

int16_t **
fprintDecmyBias(int16_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, FILE *weightfp, FILE *inputfp);

int16_t **
fprintHexmyBias(int16_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, FILE *weightfp, FILE *inputfp);

int16_t **
my11Bias(int64_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int quantShiftCount, int biasShiftCount);

int CalcOriginY(int index, float scale);
int CalcOriginX(int index, float scale);

int16_t **
fprintDecmy11Bias(int64_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp);

int16_t **
fprintHexmy11Bias(int64_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp);

int16_t **myFcBias(int16_t **inputBuffer, int8_t *bias, int outChannels, int biasShiftCount);

int16_t **fprintDecmyFcBias(int16_t **inputBuffer, int8_t *bias, int outChannels, FILE *tfp, FILE *inputfp);

int16_t **fprintHexmyFcBias(int16_t **inputBuffer, int8_t *bias, int outChannels, FILE *tfp, FILE *inputfp);

int16_t **myPrelu(int16_t **featureBuffer, int width, int height, int8_t *act, int outChannels, int shiftBitCount);

int16_t **fprintDecmyPrelu(int16_t **featureBuffer, int width, int height, int8_t *act, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp);

int16_t **fprintHexmyPrelu(int16_t **featureBuffer, int width, int height, int8_t *act, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp);

int16_t **myMaxPooling(int16_t **featureBuffer, int width, int height, int kernelSize, int stride, int outChannels,
                       int paddingSize);

int16_t **fprintDecmyMaxPooling(int16_t **featureBuffer, int width, int height, int kernelSize, int stride, int outChannels, int paddingSize, FILE *inputfp);

int16_t **myFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int shiftBitCount);

int16_t **fprintDecmyFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp);

int16_t **fprintHexmyFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp);

int16_t changeBit(int *num, int shift);

void ****freeMyLayerResult(int16_t ****pNetResults, int16_t ****rNetResults);

int16_t **FilterBBox(int16_t **pNetResults, int width, int height);

void quickSortDesc(int16_t **arr, int left, int right);

void SortDesc(int16_t **arr, int left, int right);

int16_t **FilterBBox(int16_t **pNetResults, int width, int height);


void SortDesc(int16_t **arr, int left, int right);

int16_t **
tempmyBias(int16_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, FILE *tfp);

void ChangeCoordPnet(int16_t **pNetResults);

void ChangeCoordRnet(int16_t **rNetResults, int16_t **pNetResults);

int16_t **BoundingBox(int16_t **arr, int width, int height);

int16_t **BoundingBoxCheck2(int16_t **pNetResults, int width, int height);

int16_t ** BoundingBoxCheck(int16_t **arr, int width, int height);

int16_t **Threshold(int16_t **arr, int thres, int width, int height);

void ThresholdCheck(int16_t **pNetResults, int thres);

void ReturnWidthHeightZero(int16_t **pNetResults);

void ChangeCoordinateRnet(int16_t **rNet, int16_t **pNet);

void ChangeCoordinatePnet(int16_t **arr, int type);

int16_t **FilterBBox(int16_t **pNetResults, int width, int height);

int16_t **myConvFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int width, int height, int quantShiftCount);

#endif //MTCNN_MYLAYERTOOLS_H
