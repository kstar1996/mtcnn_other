//
// Created by uxfac on 2021-09-13.
//
#include "myLayerTools.h"
//#include <bits/stdint-intn.h>
#include <math.h>

// for changing from 32 to 16 signed bit
int16_t changeBit(int32_t *num, int shift){
    int16_t beta = (*num >> shift) & 32767;
    // printf("beta is: %d\n",beta);
    int32_t mul_s = (*num>>31) & 1;
    // printf("mul_s is: %d\n",mul_s);
    int16_t result = beta + (mul_s * 32768);
    // printf("result: %d\n",result);
    return result;
}


int16_t latestChangeBit32(int32_t *num, int shift){
    // 32 bit with sign bit , full num
    int32_t beta1 = (*num >> shift);

    int16_t beta2 = beta1 & 32767;
    // printf("beta is: %d\n",beta);
    int32_t mul_s = (*num >> 31) & 1;
    // the full number
    int16_t result = beta2 + (mul_s * 32768);

    if(result >= 0 && beta1 >= 0 && (beta1>result)){
        return 32767;
    }
    else if(result < 0 && beta1 < 0 && (beta1<result)){
        return -32768;
    }
    else {
        return result;
    }
}

int16_t **ReturnPnetTop32(int16_t **pNetResults){
    int16_t **pNetResultsFinal = (int16_t **)malloc(32 * sizeof(int16_t *));
    for(int i=0; i<32; i++) {
        pNetResultsFinal[i] = pNetResults[i];
        // pNetResultsFinal[i] = pNetResults[i];
    }
    return pNetResultsFinal;
}

int16_t latestChangeBit64(int64_t *num, int shift){
    // 64 bit with sign bit , full num
    int64_t beta1 = (*num >> shift);

    int16_t beta2 = beta1 & 32767;
    int64_t mul_s = (*num >> 63) & 1;
    // the full number
    int16_t result = beta2 + (mul_s * 32768);

    if(result >= 0 && beta1 >= 0 && (beta1>result)){
        return 32767;
    }
    else if(result < 0 && beta1 < 0 && (beta1<result)){
        return -32768;
    }
    else {
        return result;
    }
}


int16_t addOverflowCheck(int16_t *value, int16_t added) {
    // overflow
    if (*value > 0 && added > INT16_MAX - *value) {
        *value = INT16_MAX;
        //underflow
    } else if (*value < 0 && added < INT16_MIN - *value) {
        *value = INT16_MIN;
    }
    else{
        *value = *value + added;
    }
    return *value;
}


int32_t multOverflowCheck(int32_t a, int32_t b) {
    // overflow
    int32_t result = a * b;
    if (a == 0 || b == 0) {
        return 0;
    }

    if (a == result / b){
        return result;
    }
    else{
        if ((a > 0 && b>0) || (a<0 && b<0)){
            return INT32_MAX;
        }
        else if((a < 0 && b>0) || (a>0 && b<0)){
            return INT32_MIN;
        }
        else{
            return result;
        }
    }
}


void OverflowCheck(int16_t *value){
    if (*value > INT16_MAX){
        *value = INT16_MAX;
    }
    else if (*value < INT16_MIN){
        *value = INT16_MIN;
    }
}

void OverflowCheck32(int32_t *value){
    if (*value > INT16_MAX){
        *value = INT16_MAX;
    }
    else if (*value < INT16_MIN){
        *value = INT16_MIN;
    }
}

void quickSortDesc(int16_t **arr, int left, int right) {
    int Left = left, Right = right;
    int16_t ***temp;
    int pivot = arr[(left + right) / 2][1];

    while (Left <= Right) {
        while (arr[Left][1] > pivot) {
            Left++;
        }
        while (arr[Right][1] < pivot) {
            Right--;
        }

        if (Left <= Right) {
            if (Left != Right) {
                temp = arr[Left];
                arr[Left] = arr[Right];
                arr[Right] = temp;
            }
            Left++; Right--;
        }
    }
    if (left < Right) {
        quickSortDesc(arr, left, Right);
    }
    if (Left < right) {
        quickSortDesc(arr, Left, right);
    }
}


void SortDesc(int16_t **arr, int left, int right) {
    int L = left, R = right;
    int16_t ***temp;
    int16_t pivot;
    int16_t pivot1= arr[(left + right) / 2][0];
    int16_t pivot2= arr[(left + right) / 2][1];

//    printf("pivot1: %d\n",pivot1);
//    printf("pivot2: %d\n",pivot2);

    if (pivot1-pivot2>INT16_MAX){
        pivot = INT16_MAX;
    }
    else if(pivot1-pivot2<INT16_MIN){
        pivot = INT16_MIN;
    }
    else{
        pivot = pivot1-pivot2;
    }

//    printf("pivot: %d\n",pivot);
//    pivot = arr[(left + right) / 2][0][0][0];

    while (L <= R) {
        int pivotL = arr[L][0]-arr[L][1];
        int pivotR = arr[R][0]-arr[R][1];

        if (pivotL > pivot) {
            L++;
        }
        if (pivotR < pivot) {
            R--;
        }

        if (L <= R) {
            if (L != R) {
                temp = arr[L];
                arr[L] = arr[R];
                arr[R] = temp;
            }
            L++; R--;
        }
    }
    if (left < R)
        quickSortDesc(arr, left, R);
    if (L < right)
        quickSortDesc(arr, L, right);
}

int16_t **
my3x3Convolution(int8_t **weightValue, int16_t *featureBuffer, int width, int height, int filterSize, int stride,
                 int padding,
                 int outChannels, int featureOffset, int shiftBitCount) {
    int featureSize = (((width) - filterSize + (2 * padding)) / stride) + 1;
    int16_t **kernelResult = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        kernelResult[i] = (int16_t *) malloc((width - 2) * (height - 2) * sizeof(int16_t));
    }
    int iCounter = 0;
    int jCounter = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < featureSize; j++) {
            for (int k = 0; k < featureSize; k++) {
                int32_t temp =
                        (int8_t) weightValue[i + (featureOffset * outChannels)][0]*
                        (int16_t) featureBuffer[((j * height) + k)] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][1]*
                        (int16_t) featureBuffer[((j * height) + k) + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][2]*
                        (int16_t) featureBuffer[((j * height) + k) + 2] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][3]*
                        (int16_t) featureBuffer[((j * height) + k) + width] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][4]*
                        (int16_t) featureBuffer[((j * height) + k) + width + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][5]*
                        (int16_t) featureBuffer[((j * height) + k) + width + 2] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][6]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][7]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][8]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width + 2];

                temp = latestChangeBit32(&temp, shiftBitCount);

                //    temp = valueOverflowCheck(&temp);

                kernelResult[i][(j * (height - 2)) + k] = (int16_t) temp;
                jCounter++;
            }
        }
        iCounter++;
    }
    return kernelResult;
}

int16_t **
fprintDecmy3x3Convolution(int8_t **weightValue, int16_t *featureBuffer, int width, int height, int filterSize, int stride,
                          int padding,
                          int outChannels, int featureOffset, int shiftBitCount, FILE *tfp, FILE *inputfp) {
    int featureSize = (((width) - filterSize + (2 * padding)) / stride) + 1;
    int16_t **kernelResult = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        kernelResult[i] = (int16_t *) malloc((width - 2) * (height - 2) * sizeof(int16_t));
    }
    int iCounter = 0;
    int jCounter = 0;
    // printf("check: %d =====================================================\n", outChannels);
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < featureSize; j++) {
            for (int k = 0; k < featureSize; k++) {
                int32_t temp =
                        (int8_t) weightValue[i + (featureOffset * outChannels)][0]*
                        (int16_t) featureBuffer[((j * height) + k)] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][1]*
                        (int16_t) featureBuffer[((j * height) + k) + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][2]*
                        (int16_t) featureBuffer[((j * height) + k) + 2] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][3]*
                        (int16_t) featureBuffer[((j * height) + k) + width] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][4]*
                        (int16_t) featureBuffer[((j * height) + k) + width + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][5]*
                        (int16_t) featureBuffer[((j * height) + k) + width + 2] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][6]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][7]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][8]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width + 2];
                // changed this part
                temp = latestChangeBit32(&temp, shiftBitCount);
                if(i==0){
                    fprintf(inputfp, "%d %d %d %d %d %d %d %d %d \n",
                            (int) featureBuffer[((j * height) + k)],
                            (int) featureBuffer[((j * height) + k) + 1],
                            (int) featureBuffer[((j * height) + k) + 2],
                            (int) featureBuffer[((j * height) + k) + width] ,
                            (int) featureBuffer[((j * height) + k) + width + 1] ,
                            (int) featureBuffer[((j * height) + k) + width + 2] ,
                            (int) featureBuffer[((j * height) + k) + width + width] ,
                            (int) featureBuffer[((j * height) + k) + width + width + 1] ,
                            (int) featureBuffer[((j * height) + k) + width + width + 2]);
                }


            //    temp = valueOverflowCheck(&temp);


                kernelResult[i][(j * (height - 2)) + k] = (int16_t) temp;
                jCounter++;
            }
        }
        for(int t=0; t<9; t++){
            fprintf(tfp, "%d ", weightValue[i + (featureOffset * outChannels)][t]);
        }
        fprintf(tfp, "\n");
        iCounter++;
    }

    return kernelResult;
}

int16_t **
fprintHexmy3x3Convolution(int8_t **weightValue, int16_t *featureBuffer, int width, int height, int filterSize, int stride,
                          int padding,
                          int outChannels, int featureOffset, int shiftBitCount, FILE *tfp, FILE *inputfp) {
    int featureSize = (((width) - filterSize + (2 * padding)) / stride) + 1;
    int16_t **kernelResult = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        kernelResult[i] = (int16_t *) malloc((width - 2) * (height - 2) * sizeof(int16_t));
    }
    int iCounter = 0;
    int jCounter = 0;
    // printf("check: %d =====================================================\n", outChannels);
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < featureSize; j++) {
            for (int k = 0; k < featureSize; k++) {
                int32_t temp =
                        (int8_t) weightValue[i + (featureOffset * outChannels)][0]*
                        (int16_t) featureBuffer[((j * height) + k)] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][1]*
                        (int16_t) featureBuffer[((j * height) + k) + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][2]*
                        (int16_t) featureBuffer[((j * height) + k) + 2] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][3]*
                        (int16_t) featureBuffer[((j * height) + k) + width] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][4]*
                        (int16_t) featureBuffer[((j * height) + k) + width + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][5]*
                        (int16_t) featureBuffer[((j * height) + k) + width + 2] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][6]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][7]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width + 1] +
                        (int8_t) weightValue[i + (featureOffset * outChannels)][8]*
                        (int16_t) featureBuffer[((j * height) + k) + width + width + 2];

                temp = latestChangeBit32(&temp, shiftBitCount);
                if(i==1){
                    fprintf(inputfp, "%04x %04x %04x %04x %04x %04x %04x %04x %04x \n",
                            (int) featureBuffer[((j * height) + k)],
                            (int) featureBuffer[((j * height) + k) + 1],
                            (int) featureBuffer[((j * height) + k) + 2],
                            (int) featureBuffer[((j * height) + k) + width] ,
                            (int) featureBuffer[((j * height) + k) + width + 1] ,
                            (int) featureBuffer[((j * height) + k) + width + 2] ,
                            (int) featureBuffer[((j * height) + k) + width + width] ,
                            (int) featureBuffer[((j * height) + k) + width + width + 1] ,
                            (int) featureBuffer[((j * height) + k) + width + width + 2]);
                }


            //    temp = valueOverflowCheck(&temp);


                kernelResult[i][(j * (height - 2)) + k] = (int16_t) temp;
                jCounter++;
            }
        }
        for(int t=0; t<9; t++){
            fprintf(tfp, "%02x ", weightValue[i + (featureOffset * outChannels)][t]);
        }
        fprintf(tfp, "\n");
        iCounter++;
    }

    return kernelResult;
}

int64_t **
my1x1Convolution(int8_t *weightValue, int16_t *featureBuffer, int outChannels, int featureOffset) {
    int featureSize = 1;
    int64_t **kernelResult = (int64_t **) malloc(outChannels * sizeof(int64_t *));
    for (int i = 0; i < outChannels; i++) {
        kernelResult[i] = (int64_t *) malloc(1 * sizeof(int64_t));
    }
    for (int i = 0; i < outChannels; i++) {
        int64_t temp = 0;
        for (int j = 0; j < featureSize; j++) {
            temp = (int8_t) weightValue[featureOffset + (i*32)] * (int16_t) featureBuffer[j];
            kernelResult[i][j] = (int64_t) temp;
        }
    }
    return kernelResult;
}

int64_t **
fprintDecmy1x1Convolution(int8_t *weightValue, int16_t *featureBuffer, int outChannels, int featureOffset, FILE *weightfp, FILE *inputfp) {
    int featureSize = 1;
    int64_t **kernelResult = (int64_t **) malloc(outChannels * sizeof(int64_t *));
    for (int i = 0; i < outChannels; i++) {
        kernelResult[i] = (int64_t *) malloc(1 * sizeof(int64_t));
    }
    for (int i = 0; i < outChannels; i++) {
        int64_t temp = 0;
        for (int j = 0; j < featureSize; j++) {
            temp = (int8_t) weightValue[featureOffset + (i*32)] * (int16_t) featureBuffer[j];
            kernelResult[i][j] = (int64_t) temp;

            fprintf(inputfp, "%d\n", featureBuffer[j]);
        }
        fprintf(weightfp, "%d\n", weightValue[featureOffset + (i*32)]);
    }
    return kernelResult;
}

int64_t **
fprintHexmy1x1Convolution(int8_t *weightValue, int16_t *featureBuffer, int outChannels, int featureOffset, FILE *weightfp, FILE *inputfp) {
    int featureSize = 1;
    int64_t **kernelResult = (int64_t **) malloc(outChannels * sizeof(int64_t *));
    for (int i = 0; i < outChannels; i++) {
        kernelResult[i] = (int64_t *) malloc(1 * sizeof(int64_t));
    }
    for (int i = 0; i < outChannels; i++) {
        int64_t temp = 0;
        for (int j = 0; j < featureSize; j++) {
            temp = (int8_t) weightValue[featureOffset + (i*32)] * (int16_t) featureBuffer[j];
            //    temp = valueOverflowCheck(&temp);
            kernelResult[i][j] = (int64_t) temp;

            fprintf(inputfp, "%x\n", featureBuffer[j]);
        }
        fprintf(weightfp, "%02x\n", weightValue[featureOffset + (i*32)]);
    }
    return kernelResult;
}

int16_t **myConvFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int width, int height, int quantShiftCount) {
    int16_t **resultBuffer;
    resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(1 * sizeof(int16_t));
    }
    for (int i = 0; i < outChannels; i++) {
        int64_t temp = 0;
        for (int j = 0; j < inputChannels; j++) {
            for(int k = 0; k < height; k++){
                for(int l = 0; l < width; l++){
                    temp += featureBuffer[j][k * width + l] *
                            fc[(i * width * height * inputChannels) + (j * width * height) + (k * width) + l];
                }
            }
        }
        temp = latestChangeBit64(&temp, quantShiftCount);
        resultBuffer[i][0] = (int16_t) temp;
    }
    return resultBuffer;
}

int16_t **
myBias(int16_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int bitShiftCount) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int16_t temp = 0;
            for (int k = 0; k < inputChannels; k++) {
                temp = addOverflowCheck(&temp, inputBuffer[k][i][j]);
            }
            int32_t temp32 = 0;
            int16_t biasTemp = bias[i];

            if(biasTemp&0x80) biasTemp = biasTemp << bitShiftCount;
            else biasTemp = biasTemp >> bitShiftCount;

            temp32 = temp + biasTemp;
            OverflowCheck32(&temp32);
            // overflow check
            //    temp = valueOverflowCheck(&temp);
            resultBuffer[i][j] = (int16_t)temp32;
            jCount++;
        }
        iCount++;
    }
    return resultBuffer;
}

int16_t **
fprintDecmyBias(int16_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int16_t temp = 0;
            for (int k = 0; k < inputChannels; k++) {
                //    temp += (int) inputBuffer[k][i][j];
                temp = addOverflowCheck(&temp, inputBuffer[k][i][j]);
                fprintf(inputfp, "%d\n", inputBuffer[k][i][j]);
            }
            int32_t temp32 = 0;
            temp32 = temp + bias[i];
            OverflowCheck32(&temp32);
            // overflow check
        //    temp = valueOverflowCheck(&temp);
            resultBuffer[i][j] = (int16_t)temp32;
            jCount++;
        }
        fprintf(weightfp, "%d\n", bias[i]);
        iCount++;
    }
    return resultBuffer;
}

int16_t **
fprintHexmyBias(int16_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int16_t temp = 0;
            for (int k = 0; k < inputChannels; k++) {
            //    temp += (int) inputBuffer[k][i][j];
                temp = addOverflowCheck(&temp, inputBuffer[k][i][j]);
                fprintf(inputfp, "%x\n", inputBuffer[k][i][j]);
            }
            int32_t temp32 = 0;
            temp32 = temp + bias[i];
            OverflowCheck32(&temp32);
            // overflow check
        //    temp = valueOverflowCheck(&temp);
            resultBuffer[i][j] = (int16_t)temp32;
            jCount++;
        }
        fprintf(weightfp, "%02x\n", bias[i]);
        iCount++;
    }
    return resultBuffer;
}

int16_t **
my11Bias(int64_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int quantShiftCount, int biasShiftCount) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int64_t temp = 0;
            for (int k = 0; k < inputChannels; k++) {
                temp += (int64_t) inputBuffer[k][i][j];
                // temp = addOverflowCheck(&tem, inputBuffer[k][i][j]);
            }
            int16_t biasTemp = bias[i];

            if(biasTemp&0x80) biasTemp = biasTemp << biasShiftCount;
            else biasTemp = biasTemp >> biasShiftCount;

            temp = temp + biasTemp;
            temp = latestChangeBit64(&temp, quantShiftCount);
            resultBuffer[i][j] = (int16_t)temp;
            jCount++;
        }
        iCount++;
    }
    return resultBuffer;
}

int16_t **
fprintDecmy11Bias(int64_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }
    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int64_t temp = 0;
            for (int k = 0; k < inputChannels; k++) {
                temp += (int64_t) inputBuffer[k][i][j];
                // temp = addOverflowCheck(&tem, inputBuffer[k][i][j]);
                fprintf(inputfp, "%ld\n", inputBuffer[k][i][j]);
            }
            temp = temp + bias[i];
            temp = latestChangeBit64(&temp, shiftBitCount);
            resultBuffer[i][j] = (int16_t)temp;
            jCount++;
        }
        iCount++;
        fprintf(weightfp, "%d\n", bias[i]);
    }
    return resultBuffer;
}

int16_t **
fprintHexmy11Bias(int64_t ***inputBuffer, int width, int height, int8_t *bias, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int64_t temp = 0;
            for (int k = 0; k < inputChannels; k++) {
                temp += (int64_t) inputBuffer[k][i][j];
                // temp = addOverflowCheck(&tem, inputBuffer[k][i][j]);
                fprintf(inputfp, "%lx\n", inputBuffer[k][i][j]);
            }
            temp = temp + bias[i];
            temp = latestChangeBit64(&temp, shiftBitCount);
            resultBuffer[i][j] = (int16_t)temp;

            jCount++;
        }
        iCount++;
        fprintf(weightfp, "%02x\n", bias[i]);
    }
    return resultBuffer;
}

int16_t **myFcBias(int16_t **inputBuffer, int8_t *bias, int outChannels, int biasShiftCount) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(1 * sizeof(int16_t));
    }
    for (int i = 0; i > outChannels; i++) {
        int32_t temp = 0;
        int16_t biasTemp = bias[i];

        if(biasTemp&0x80) biasTemp = biasTemp << biasShiftCount;
        else biasTemp = biasTemp >> biasShiftCount;

        temp = (int16_t)inputBuffer[i][0] + biasTemp;
        resultBuffer[i][0] = (int16_t) temp;
    }
    return resultBuffer;

}

int16_t **fprintDecmyFcBias(int16_t **inputBuffer, int8_t *bias, int outChannels, FILE *tfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(1 * sizeof(int16_t));
    }

    for (int i = 0; i > outChannels; i++) {
        int32_t temp = 0;
        temp = (int16_t)inputBuffer[i][0] + (int8_t)bias[i];
        //    temp = valueOverflowCheck(&temp);
        resultBuffer[i][0] = (int16_t) temp;
        fprintf(tfp, "%d\n", bias[i]);
        fprintf(inputfp, "%d\n", inputBuffer[i][0]);
    }
    return resultBuffer;
}

int16_t **fprintHexmyFcBias(int16_t **inputBuffer, int8_t *bias, int outChannels, FILE *tfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(1 * sizeof(int16_t));
    }

    for (int i = 0; i > outChannels; i++) {
        int32_t temp = 0;
        temp = (int16_t)inputBuffer[i][0] + (int8_t)bias[i];
        //    temp = valueOverflowCheck(&temp);
        resultBuffer[i][0] = (int16_t) temp;
        fprintf(tfp, "%02x\n", bias[i]);
        fprintf(inputfp, "%x\n", inputBuffer[i][0]);
    }
    return resultBuffer;
}

int16_t **myPrelu(int16_t **featureBuffer, int width, int height, int8_t *act, int outChannels, int shiftBitCount) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }
    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int32_t temp = (int16_t) featureBuffer[i][j];
            if (temp > 0) {
                temp = temp << shiftBitCount;
            } else {
                temp = temp * (int8_t) act[i];
            }
            temp = latestChangeBit32(&temp, shiftBitCount);
            resultBuffer[i][j] = (int16_t)temp;

            jCount++;
        }
        iCount++;
    }
    return resultBuffer;
}

int16_t **fprintDecmyPrelu(int16_t **featureBuffer, int width, int height, int8_t *act, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int32_t temp = (int16_t) featureBuffer[i][j];
            fprintf(inputfp, "%d\n", featureBuffer[i][j]);
            if (temp > 0) {
                temp = temp << shiftBitCount;
            } else {
                temp = temp * (int8_t) act[i];

            }
            temp = latestChangeBit32(&temp, shiftBitCount);
            resultBuffer[i][j] = (int16_t)temp;
            jCount++;
        }
        iCount++;
        fprintf(weightfp, "%d\n", act[i]);
    }
    return resultBuffer;
}

int16_t **fprintHexmyPrelu(int16_t **featureBuffer, int width, int height, int8_t *act, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(width * height * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            int32_t temp = (int16_t) featureBuffer[i][j];
            fprintf(inputfp, "%x\n", featureBuffer[i][j]);
            if (temp > 0) {
                temp = temp << shiftBitCount;
            } else {
                temp = temp * (int8_t) act[i];
            }
            temp = latestChangeBit32(&temp, shiftBitCount);
            resultBuffer[i][j] = (int16_t)temp;
            jCount++;
        }
        iCount++;
        fprintf(weightfp, "%02x\n", act[i]);
    }
    return resultBuffer;
}

int16_t **myMaxPooling(int16_t **featureBuffer, int width, int height, int kernelSize, int stride, int outChannels, int paddingSize) {
    int16_t **swapBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    if (paddingSize != 0) {
        for(int i = 0; i < outChannels; i++){
            swapBuffer[i] = (int16_t *) malloc((width + paddingSize) * (width + paddingSize) * sizeof(int16_t));
            memset(swapBuffer[i], 0, (width + paddingSize) * (width + paddingSize) * sizeof(int16_t));
            for(int j = 0; j < height; j++){
                for(int k = 0; k < width; k++){
                    swapBuffer[i][(j * width) + (j * paddingSize) + k] = featureBuffer[i][(j * width) + k];
                }
            }
        }
    } else {
        for (int i = 0; i < outChannels; i++) {
            swapBuffer[i] = (int16_t *) malloc(height * width * sizeof(int16_t));
            memcpy(swapBuffer[i], featureBuffer[i], (height * width * sizeof(int16_t)));
        }
    }
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    int mpOutSize = ((((width + paddingSize) - kernelSize) / stride) + 1);
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(mpOutSize * mpOutSize * sizeof(int16_t));
    }

    int iCount = 0;
    int jCount = 0;
    int kCount = 0;
    int mpCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < mpOutSize; j++) {
            for (int k = 0; k < mpOutSize; k++) {
                int temp = 0;
                int max = INT32_MIN;
                mpCount = 0;
                for (int a = 0; a < kernelSize; a++) {
                    for (int b = 0; b < kernelSize; b++) {
                        temp = swapBuffer[i][b + (k * stride) + (j * stride * (width + paddingSize)) +
                                             (a * (width + paddingSize))];
                        if (temp > max) {
                            max = temp;
                        }
                        mpCount++;
                    }
                }
                resultBuffer[i][k + (j * mpOutSize)] = max;
                kCount++;
            }
            jCount++;
        }
        iCount++;
    }
    for (int i = 0; i < outChannels; i++) {
        free(swapBuffer[i]);
    }
    free(swapBuffer);
    return resultBuffer;
}

int16_t **fprintDecmyMaxPooling(int16_t **featureBuffer, int width, int height, int kernelSize, int stride, int outChannels, int paddingSize, FILE *inputfp) {
    int16_t **swapBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    if (paddingSize != 0) {
        for(int i = 0; i < outChannels; i++){
            swapBuffer[i] = (int16_t *) malloc((width + paddingSize) * (width + paddingSize) * sizeof(int16_t));
            // memset(swapBuffer[i], 0, (width + paddingSize) * (width + paddingSize) * sizeof(int16_t));
            for(int j = 0; j < height; j++){
                // memcpy(&swapBuffer[i][j * (width + paddingSize)], &featureBuffer[i][j * width], 9 * sizeof(int16_t));
                for(int k = 0; k < width; k++){
                    swapBuffer[i][(j * (width + paddingSize)) + k] = featureBuffer[i][(j * width) + k];
                }
                swapBuffer[i][(j * (width + paddingSize)) + 9] = 0;
            }
            for(int j = 0; j < width+paddingSize; j++){
                swapBuffer[i][(height * (width + paddingSize)) + j] = 0;
            }
        }
    } else {
        for (int i = 0; i < outChannels; i++) {
            swapBuffer[i] = (int16_t *) malloc((width + paddingSize) * (width + paddingSize) * sizeof(int16_t));
            memcpy(swapBuffer[i], featureBuffer[i], (height * width * sizeof(int16_t)));
        }
    }
    int16_t **resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    int mpOutSize = ((((width + paddingSize) - kernelSize) / stride) + 1);
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(mpOutSize * mpOutSize * sizeof(int16_t));
    }
    int iCount = 0;
    int jCount = 0;
    int kCount = 0;
    int mpCount = 0;
    for (int i = 0; i < outChannels; i++) {
        for (int j = 0; j < mpOutSize; j++) {
            for (int k = 0; k < mpOutSize; k++) {
                int temp = 0;
                int max = INT32_MIN;
                mpCount = 0;
                for (int a = 0; a < kernelSize; a++) {
                    for (int b = 0; b < kernelSize; b++) {
                        temp = swapBuffer[i][(j * stride * (width + paddingSize)) + (k * stride) +
                                             (a * (width + paddingSize)) + b];
                        fprintf(inputfp, "%d: %d\n", (j * stride * (width + paddingSize)) + (k * stride) +
                                                     (a * (width + paddingSize)) + b, temp);
                        if (temp > max) {
                            max = temp;
                        }
                        mpCount++;
                    }
                }
                resultBuffer[i][(j * mpOutSize) + k] = max;
                kCount++;
                fprintf(inputfp, "MAX: %d\n\n", max);
            }
            jCount++;
        }
        iCount++;
    }
    for (int i = 0; i < outChannels; i++) {
        free(swapBuffer[i]);
    }
    free(swapBuffer);
    return resultBuffer;
}

int16_t **myFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int shiftBitCount) {
    int16_t **resultBuffer;
    resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(1 * sizeof(int16_t));
    }
    int fcWeightOffset = 0;
    for (int i = 0; i < outChannels; i++) {
        int64_t temp = 0;
        for (int j = 0; j < inputChannels; j++) {
            for (int k = 0; k < inputChannels; k++) {
                temp += featureBuffer[j][k] *
                        fc[(i * outChannels) + (j * inputChannels) + k];
            }
        }
        temp = latestChangeBit64(&temp, shiftBitCount);
        resultBuffer[i][0] = (int16_t) temp;
    }
    return resultBuffer;
}

int16_t **fprintDecmyFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer;
    resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(1 * sizeof(int16_t));
    }
    int fcWeightOffset = 0;
    for (int i = 0; i < outChannels; i++) {
        int64_t temp = 0;
        for (int j = 0; j < inputChannels; j++) {
            for (int k = 0; k < inputChannels; k++) {
                temp += featureBuffer[j][k] *
                        fc[(i * outChannels) + (j * inputChannels) + k];
                fprintf(weightfp, "%d\n", fc[(i * outChannels) + (j * inputChannels) + k]);
                fprintf(inputfp, "%d\n", featureBuffer[j][k]);
            }
        }
        temp = latestChangeBit64(&temp, shiftBitCount);
        //    temp = valueOverflowCheck(&temp);
        resultBuffer[i][0] = (int16_t) temp;
    }
    return resultBuffer;
}

int16_t **fprintHexmyFC(int16_t **featureBuffer, int8_t *fc, int inputChannels, int outChannels, int shiftBitCount, FILE *weightfp, FILE *inputfp) {
    int16_t **resultBuffer;
    resultBuffer = (int16_t **) malloc(outChannels * sizeof(int16_t *));
    for (int i = 0; i < outChannels; i++) {
        resultBuffer[i] = (int16_t *) malloc(1 * sizeof(int16_t));
    }
    int fcWeightOffset = 0;
    for (int i = 0; i < outChannels; i++) {
        int64_t temp = 0;
        for (int j = 0; j < inputChannels; j++) {
            for (int k = 0; k < inputChannels; k++) {
                temp += featureBuffer[j][k] *
                        fc[(i * outChannels) + (j * inputChannels) + k];
                fprintf(weightfp, "%02x\n", fc[(i * outChannels) + (j * inputChannels) + k]);
                fprintf(inputfp, "%x\n", featureBuffer[j][k]);
            }
        }
        temp = latestChangeBit64(&temp, shiftBitCount);
        //    temp = valueOverflowCheck(&temp);
        resultBuffer[i][0] = (int16_t) temp;
    }
    return resultBuffer;
}

void ****freeMyLayerResult(int16_t ****pNetResults, int16_t ****rNetResults) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == 0) {
                if (j == 2) {
                    break;
                }
            }
            free(pNetResults[i][j]);
            free(rNetResults[i][j]);
        }
        free(pNetResults[i]);
        free(rNetResults[i]);
    }
    free(pNetResults);
    free(rNetResults);
}


//eujin functions
// 0: face exists
// 1: is face
// 2: x
// 3: y
// 4: width
// 5: height
// 6: 12x12 patch index

void ChangeCoordinatePnet(int16_t **arr, int type){
    float scale;
    int x_win, y_win;
    int max_index = arr[0][7];
    for(int i=0; i<max_index; i++){
        // original
        if(type == 1) {
            scale = 1.0;
            x_win = arr[i][6] % 31 * 2;
            y_win = (int)(arr[i][6] / 31) * 2;
        }
        // two third
        else if(type == 23){
            scale = 2.0/3.0;
            x_win = arr[i][6] % 19 * 2;
            y_win = (int)(arr[i][6] / 19) * 2;
        }// one half
        else if(type == 12){
            scale = 1.0/2.0;
            x_win = arr[i][6] % 13 * 2;
            y_win = (int)(arr[i][6] / 13) * 2;
        }
        arr[i][2] = (x_win + arr[i][2] * 12) / scale;
        arr[i][3] = (y_win + arr[i][3] * 12) / scale;
        arr[i][4] = arr[i][4] * 12 / scale;
        arr[i][5] = arr[i][5] * 12 / scale;

        arr[i][2] *= 12;
        arr[i][3] *= 12;
        arr[i][4] *= 12;
        arr[i][5] *= 12;

        arr[i][2] = arr[i][2]>>15;
        arr[i][3] = arr[i][3]>>15;
        arr[i][4] = arr[i][4]>>15;
        arr[i][5] = arr[i][5]>>15;
//        printf("%d, %d, %d, %d, %d, %d index: %d\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
    }
}


void ChangeCoordinateRnet(int16_t **rNet, int16_t **pNet){
    float scale;
    int x_win, y_win;
    int max_index = pNet[0][7];
    for(int i=0; i<96; i++){
        if(max_index>2000) scale = 1.0;
        else if(max_index>500) scale = 2.0/3.0;
        else scale = 1.0/2.0;

        x_win = pNet[i][2];
        y_win = pNet[i][3];

        rNet[i][2] = (x_win + rNet[i][2] * 24) / scale;
        rNet[i][3] = (y_win + rNet[i][3] * 24) / scale;
        rNet[i][4] = rNet[i][4] * 24 / scale;
        rNet[i][5] = rNet[i][5] * 24 / scale;
    }
}


// Delete if not in threshold
//int16_t **Threshold(int16_t **arr, int thres, int width, int height) {
//    int16_t **finalResults = (int16_t **) malloc(width * height * sizeof(int16_t *));
//    int max_index = sizeof(arr)/sizeof(int16_t *);
//
//    int16_t face_score;
//    int incr = 0;
//    for(int i=0; i<max_index; i++) {
//        face_score = arr[i][0];
//        if (face_score>=thres){
//            finalResults[incr] = arr[i];
//            incr+=1;
//        }
//    }
//    return finalResults;
//}

// fill with 0 if not in threshold
void ThresholdCheck(int16_t **pNetResults, int thres) {
    int max_index = sizeof(pNetResults)/sizeof(int16_t *);

    int16_t face_score;
    for(int i=0; i<pNetResults[0][7]; i++) {
        face_score = pNetResults[i][1];
        if (face_score<thres){
            pNetResults[i][0] = 0;
            pNetResults[i][1] = 0;
        }
    }
//    for(int j=0; j<max_index; j++) {
//        printf("%d %d\n", pNetResults[j][0], pNetResults[j][1]);
//    }
}

// fill scores with 0 if bounding box not in image

int16_t ** BoundingBoxCheck(int16_t **arr, int width, int height) {
    int16_t **results = (int16_t **)malloc(sizeof (int16_t *) * arr[0][7]);
    int new_x, new_y, new_w, new_h;

    for(int i=0; i<arr[0][7]; i++) {
//        printf("%d\n", i);
        new_x = arr[i][2];
        new_y = arr[i][3];
        new_w = arr[i][4];
        new_h = arr[i][5];
        if (new_x<0 || new_x>width || new_y<0 || new_y>height||(new_x+new_w)>width || (new_y+new_h)>height ||new_w<=0 ||new_h<=0) {
           results[i] = (int16_t *)malloc(sizeof(int16_t) * 8);
            results[i][7]=arr[0][7];
            results[i][0]=0;
            results[i][1]=0;
            results[i][2]=arr[i][2];
            results[i][3]=arr[i][3];
            results[i][4]=arr[i][4];
            results[i][5]=arr[i][5];
            results[i][6]=arr[i][6];
        }
        else{
            results[i] = (int16_t *)malloc(sizeof(int16_t) * 8);
            results[i][7]=arr[0][7];
            results[i][0]=arr[i][0];
            results[i][1]=arr[i][1];
            results[i][2]=arr[i][2];
            results[i][3]=arr[i][3];
            results[i][4]=arr[i][4];
            results[i][5]=arr[i][5];
            results[i][6]=arr[i][6];
        }
    }
    return results;
//    for(int j=0; j<max_index; j++) {
//        printf("%d %d\n", arr[j][0], arr[j][1]);
}