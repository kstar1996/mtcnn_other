//
// Created by Eujin Kim on 28/09/2021.
//

#include "loadWeightFile.h"

uint8_t swapValue(uint8_t value) {
    uint8_t returnValue;
    switch (value) {
        case '0':
            returnValue = 0;
            break;
        case '1':
            returnValue = 1;
            break;
        case '2':
            returnValue = 2;
            break;
        case '3':
            returnValue = 3;
            break;
        case '4':
            returnValue = 4;
            break;
        case '5':
            returnValue = 5;
            break;
        case '6':
            returnValue = 6;
            break;
        case '7':
            returnValue = 7;
            break;
        case '8':
            returnValue = 8;
            break;
        case '9':
            returnValue = 9;
            break;
        case 'A':
            returnValue = 10;
            break;
        case 'B':
            returnValue = 11;
            break;
        case 'C':
            returnValue = 12;
            break;
        case 'D':
            returnValue = 13;
            break;
        case 'E':
            returnValue = 14;
            break;
        case 'F':
            returnValue = 15;
            break;
        default:
            break;
    }
    return returnValue;

}

void reverseBuffer(uint8_t *buffer, int size){
    uint8_t *tempBuffer = (uint8_t *) malloc(size * sizeof(uint8_t));
    for(int return_i=0, target_i=size-1; return_i<size; return_i++, target_i--){
        tempBuffer[return_i] = buffer[target_i];
    }
    for(int i=0; i<size; i++){
        buffer[i] = tempBuffer[i];
    }
}

LoadFileStruct loadWeightFile(char *filePath) {
    LoadFileStruct lfs;
    int lineSize = 33;
    uint8_t *fileBuffer;
    FILE *fp = fopen(filePath, "r");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fileBuffer = (uint8_t *) malloc(size * sizeof(uint8_t));
    int count = 0;
    int valueCount = 0;
    fseek(fp, 0, SEEK_SET);
    while (1) {
        uint8_t *buffer = (uint8_t *) malloc(lineSize * sizeof(uint8_t));
        int checkFlag = fscanf(fp, "%s", buffer);
        if (checkFlag != 1) {
            break;
        }
        for (int i = 0, j = lineSize - 2; j >= 0 ; i++, j--) {
            fileBuffer[count * (lineSize - 1) + i] = swapValue(buffer[j]);
            valueCount++;
        }
        free(buffer);
        count++;
    }
    // uint8_t *fileBufferCopy = (uint8_t *) malloc(size * sizeof(uint8_t));
    // reverseBuffer(fileBuffer, size);
    // printf("test: %d\t%d\t%d\t%d\t%d\n", fileBufferCopy[0], fileBufferCopy[1], fileBufferCopy[2], fileBufferCopy[3], fileBufferCopy[4]);
    lfs.fileSize = valueCount;
    lfs.fileBuffer = (uint8_t *) malloc(valueCount * sizeof(uint8_t));
    memcpy(lfs.fileBuffer, fileBuffer, valueCount);
    // free(fileBufferCopy);
    free(fileBuffer);

    return lfs;
}

int8_t *mergeWeight(uint8_t *weightBuffer, int weightBufferSize) {
    // weightBufferSize = 32;
    int8_t *resultBuffer = (int8_t *) malloc((weightBufferSize / 2) * sizeof(int8_t));
    int count=0;
    for (int i = 0; i < (weightBufferSize / 2); i++) {
        int8_t v2 = (int8_t) weightBuffer[i * 2];
        int8_t v1 = (int8_t) weightBuffer[i * 2 + 1];
        int8_t temp = (v1 << 4) | v2;

        resultBuffer[i] = temp;
        count++;
    }
    return resultBuffer;
}

void initPnetWeightMemory(WeightValue *weightValue) {
    weightValue->pnetWeightValue = (PnetWeightValue *) malloc(sizeof(PnetWeightValue));
    weightValue->pnetWeightValue->filterNumberConv1 = 8;
    //changed
    weightValue->pnetWeightValue->filterOutChannels1 = 8;

    weightValue->pnetWeightValue->conv1R = (int8_t **) malloc(
            (weightValue->pnetWeightValue->filterNumberConv1) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv1; i++) {
        weightValue->pnetWeightValue->conv1R[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->pnetWeightValue->conv1G = (int8_t **) malloc(
            (weightValue->pnetWeightValue->filterNumberConv1) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv1; i++) {
        weightValue->pnetWeightValue->conv1G[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->pnetWeightValue->conv1B = (int8_t **) malloc(
            (weightValue->pnetWeightValue->filterNumberConv1) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv1; i++) {
        weightValue->pnetWeightValue->conv1B[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->pnetWeightValue->bias1 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels1) * sizeof(int8_t));
    weightValue->pnetWeightValue->act1 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels1) * sizeof(int8_t));


    weightValue->pnetWeightValue->filterNumberConv2 = 128;
    // changed
    weightValue->pnetWeightValue->filterOutChannels2 = 16;
    weightValue->pnetWeightValue->conv2 = (int8_t **) malloc(
            (weightValue->pnetWeightValue->filterNumberConv2) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv2; i++) {
        weightValue->pnetWeightValue->conv2[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->pnetWeightValue->bias2 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels2) * sizeof(int8_t));
    weightValue->pnetWeightValue->act2 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels2) * sizeof(int8_t));


    weightValue->pnetWeightValue->filterNumberConv3 = 512;
    //changed
    weightValue->pnetWeightValue->filterOutChannels3 = 32;
    weightValue->pnetWeightValue->conv3 = (int8_t **) malloc(
            (weightValue->pnetWeightValue->filterNumberConv3) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv3; i++) {
        weightValue->pnetWeightValue->conv3[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->pnetWeightValue->bias3 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels3) * sizeof(int8_t));
    weightValue->pnetWeightValue->act3 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels3) * sizeof(int8_t));


    weightValue->pnetWeightValue->filterNumberConv4 = 64;
    weightValue->pnetWeightValue->filterOutChannels4 = 2;
    weightValue->pnetWeightValue->conv4 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterNumberConv4) * sizeof(int8_t));
    weightValue->pnetWeightValue->bias4 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels4) * sizeof(int8_t));


    weightValue->pnetWeightValue->filterNumberConv5 = 128;
    weightValue->pnetWeightValue->filterOutChannels5 = 4;
    weightValue->pnetWeightValue->conv5 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterNumberConv5) * sizeof(int8_t ));

    weightValue->pnetWeightValue->bias5 = (int8_t *) malloc(
            (weightValue->pnetWeightValue->filterOutChannels5) * sizeof(int8_t));
}

void initRnetWeightMemory(WeightValue *weightValue) {
    weightValue->rnetWeightValue = (RnetWeightValue *) malloc(sizeof(RnetWeightValue));
    weightValue->rnetWeightValue->filterNumberConv1 = 28;
    weightValue->rnetWeightValue->filterOutChannels1 = 28;
    weightValue->rnetWeightValue->conv1R = (int8_t **) malloc(
            (weightValue->rnetWeightValue->filterNumberConv1) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv1; i++) {
        weightValue->rnetWeightValue->conv1R[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->rnetWeightValue->conv1G = (int8_t **) malloc(
            (weightValue->rnetWeightValue->filterNumberConv1) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv1; i++) {
        weightValue->rnetWeightValue->conv1G[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->rnetWeightValue->conv1B = (int8_t **) malloc(
            (weightValue->rnetWeightValue->filterNumberConv1) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv1; i++) {
        weightValue->rnetWeightValue->conv1B[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->rnetWeightValue->bias1 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->filterOutChannels1) * sizeof(int8_t));
    weightValue->rnetWeightValue->act1 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->filterOutChannels1) * sizeof(int8_t));


    weightValue->rnetWeightValue->filterNumberConv2 = 1344;
    weightValue->rnetWeightValue->filterOutChannels2 = 48;
    weightValue->rnetWeightValue->conv2 = (int8_t **) malloc(
            (weightValue->rnetWeightValue->filterNumberConv2) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv2; i++) {
        weightValue->rnetWeightValue->conv2[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->rnetWeightValue->bias2 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->filterOutChannels2) * sizeof(int8_t));
    weightValue->rnetWeightValue->act2 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->filterOutChannels2) * sizeof(int8_t));


    weightValue->rnetWeightValue->filterNumberConv3 = 3072;
    weightValue->rnetWeightValue->filterOutChannels3 = 64;
    weightValue->rnetWeightValue->conv3 = (int8_t **) malloc(
            (weightValue->rnetWeightValue->filterNumberConv3) * sizeof(int8_t *));
    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv3; i++) {
        weightValue->rnetWeightValue->conv3[i] = (int8_t *) malloc((9) * sizeof(int8_t));
    }
    weightValue->rnetWeightValue->bias3 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->filterOutChannels3) * sizeof(int8_t));
    weightValue->rnetWeightValue->act3 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->filterOutChannels3) * sizeof(int8_t));


    weightValue->rnetWeightValue->fcNumber1 = 73728;
    weightValue->rnetWeightValue->fcOutChannels1 = 128;
    weightValue->rnetWeightValue->fc1 = (int8_t *) malloc((weightValue->rnetWeightValue->fcNumber1) * sizeof(int8_t));
    weightValue->rnetWeightValue->bias4 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->fcOutChannels1) * sizeof(int8_t));
    weightValue->rnetWeightValue->act4 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->fcOutChannels1) * sizeof(int8_t));


    weightValue->rnetWeightValue->fcNumber2 = 256;
    weightValue->rnetWeightValue->fcOutChannels2 = 2;
    weightValue->rnetWeightValue->fc2 = (int8_t *) malloc((weightValue->rnetWeightValue->fcNumber2) * sizeof(int8_t));
    weightValue->rnetWeightValue->bias5 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->fcOutChannels2) * sizeof(int8_t));


    weightValue->rnetWeightValue->fcNumber3 = 512;
    weightValue->rnetWeightValue->fcOutChannels3 = 4;
    weightValue->rnetWeightValue->fc3 = (int8_t *) malloc((weightValue->rnetWeightValue->fcNumber3) * sizeof(int8_t));
    weightValue->rnetWeightValue->bias6 = (int8_t *) malloc(
            (weightValue->rnetWeightValue->fcOutChannels3) * sizeof(int8_t));

}

WeightValue *initWeightMemory() {

    WeightValue *weightValue = (WeightValue *) malloc(sizeof(weightValue));
    initPnetWeightMemory(weightValue);
    initRnetWeightMemory(weightValue);

    return weightValue;
}

void freeWeightValue(WeightValue *weightValue) {

    //pnet
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv1; i++) {
        free(weightValue->pnetWeightValue->conv1R[i]);
        free(weightValue->pnetWeightValue->conv1G[i]);
        free(weightValue->pnetWeightValue->conv1B[i]);
    }
    free(weightValue->pnetWeightValue->conv1R);
    free(weightValue->pnetWeightValue->conv1G);
    free(weightValue->pnetWeightValue->conv1B);


    free(weightValue->pnetWeightValue->bias1);
    free(weightValue->pnetWeightValue->act1);


    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv2; i++) {
        free(weightValue->pnetWeightValue->conv2[i]);
    }
    free(weightValue->pnetWeightValue->conv2);
    free(weightValue->pnetWeightValue->bias2);
    free(weightValue->pnetWeightValue->act2);


    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv3; i++) {
        free(weightValue->pnetWeightValue->conv3[i]);
    }
    free(weightValue->pnetWeightValue->conv3);
    free(weightValue->pnetWeightValue->bias3);
    free(weightValue->pnetWeightValue->act3);


    free(weightValue->pnetWeightValue->conv4);
    free(weightValue->pnetWeightValue->bias4);



    free(weightValue->pnetWeightValue->conv5);
    free(weightValue->pnetWeightValue->bias5);

    free(weightValue->pnetWeightValue);


    //Rnet
    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv1; i++) {
        free(weightValue->rnetWeightValue->conv1R[i]);
        free(weightValue->rnetWeightValue->conv1G[i]);
        free(weightValue->rnetWeightValue->conv1B[i]);
    }
    free(weightValue->rnetWeightValue->conv1R);
    free(weightValue->rnetWeightValue->conv1G);
    free(weightValue->rnetWeightValue->conv1B);
    free(weightValue->rnetWeightValue->bias1);
    free(weightValue->rnetWeightValue->act1);


    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv2; i++) {
        free(weightValue->rnetWeightValue->conv2[i]);
    }
    free(weightValue->rnetWeightValue->conv2);
    free(weightValue->rnetWeightValue->bias2);
    free(weightValue->rnetWeightValue->act2);


    for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv3; i++) {
        free(weightValue->rnetWeightValue->conv3[i]);
    }
    free(weightValue->rnetWeightValue->conv3);
    free(weightValue->rnetWeightValue->bias3);
    free(weightValue->rnetWeightValue->act3);


    free(weightValue->rnetWeightValue->fc1);
    free(weightValue->rnetWeightValue->bias4);
    free(weightValue->rnetWeightValue->act4);


    free(weightValue->rnetWeightValue->fc2);
    free(weightValue->rnetWeightValue->bias5);


    free(weightValue->rnetWeightValue->fc3);
    free(weightValue->rnetWeightValue->bias6);

    free(weightValue->rnetWeightValue);

    //all
    free(weightValue);
}

void insertPnetValueWeightBuffer(int8_t **sramBuffer, WeightValue *weightValue, int *offset) {

    //conv1
    //sram4
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv1; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->pnetWeightValue->conv1R[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv1; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->pnetWeightValue->conv1G[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv1; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->pnetWeightValue->conv1B[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }

    //0val
    offset[0] += 8;

    //sram6
    // 8 16 32 2 4

    //changed
    int switchTemp = 1;
    int conv1BiasActTotal = weightValue->pnetWeightValue->filterOutChannels1*2;
    for(int i=0, bias_i=0, act_i=0; i<conv1BiasActTotal; i++){
        if(switchTemp){
            weightValue->pnetWeightValue->bias1[bias_i] = sramBuffer[2][offset[2]];
            bias_i++;       // 스위치 하면서 값을 써주므로 bias, act 따로 인덱스 관리 필요
        }
        else{
            weightValue->pnetWeightValue->act1[act_i] = sramBuffer[2][offset[2]];
            act_i++;        // 스위치 하면서 값을 써주므로 bias, act 따로 인덱스 관리 필요
        }
        if(i%4==3){     // 4개씩 로드 후 bias <-> act 스위치
            switchTemp = !switchTemp;
        }
        offset[2]++;
    }


    //conv2
    //sram4
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv2; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->pnetWeightValue->conv2[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }

    //sram6
    // filterOutChannels2 = 16
    //changed
    switchTemp = 1;
    int conv2BiasActTotal = weightValue->pnetWeightValue->filterOutChannels2*2;
    for(int i=0, bias_i=0, act_i=0; i<conv2BiasActTotal; i++){
        if(switchTemp){
            weightValue->pnetWeightValue->bias2[bias_i] = sramBuffer[2][offset[2]];
            bias_i++;       // 스위치 하면서 값을 써주므로 bias, act 따로 인덱스 관리 필요
        }
        else{
            weightValue->pnetWeightValue->act2[act_i] = sramBuffer[2][offset[2]];
            act_i++;        // 스위치 하면서 값을 써주므로 bias, act 따로 인덱스 관리 필요
        }
        if(i%4==3){     // 4개씩 로드 후 bias <-> act 스위치
            switchTemp = !switchTemp;
        }
        offset[2]++;
    }

    //conv3
    //sram4
    int pnetConv3OffsetTemp = 0;
    for (int i = 0; i < weightValue->pnetWeightValue->filterNumberConv3; i++) {
        if(i==(weightValue->pnetWeightValue->filterNumberConv3/2))  pnetConv3OffsetTemp = 16;       // 다시 0번째로 돌아올 때 0~15 인덱스는 값을 써줬으므로 16부터 값을 쓰기 위한 오프셋 초기화
        if(i < (weightValue->pnetWeightValue->filterNumberConv3/2)){        // 절반까지는 16번째마다 점프해가며 값을 쓰다가 절반이 지난 후부터 나머지 반의 값을 씀 (ex. 0~15 -> 32~47 -> 64~79 ...)
            for (int j = 0; j < 9; j++) {
                weightValue->pnetWeightValue->conv3[i+pnetConv3OffsetTemp][j] = sramBuffer[0][offset[0]];
                offset[0]++;
            }
            if(i%16==15){       // 16개 값을 채울 때마다 오프셋 증가시켜 17번째 필터가 아닌 다음 채널 필터 값을 써줌
                pnetConv3OffsetTemp += 16;      // weight input first 16 every channel
            }
        }
        else{       // ex. 16~31 -> 48~63 -> 80~95 ...
            for (int j = 0; j < 9; j++) {       // -256으로 다시 0부터 값을 써주는데 오프셋이 16이므로 16번째 인덱스부터 값을 씀
                weightValue->pnetWeightValue->conv3[i-256+pnetConv3OffsetTemp][j] = sramBuffer[0][offset[0]];
                offset[0]++;
            }
            if(i%16==15){
                pnetConv3OffsetTemp += 16;      // weight input last 16 every channel
            }
        }
    }

    //sram6
    // filterOutChannels3 = 32
    //changed
    switchTemp = 1;
    int conv3BiasActTotal = weightValue->pnetWeightValue->filterOutChannels3*2;
    for(int i=0, bias_i=0, act_i=0; i<conv3BiasActTotal; i++){
        if(switchTemp){
            weightValue->pnetWeightValue->bias3[bias_i] = sramBuffer[2][offset[2]];
            bias_i++;
        }
        else{
            weightValue->pnetWeightValue->act3[act_i] = sramBuffer[2][offset[2]];
            act_i++;
        }
        if(i%4==3){
            switchTemp = !switchTemp;
        }
        offset[2]++;
    }

    //conv4
    //sram4
    for(int i = 0 ; i < weightValue->pnetWeightValue->filterNumberConv4 ; i++){
        weightValue->pnetWeightValue->conv4[i] = sramBuffer[0][offset[0]];
        offset[0]++;
    }

    //sram6
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels4; i++) {
        weightValue->pnetWeightValue->bias4[i] = sramBuffer[2][offset[2]];
        offset[2]++;
    }


    //conv5
    //sram4
    for(int i = 0 ; i < weightValue->pnetWeightValue->filterNumberConv5 ; i++){
        weightValue->pnetWeightValue->conv5[i] = sramBuffer[0][offset[0]];
        offset[0]++;
    }

    //sram6
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels5; i++) {
        weightValue->pnetWeightValue->bias5[i] = sramBuffer[2][offset[2]];
        offset[2]++;
    }

    //0val
    offset[2] += 10;

}

void insertRnetValueWeightBuffer(int8_t **sramBuffer, WeightValue *weightValue, int *offset) {


    //conv1
    //sram4
    // for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv1; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         weightValue->rnetWeightValue->conv1R[i][j] = sramBuffer[0][offset[0]];
    //         offset[0]++;
    //     }
    // }
    // for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv1; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         weightValue->rnetWeightValue->conv1G[i][j] = sramBuffer[0][offset[0]];
    //         offset[0]++;
    //     }
    // }
    // for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv1; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         weightValue->rnetWeightValue->conv1B[i][j] = sramBuffer[0][offset[0]];
    //         offset[0]++;
    //     }
    // }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->rnetWeightValue->conv1R[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->rnetWeightValue->conv1G[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->rnetWeightValue->conv1B[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }
    for (int i = 16; i < 28; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->rnetWeightValue->conv1R[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }
    for (int i = 16; i < 28; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->rnetWeightValue->conv1G[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }
    for (int i = 16; i < 28; i++) {
        for (int j = 0; j < 9; j++) {
            weightValue->rnetWeightValue->conv1B[i][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
    }

    //0val
    offset[0] += 28;

    //sram6
    int switchTemp = 1;
    int conv1BiasActTotal = weightValue->rnetWeightValue->filterOutChannels1*2;
    for(int i=0, bias_i=0, act_i=0; i<conv1BiasActTotal; i++){
        if(switchTemp){
            weightValue->rnetWeightValue->bias1[bias_i] = sramBuffer[2][offset[2]];
            bias_i++;
        }
        else{
            weightValue->rnetWeightValue->act1[act_i] = sramBuffer[2][offset[2]];
            act_i++;
        }
        if(i%4==3){
            switchTemp = !switchTemp;
        }
        offset[2]++;
    }

    //0val
    offset[2] += 8;


    //conv2
    //sram4
    // for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv2; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         weightValue->rnetWeightValue->conv2[i][j] = sramBuffer[0][offset[0]];
    //         offset[0]++;
    //     }
    // }
    int conv2IdxOffset = 0;
    for(int i=0; i<weightValue->rnetWeightValue->filterNumberConv2/3; i++){
        for(int j=0; j<9; j++){
            weightValue->rnetWeightValue->conv2[i+conv2IdxOffset][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
        if(i%16==15){
            conv2IdxOffset += 32;
        }
    }
    conv2IdxOffset = 16;
    for(int i=0; i<weightValue->rnetWeightValue->filterNumberConv2/3; i++){
        for(int j=0; j<9; j++){
            weightValue->rnetWeightValue->conv2[i+conv2IdxOffset][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
        if(i%16==15){
            conv2IdxOffset += 32;
        }
    }
    conv2IdxOffset = 32;
    for(int i=0; i<weightValue->rnetWeightValue->filterNumberConv2/3; i++){
        for(int j=0; j<9; j++){
            weightValue->rnetWeightValue->conv2[i+conv2IdxOffset][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
        if(i%16==15){
            conv2IdxOffset += 32;
        }
    }

    //sram6
    switchTemp = 1;
    int conv2BiasActTotal = weightValue->rnetWeightValue->filterOutChannels2*2;
    for(int i=0, bias_i=0, act_i=0; i<conv2BiasActTotal; i++){
        if(switchTemp){
            weightValue->rnetWeightValue->bias2[bias_i] = sramBuffer[2][offset[2]];
            bias_i++;
        }
        else{
            weightValue->rnetWeightValue->act2[act_i] = sramBuffer[2][offset[2]];
            act_i++;
        }
        if(i%4==3){
            switchTemp = !switchTemp;
        }
        offset[2]++;
    }

    //conv3
    //sram4
    // for (int i = 0; i < weightValue->rnetWeightValue->filterNumberConv3; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         weightValue->rnetWeightValue->conv3[i][j] = sramBuffer[0][offset[0]];
    //         offset[0]++;
    //     }
    // }
    int conv3IdxOffset = 0;
    for(int i=0; i<weightValue->rnetWeightValue->filterNumberConv3/4; i++){
        for(int j=0; j<9; j++){
            weightValue->rnetWeightValue->conv3[i+conv3IdxOffset][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
        if(i%16==15){
            conv3IdxOffset += 48;
        }
    }
    conv3IdxOffset = 16;
    for(int i=0; i<weightValue->rnetWeightValue->filterNumberConv3/4; i++){
        for(int j=0; j<9; j++){
            weightValue->rnetWeightValue->conv3[i+conv3IdxOffset][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
        if(i%16==15){
            conv3IdxOffset += 48;
        }
    }
    conv3IdxOffset = 32;
    for(int i=0; i<weightValue->rnetWeightValue->filterNumberConv3/4; i++){
        for(int j=0; j<9; j++){
            weightValue->rnetWeightValue->conv3[i+conv3IdxOffset][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
        if(i%16==15){
            conv3IdxOffset += 48;
        }
    }
    conv3IdxOffset = 48;
    for(int i=0; i<weightValue->rnetWeightValue->filterNumberConv3/4; i++){
        for(int j=0; j<9; j++){
            weightValue->rnetWeightValue->conv3[i+conv3IdxOffset][j] = sramBuffer[0][offset[0]];
            offset[0]++;
        }
        if(i%16==15){
            conv3IdxOffset += 48;
        }
    }

    //sram6
    switchTemp = 1;
    int conv3BiasActTotal = weightValue->rnetWeightValue->filterOutChannels3*2;
    for(int i=0, bias_i=0, act_i=0; i<conv3BiasActTotal; i++){
        if(switchTemp){
            weightValue->rnetWeightValue->bias3[bias_i] = sramBuffer[2][offset[2]];
            bias_i++;
        }
        else{
            weightValue->rnetWeightValue->act3[act_i] = sramBuffer[2][offset[2]];
            act_i++;
        }
        if(i%4==3){
            switchTemp = !switchTemp;
        }
        offset[2]++;
    }

    //fc1
    //sram5
    for (int i = 0; i < weightValue->rnetWeightValue->fcNumber1; i++) {
        weightValue->rnetWeightValue->fc1[i] = sramBuffer[1][offset[1]];
        offset[1]++;
    }

    //sram6
    switchTemp = 1;
    int fc1BiasActTotal = weightValue->rnetWeightValue->fcOutChannels1*2;
    for(int i=0, bias_i=0, act_i=0; i<fc1BiasActTotal; i++){
        if(switchTemp){
            weightValue->rnetWeightValue->bias4[bias_i] = sramBuffer[2][offset[2]];
            bias_i++;
        }
        else{
            weightValue->rnetWeightValue->act4[act_i] = sramBuffer[2][offset[2]];
            act_i++;
        }
        switchTemp = !switchTemp;       // FC 레이어는 bias, act 한개씩 번갈아가면서 로드함
        offset[2]++;
    }

    //fc2
    //sram5
    for (int i = 0; i < weightValue->rnetWeightValue->fcNumber2; i++) {
        weightValue->rnetWeightValue->fc2[i] = sramBuffer[0][offset[0]];
        offset[0]++;
    }
    //sram6
    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels2; i++) {
        weightValue->rnetWeightValue->bias5[i] = sramBuffer[2][offset[2]];
        offset[2]++;
    }
    //fc3
    //sram5
    for (int i = 0; i < weightValue->rnetWeightValue->fcNumber3; i++) {
        weightValue->rnetWeightValue->fc3[i] = sramBuffer[0][offset[0]];
        offset[0]++;
    }
    //sram6
    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels3; i++) {
        weightValue->rnetWeightValue->bias6[i] = sramBuffer[2][offset[2]];
        offset[2]++;
    }
    //0val
    offset[2] += 10;

}

void insertValueInWeightBuffer(int8_t **sramBuffer, WeightValue *weightValue) {
    int *offset = (int *) malloc(3 * sizeof(int));
    offset[0] = 0;
    offset[1] = 0;
    offset[2] = 0;
    insertPnetValueWeightBuffer(sramBuffer, weightValue, offset);
    insertRnetValueWeightBuffer(sramBuffer, weightValue, offset);

}

int8_t *makeSramWeightFile(char *filePath) {
    LoadFileStruct lfs = loadWeightFile(filePath);
    int weightBufferSize = lfs.fileSize;
    int8_t *mergetWeightBuffer = mergeWeight(lfs.fileBuffer, weightBufferSize);
    free(lfs.fileBuffer);
    //    free(lfs);
    return mergetWeightBuffer;
}

// in main
int8_t **loadMySram(char *sram4Path, char *sram5Path, char *sram6Path) {

    int8_t *sram4Weight = makeSramWeightFile(sram4Path);
    int8_t *sram5Weight = makeSramWeightFile(sram5Path);
    int8_t *sram6Weight = makeSramWeightFile(sram6Path);

    int8_t **sramWeightBuffer = (int8_t **) malloc(3 * sizeof(int8_t *));
    sramWeightBuffer[0] = sram4Weight;
    sramWeightBuffer[1] = sram5Weight;
    sramWeightBuffer[2] = sram6Weight;
    return sramWeightBuffer;
}

void freeSramValue(int8_t **sramWeightBuffer) {
    free(sramWeightBuffer[0]);
    free(sramWeightBuffer[1]);
    free(sramWeightBuffer[2]);
    free(sramWeightBuffer);
}