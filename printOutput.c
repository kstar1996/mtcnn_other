#include "printOutput.h"

void printInput(FILE **fp, int16_t *buffer, int height, int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(buffer[j + (i * height)]>=0){
                fprintf(fp[i%16], "%04x\n", buffer[j + (i * height)]);
            }
            else{
                fprintf(fp[i%16], "%04x\n", buffer[j + (i * height)]&0xFFFF);
            }
        }
        // fprintf(fp, "\n");
    }
    // fprintf(fp, "\n");
}

void printAfterConv(FILE **fp, int16_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int height, int width, int stride, int padding, int filterSize){
    int featureSize = (((width) - filterSize + (2 * padding)) / stride) + 1;
    if(filterOutChannels <= 16){
        for(int num = 0; num < filterInChannels; num++){
            for (int i = 0; i < filterOutChannels; i++) {
                for (int j = 0; j < featureSize; j++) {
                    for (int k = 0; k < featureSize; k++) {
                        if (convResultBuffer[num][i][(j * (height - 2)) + k] >= 0) {
                            fprintf(fp[i%16], "%04x\n", convResultBuffer[num][i][(j * (height - 2)) + k]);
                        } else {
                            fprintf(fp[i%16], "%04x\n", convResultBuffer[num][i][(j * (height - 2)) + k] & 0xFFFF);
                        }
                    }
                }
            }
        }
    }
    else{
        int outChannelQuotient = filterOutChannels / 16;
        int outChannelRemainder = filterOutChannels % 16;
        for(int split_index=0; split_index<outChannelQuotient; split_index++){
            for(int num = 0; num < filterInChannels; num++){
                for (int i=split_index*16; i < (split_index+1)*16; i++) {
                    for (int j = 0; j < featureSize; j++) {
                        for (int k = 0; k < featureSize; k++) {
                            if (convResultBuffer[num][i][(j * (height - 2)) + k] >= 0) {
                                fprintf(fp[i%16], "%04x\n", convResultBuffer[num][i][(j * (height - 2)) + k]);
                            } else {
                                fprintf(fp[i%16], "%04x\n", convResultBuffer[num][i][(j * (height - 2)) + k] & 0xFFFF);
                            }
                        }
                    }
                }
            }
        }
        if(outChannelRemainder>0){
            for(int num = 0; num < filterInChannels; num++){
                for (int i=outChannelQuotient*16; i < filterOutChannels; i++) {
                    for (int j = 0; j < featureSize; j++) {
                        for (int k = 0; k < featureSize; k++) {
                            if (convResultBuffer[num][i][(j * (height - 2)) + k] >= 0) {
                                fprintf(fp[i%16], "%04x\n", convResultBuffer[num][i][(j * (height - 2)) + k]);
                            } else {
                                fprintf(fp[i%16], "%04x\n", convResultBuffer[num][i][(j * (height - 2)) + k] & 0xFFFF);
                            }
                        }
                    }
                }
            }
        }
    }
}

void printDecAfterConv(FILE **fp, int16_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int height, int width, int stride, int padding, int filterSize){
    int featureSize = (((width) - filterSize + (2 * padding)) / stride) + 1;
    if(filterOutChannels <= 16){
        for(int num = 0; num < filterInChannels; num++){
            for (int i = 0; i < filterOutChannels; i++) {
                for (int j = 0; j < featureSize; j++) {
                    for (int k = 0; k < featureSize; k++) {
                        fprintf(fp[i%16], "%d\n", convResultBuffer[num][i][(j * (height - 2)) + k]);
                    }
                }
            }
        }
    }
    else{
        int outChannelQuotient = filterOutChannels / 16;
        int outChannelRemainder = filterOutChannels % 16;
        for(int split_index=0; split_index<outChannelQuotient; split_index++){
            for(int num = 0; num < filterInChannels; num++){
                for (int i=split_index*16; i < (split_index+1)*16; i++) {
                    for (int j = 0; j < featureSize; j++) {
                        for (int k = 0; k < featureSize; k++) {
                            fprintf(fp[i%16], "%d\n", convResultBuffer[num][i][(j * (height - 2)) + k]);
                        }
                    }
                }
            }
        }
        if(outChannelRemainder>0){
            for(int num = 0; num < filterInChannels; num++){
                for (int i=outChannelQuotient*16; i < filterOutChannels; i++) {
                    for (int j = 0; j < featureSize; j++) {
                        for (int k = 0; k < featureSize; k++) {
                            fprintf(fp[i%16], "%d\n", convResultBuffer[num][i][(j * (height - 2)) + k]);
                        }
                    }
                }
            }
        }
    }
}

void printAfter11Conv(FILE **fp, int64_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int stride, int padding, int filterSize){
    int featureSize = 1;
    for(int num = 0; num < filterInChannels; num++){
        for (int i = 0; i < filterOutChannels; i++) {
            for (int j = 0; j < featureSize; j++) {
                if (convResultBuffer[num][i][j] >= 0) {
                    fprintf(fp[i%16], "%016lx\n", convResultBuffer[num][i][j]);
                } else {
                    fprintf(fp[i%16], "%016lx\n", convResultBuffer[num][i][j] & 0xFFFFFFFFFFFFFFFF);
                }
            }
        }
    }
}

void printDecAfter11Conv(FILE **fp, int64_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int stride, int padding, int filterSize){
    int featureSize = 1;
    for(int num = 0; num < filterInChannels; num++){
        for (int i = 0; i < filterOutChannels; i++) {
            for (int j = 0; j < featureSize; j++) {
                fprintf(fp[i%16], "%ld\n", convResultBuffer[num][i][j]);
            }
        }
    }
}

void printAfterBias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width){
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            if (biasResult[i][j] >= 0) {
                fprintf(fp[i%16], "%04x\n", biasResult[i][j]);
            } else {
                fprintf(fp[i%16], "%04x\n", biasResult[i][j] & 0xFFFF);
            }
        }
    }
}

void printDecAfterBias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width){
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            fprintf(fp[i%16], "%d\n", biasResult[i][j]);
        }
    }
}

void printAfter11Bias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width){
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < 1; j++) {
            if (biasResult[i][j] >= 0) {
                fprintf(fp[16], "%04x", biasResult[i][j]);
            } else {
                fprintf(fp[16], "%04x", biasResult[i][j] & 0xFFFF);
            }
        }
    }
}

void printDecAfter11Bias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width){
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < 1; j++) {
            fprintf(fp[16], "%d", biasResult[i][j]);
        }
    }
}

void printAfterAct(FILE **fp, int16_t **actResult, int filterOutChannels, int height, int width){
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            if (actResult[i][j] >= 0) {
                fprintf(fp[i%16], "%04x\n", actResult[i][j]);
            } else {
                fprintf(fp[i%16], "%04x\n", actResult[i][j] & 0xFFFF);
            }
        }
    }
}

void printDecAfterAct(FILE **fp, int16_t **actResult, int filterOutChannels, int height, int width){
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < width * height; j++) {
            fprintf(fp[i%16], "%d\n", actResult[i][j]);
        }
    }
}

void printAfterMp(FILE **fp, int16_t **mpResult, int filterOutChannels, int height, int width, int kernelSize, int stride, int paddingSize){
    int mpOutSize = ((((width + paddingSize) - kernelSize) / stride) + 1);
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < mpOutSize; j++) {
            for (int k = 0; k < mpOutSize; k++) {
                if (mpResult[i][k + (j * mpOutSize)] >= 0) {
                    fprintf(fp[i%16], "%04x\n", mpResult[i][k + (j * mpOutSize)]);
                } else {
                    fprintf(fp[i%16], "%04x\n", mpResult[i][k + (j * mpOutSize)] & 0xFFFF);
                }
            }
        }
    }
}

void printDecAfterMp(FILE **fp, int16_t **mpResult, int filterOutChannels, int height, int width, int kernelSize, int stride, int paddingSize){
    int mpOutSize = ((((width + paddingSize) - kernelSize) / stride) + 1);
    for (int i = 0; i < filterOutChannels; i++) {
        for (int j = 0; j < mpOutSize; j++) {
            for (int k = 0; k < mpOutSize; k++) {
                fprintf(fp[i%16], "%d\n", mpResult[i][k + (j * mpOutSize)]);
            }
        }
    }
}

void printAfterFc(FILE **fp, int16_t **fcResult, int filterOutChannels){
    for (int i = 0; i < filterOutChannels; i++) {
        if (fcResult[i][0] >= 0) {
            fprintf(fp[i%16], "%04x\n", fcResult[i][0]);
        } else {
            fprintf(fp[i%16], "%04x\n", fcResult[i][0] & 0xFFFF);
        }
    }
}

void printDecAfterFc(FILE **fp, int16_t **fcResult, int filterOutChannels){
    for (int i = 0; i < filterOutChannels; i++) {
        fprintf(fp[i%16], "%d\n", fcResult[i][0]);
    }
}

void printAfterFcBias(FILE **fp, int16_t **biasResult, int filterOutChannels){
    for (int i = 0; i < filterOutChannels; i++) {
        if (biasResult[i][0] >= 0) {
            fprintf(fp[i%16], "%04x\n", biasResult[i][0]);
        } else {
            fprintf(fp[i%16], "%04x\n", biasResult[i][0] & 0x0FFFF);
        }
    }
}

void printDecAfterFcBias(FILE **fp, int16_t **biasResult, int filterOutChannels){
    for (int i = 0; i < filterOutChannels; i++) {
        fprintf(fp[i%16], "%d\n", biasResult[i][0]);
    }
}

void printAfterFcBiasOut(FILE **fp, int16_t **biasResult, int filterOutChannels){
    for (int i = 0; i < filterOutChannels; i++) {
        if (biasResult[i][0] >= 0) {
            fprintf(fp[16], "%04x", biasResult[i][0]);
        } else {
            fprintf(fp[16], "%04x", biasResult[i][0] & 0x0FFFF);
        }
    }
}

void printDecAfterFcBiasOut(FILE **fp, int16_t **biasResult, int filterOutChannels){
    for (int i = 0; i < filterOutChannels; i++) {
        fprintf(fp[16], "%d\n", biasResult[i][0]);
    }
}

void printPnet(FILE **fp, int width, int height, int16_t *Rbuffer, int16_t *Gbuffer, int16_t *Bbuffer, WeightValue *weightValue,
               int16_t ***rgbResultBuffer, int16_t **bias1Result, int16_t **act1Result, int16_t **mp1Result,
               int16_t ***conv2ResultBuffer, int16_t **bias2Result, int16_t **act2Result,
               int16_t ***conv3ResultBuffer, int16_t **bias3Result, int16_t **act3Result,
               int64_t ***conv4ResultBuffer, int16_t **bias4Result, int64_t ***conv5ResultBuffer, int16_t **bias5Result){
    // fprintf(fp, "Raw image ========================================================\n");
//     printInput(fp, Rbuffer, height, width);

    // printInput(fp, Gbuffer, height, width);

    // printInput(fp, Bbuffer, height, width);


    // fprintf(fp, "After conv1 =========================================================\n");
    int stride = 1;
    int padding = 0;
    int filterSize = 3;
    printAfterConv(fp, rgbResultBuffer, 3, weightValue->pnetWeightValue->filterOutChannels1, height, width, stride, padding, filterSize);
    // printDecAfterConv(fp, rgbResultBuffer, 3, weightValue->pnetWeightValue->filterOutChannels1, height, width, stride, padding, filterSize);

    // fprintf(fp, "After bias1 =========================================================\n");
    width = 10;
    height = 10;
//    printAfterBias(fp, bias1Result, weightValue->pnetWeightValue->filterOutChannels1, height, width);
    // printDecAfterBias(fp, bias1Result, weightValue->pnetWeightValue->filterOutChannels1, height, width);

    // fprintf(fp, "After act1 =========================================================\n");
    width = 10;
    height = 10;
//    printAfterAct(fp, act1Result, weightValue->pnetWeightValue->filterOutChannels1, height, width);
    // printDecAfterAct(fp, act1Result, weightValue->pnetWeightValue->filterOutChannels1, height, width);

    // fprintf(fp, "After mp1 =========================================================\n");
    width = 10;
    height = 10;
    int kernelSize = 2;
    stride = 2;
    int paddingSize = 0;
//    printAfterMp(fp, mp1Result, weightValue->pnetWeightValue->filterOutChannels1, height, width, kernelSize, stride, paddingSize);
    // printDecAfterMp(fp, mp1Result, weightValue->pnetWeightValue->filterOutChannels1, height, width, kernelSize, stride, paddingSize);


    // fprintf(fp, "After conv2 =========================================================\n");
    stride = 1;
    padding = 0;
    filterSize = 3;
    width = 5;
    height = 5;
    printAfterConv(fp, conv2ResultBuffer, weightValue->pnetWeightValue->filterOutChannels1, weightValue->pnetWeightValue->filterOutChannels2, height, width, stride, padding, filterSize);
    // printDecAfterConv(fp, conv2ResultBuffer, weightValue->pnetWeightValue->filterOutChannels1, weightValue->pnetWeightValue->filterOutChannels2, height, width, stride, padding, filterSize);

    // fprintf(fp, "After bias2 =========================================================\n");
    width = 3;
    height = 3;
//    printAfterBias(fp, bias2Result, weightValue->pnetWeightValue->filterOutChannels2, height, width);
    // printDecAfterBias(fp, bias2Result, weightValue->pnetWeightValue->filterOutChannels2, height, width);

    // fprintf(fp, "After act2 =========================================================\n");
    width = 3;
    height = 3;
//    printAfterAct(fp, act2Result, weightValue->pnetWeightValue->filterOutChannels2, height, width);
    // printDecAfterAct(fp, act2Result, weightValue->pnetWeightValue->filterOutChannels2, height, width);


    // fprintf(fp, "After conv3 =========================================================\n");
    filterSize = 3;
    stride = 1;
    padding = 0;
    width = 3;
    height = 3;
    printAfterConv(fp, conv3ResultBuffer, weightValue->pnetWeightValue->filterOutChannels2, weightValue->pnetWeightValue->filterOutChannels3, height, width, stride, padding, filterSize);
    // printDecAfterConv(fp, conv3ResultBuffer, weightValue->pnetWeightValue->filterOutChannels2, weightValue->pnetWeightValue->filterOutChannels3, height, width, stride, padding, filterSize);

    // fprintf(fp, "After bias3 =========================================================\n");
    width = 1;
    height = 1;
//    printAfterBias(fp, bias3Result, weightValue->pnetWeightValue->filterOutChannels3, height, width);
    // printDecAfterBias(fp, bias3Result, weightValue->pnetWeightValue->filterOutChannels3, height, width);

    // fprintf(fp, "After act3 =========================================================\n");
    width = 1;
    height = 1;
//    printAfterAct(fp, act3Result, weightValue->pnetWeightValue->filterOutChannels3, height, width);
    // printDecAfterAct(fp, act3Result, weightValue->pnetWeightValue->filterOutChannels3, height, width);


    // fprintf(fp, "After conv4 =========================================================\n");
    filterSize = 1;
    stride = 1;
    padding = 0;
//    printAfter11Conv(fp, conv4ResultBuffer, weightValue->pnetWeightValue->filterOutChannels3, weightValue->pnetWeightValue->filterOutChannels4, stride, padding, filterSize);
    // printDecAfter11Conv(fp, conv4ResultBuffer, weightValue->pnetWeightValue->filterOutChannels3, weightValue->pnetWeightValue->filterOutChannels4, stride, padding, filterSize);

    // fprintf(fp, "After bias4 =========================================================\n");
//    fprintf(fp[16], "00000000");
    width = 1;
    height = 1;
//    printAfter11Bias(fp, bias4Result, weightValue->pnetWeightValue->filterOutChannels4, height, width);
    // printDecAfter11Bias(fp, bias4Result, weightValue->pnetWeightValue->filterOutChannels4, height, width);


    // fprintf(fp, "After conv5 =========================================================\n");
    filterSize = 1;
    stride = 1;
    padding = 0;
//    printAfter11Conv(fp, conv5ResultBuffer, weightValue->pnetWeightValue->filterOutChannels4, weightValue->pnetWeightValue->filterOutChannels5, stride, padding, filterSize);
    // printDecAfter11Conv(fp, conv5ResultBuffer, weightValue->pnetWeightValue->filterOutChannels4, weightValue->pnetWeightValue->filterOutChannels5, stride, padding, filterSize);

    // fprintf(fp, "After bias5 =========================================================\n");
    width = 1;
    height = 1;
//    printAfter11Bias(fp, bias5Result, weightValue->pnetWeightValue->filterOutChannels5, height, width);
    // printDecAfter11Bias(fp, bias5Result, weightValue->pnetWeightValue->filterOutChannels5, height, width);
//    fprintf(fp[16], "\n");
}

void printRnet(FILE **fp, int width, int height, int16_t *Rbuffer, int16_t *Gbuffer, int16_t *Bbuffer, WeightValue *weightValue,
               int16_t ***rgbResultBuffer, int16_t **bias1Result, int16_t **act1Result, int16_t **mp1Result,
               int16_t ***conv2ResultBuffer, int16_t **bias2Result, int16_t **act2Result, int16_t **mp2Result,
               int16_t ***conv3ResultBuffer, int16_t **bias3Result, int16_t **act3Result,
               int16_t **fc1Result, int16_t **bias4Result, int16_t **act4Result,
               int16_t **fc2Result, int16_t **bias5Result, int16_t **fc3Result, int16_t **bias6Result){
    // fprintf(fp, "Raw image ========================================================\n");
     printInput(fp, Rbuffer, height, width);

    // printInput(fp, Gbuffer, height, width);

    // printInput(fp, Bbuffer, height, width);


    // fprintf(fp, "After conv1 =========================================================\n");
    int stride = 1;
    int padding = 0;
    int filterSize = 3;
    // int mpPadding = 0;
    width = 24;
    height = 24;
//    printAfterConv(fp, rgbResultBuffer, 3, weightValue->rnetWeightValue->filterOutChannels1, height, width, stride, padding, filterSize);
    // printDecAfterConv(fp, rgbResultBuffer, 3, weightValue->rnetWeightValue->filterOutChannels1, height, width, stride, padding, filterSize);

    // fprintf(fp, "After bias1 =========================================================\n");
    width = 22;
    height = 22;
//    printAfterBias(fp, bias1Result, weightValue->rnetWeightValue->filterOutChannels1, height, width);
    // printDecAfterBias(fp, bias1Result, weightValue->rnetWeightValue->filterOutChannels1, height, width);

    // fprintf(fp, "After act1 =========================================================\n");
    width = 22;
    height = 22;
//    printAfterAct(fp, act1Result, weightValue->rnetWeightValue->filterOutChannels1, height, width);
    // printDecAfterAct(fp, act1Result, weightValue->rnetWeightValue->filterOutChannels1, height, width);

    // fprintf(fp, "After mp1 =========================================================\n");
    width = 22;
    height = 22;
    int kernelSize = 2;
    stride = 2;
    int paddingSize = 0;
//    printAfterMp(fp, mp1Result, weightValue->rnetWeightValue->filterOutChannels1, height, width, kernelSize, stride, paddingSize);
    // printDecAfterMp(fp, mp1Result, weightValue->rnetWeightValue->filterOutChannels1, height, width, kernelSize, stride, paddingSize);


    // fprintf(fp, "After conv2 =========================================================\n");
    stride = 1;
    padding = 0;
    filterSize = 3;
    width = 11;
    height = 11;
//    printAfterConv(fp, conv2ResultBuffer, weightValue->rnetWeightValue->filterOutChannels1, weightValue->rnetWeightValue->filterOutChannels2, height, width, stride, padding, filterSize);
    // printDecAfterConv(fp, conv2ResultBuffer, weightValue->rnetWeightValue->filterOutChannels1, weightValue->rnetWeightValue->filterOutChannels2, height, width, stride, padding, filterSize);

    // fprintf(fp, "After bias2 =========================================================\n");
    width = 9;
    height = 9;
//    printAfterBias(fp, bias2Result, weightValue->rnetWeightValue->filterOutChannels2, height, width);
    // printDecAfterBias(fp, bias2Result, weightValue->rnetWeightValue->filterOutChannels2, height, width);

    // fprintf(fp, "After act2 =========================================================\n");
    width = 9;
    height = 9;
//    printAfterAct(fp, act2Result, weightValue->rnetWeightValue->filterOutChannels2, height, width);
    // printDecAfterAct(fp, act2Result, weightValue->rnetWeightValue->filterOutChannels2, height, width);

//    printInput(fp, mp2Result, height, width);
    // fprintf(fp, "After mp2 =========================================================\n");
    width = 9;
    height = 9;
    kernelSize = 2;
    stride = 2;
    paddingSize = 1;
//    printAfterMp(fp, mp2Result, weightValue->rnetWeightValue->filterOutChannels2, height, width, kernelSize, stride, paddingSize);
    // printDecAfterMp(fp, mp2Result, weightValue->rnetWeightValue->filterOutChannels2, height, width, kernelSize, stride, paddingSize);


    // fprintf(fp, "After conv3 =========================================================\n");
    stride = 1;
    padding = 0;
    filterSize = 3;
    width = 5;
    height = 5;
//    printAfterConv(fp, conv3ResultBuffer, weightValue->rnetWeightValue->filterOutChannels2, weightValue->rnetWeightValue->filterOutChannels3, height, width, stride, padding, filterSize);
    // printDecAfterConv(fp, conv3ResultBuffer, weightValue->rnetWeightValue->filterOutChannels2, weightValue->rnetWeightValue->filterOutChannels3, height, width, stride, padding, filterSize);

    // fprintf(fp, "After bias3 =========================================================\n");
    width = 3;
    height = 3;
//    printAfterBias(fp, bias3Result, weightValue->rnetWeightValue->filterOutChannels3, height, width);
    // printDecAfterBias(fp, bias3Result, weightValue->rnetWeightValue->filterOutChannels3, height, width);

    // fprintf(fp, "After act3 =========================================================\n");
    width = 3;
    height = 3;
//    printAfterAct(fp, act3Result, weightValue->rnetWeightValue->filterOutChannels3, height, width);
    // printDecAfterAct(fp, act3Result, weightValue->rnetWeightValue->filterOutChannels3, height, width);


    // fprintf(fp, "After fc1 =========================================================\n");
//    printAfterFc(fp, fc1Result, weightValue->rnetWeightValue->fcOutChannels1);
    // printDecAfterFc(fp, fc1Result, weightValue->rnetWeightValue->fcOutChannels1);

    // fprintf(fp, "After bias4 =========================================================\n");
//    printAfterFcBias(fp, bias4Result, weightValue->rnetWeightValue->fcOutChannels1);
    // printDecAfterFcBias(fp, bias4Result, weightValue->rnetWeightValue->fcOutChannels1);


    // fprintf(fp, "After act4 =========================================================\n");
    width = 1;
    height = 1;
//    printAfterAct(fp, act4Result, weightValue->rnetWeightValue->fcOutChannels1, height, width);
    // printDecAfterAct(fp, act4Result, weightValue->rnetWeightValue->fcOutChannels1, height, width);


    // fprintf(fp, "After fc2 =========================================================\n");
//    printAfterFc(fp, fc2Result, weightValue->rnetWeightValue->fcOutChannels2);
    // printDecAfterFc(fp, fc2Result, weightValue->rnetWeightValue->fcOutChannels2);

    // fprintf(fp, "After bias5 =========================================================\n");
//    fprintf(fp[16], "00000000");
//    printAfterFcBiasOut(fp, bias5Result, weightValue->rnetWeightValue->fcOutChannels2);
    // printDecAfterFcBiasOut(fp, bias5Result, weightValue->rnetWeightValue->fcOutChannels2);


    // fprintf(fp, "After fc3 =========================================================\n");
//    printAfterFc(fp, fc3Result, weightValue->rnetWeightValue->fcOutChannels3);
    // printDecAfterFc(fp, fc3Result, weightValue->rnetWeightValue->fcOutChannels3);

    // fprintf(fp, "After bias6 =========================================================\n");
//    printAfterFcBiasOut(fp, bias6Result, weightValue->rnetWeightValue->fcOutChannels3);
    // printDecAfterFcBiasOut(fp, bias6Result, weightValue->rnetWeightValue->fcOutChannels3);
//    fprintf(fp[16], "\n");
}