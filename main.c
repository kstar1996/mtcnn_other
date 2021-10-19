#include "unionHeader.h"
#include "loadWeightFile.h"
#include "loadImageFile.h"
#include "myLayerTools.h"
#include "printOutput.h"
#include <bits/stdint-intn.h>
#include <time.h>

void freeSystemMemory(int8_t **sramBuffer, WeightValue *weightBuffer, uint8_t ****imageBuffer, int16_t **pNetResults,
                      int16_t **rNetResults) {
    freeSramValue(sramBuffer);
    freeWeightValue(weightBuffer);
    freeMyImage(imageBuffer, 72, 144, 3);
    freeMyLayerResult(pNetResults, rNetResults);
}

void freePnet(int16_t *Rbuffer, int16_t *Gbuffer, int16_t *Bbuffer, WeightValue *weightValue,
              int16_t ***rgbResultBuffer, int16_t **bias1Result, int16_t **act1Result, int16_t **mp1Result,
              int16_t ***conv2ResultBuffer, int16_t **bias2Result, int16_t **act2Result,
              int16_t ***conv3ResultBuffer, int16_t **bias3Result, int16_t **act3Result,
              int64_t ***conv4ResultBuffer, int64_t ***conv5ResultBuffer) {
    free(Rbuffer);
    free(Gbuffer);
    free(Bbuffer);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < weightValue->pnetWeightValue->filterOutChannels1; j++) {
            free(rgbResultBuffer[i][j]);
        }
        free(rgbResultBuffer[i]);
    }
    free(rgbResultBuffer);
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels1; i++) {
        free(bias1Result[i]);
    }
    free(bias1Result);
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels1; i++) {
        free(act1Result[i]);
    }
    free(act1Result);
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels1; i++) {
        free(mp1Result[i]);
    }
    free(mp1Result);
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels1; i++) {
        for (int j = 0; j < weightValue->pnetWeightValue->filterOutChannels2; j++) {
            free(conv2ResultBuffer[i][j]);
        }
        free(conv2ResultBuffer[i]);
    }
    free(conv2ResultBuffer);
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels2; i++) {
        free(bias2Result[i]);
    }
    free(bias2Result);
    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels2; i++) {
        free(act2Result[i]);
    }
    free(act2Result);

    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels2; i++) {
        for (int j = 0; j < weightValue->pnetWeightValue->filterOutChannels3; j++) {
            free(conv3ResultBuffer[i][j]);
        }
        free(conv3ResultBuffer[i]);
    }
    free(conv3ResultBuffer);

    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels3; i++) {
        free(bias3Result[i]);
    }
    free(bias3Result);

    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels3; i++) {
        free(act3Result[i]);
    }
    free(act3Result);

    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels3; i++) {
        for (int j = 0; j < weightValue->pnetWeightValue->filterOutChannels4; j++) {
            free(conv4ResultBuffer[i][j]);
        }
        free(conv4ResultBuffer[i]);
    }
    free(conv4ResultBuffer);

    for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels3; i++) {
        for (int j = 0; j < weightValue->pnetWeightValue->filterOutChannels5; j++) {
            free(conv5ResultBuffer[i][j]);
        }
        free(conv5ResultBuffer[i]);
    }
    free(conv5ResultBuffer);
}

void freeRnet(int16_t *Rbuffer, int16_t *Gbuffer, int16_t *Bbuffer, WeightValue *weightValue,
              int16_t ***rgbResultBuffer, int16_t **bias1Result, int16_t **act1Result, int16_t **mp1Result,
              int16_t ***conv2ResultBuffer, int16_t **bias2Result, int16_t **act2Result, int16_t **mp2Result,
              int16_t ***conv3ResultBuffer, int16_t **bias3Result, int16_t **act3Result,
              int16_t **fc1Result, int16_t **bias4Result, int16_t **act4Result, int16_t **fc2Result, int16_t **fc3Result){
    free(Rbuffer);
    free(Gbuffer);
    free(Bbuffer);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < weightValue->rnetWeightValue->filterOutChannels1; j++) {
            free(rgbResultBuffer[i][j]);
        }
        free(rgbResultBuffer[i]);
    }
    free(rgbResultBuffer);
    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels1; i++) {
        free(bias1Result[i]);
    }
    free(bias1Result);
    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels1; i++) {
        free(act1Result[i]);
    }
    free(act1Result);
    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels1; i++) {
        free(mp1Result[i]);
    }
    free(mp1Result);

    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels1; i++) {
        for (int j = 0; j < weightValue->rnetWeightValue->filterOutChannels2; j++) {
            free(conv2ResultBuffer[i][j]);
        }
        free(conv2ResultBuffer[i]);
    }
    free(conv2ResultBuffer);
    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels2; i++) {
        free(bias2Result[i]);
    }
    free(bias2Result);
    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels2; i++) {
        free(act2Result[i]);
    }
    free(act2Result);
    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels2; i++) {
        free(mp2Result[i]);
    }
    free(mp2Result);

    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels2; i++) {
        for (int j = 0; j < weightValue->rnetWeightValue->filterOutChannels3; j++) {
            free(conv3ResultBuffer[i][j]);
        }
        free(conv3ResultBuffer[i]);
    }
    free(conv3ResultBuffer);

    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels3; i++) {
        free(bias3Result[i]);
    }
    free(bias3Result);
    for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels3; i++) {
        free(act3Result[i]);
    }
    free(act3Result);

    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels1; i++) {
        free(fc1Result[i]);
    }
    free(fc1Result);

    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels1; i++) {
        free(bias4Result[i]);
    }
    free(bias4Result);

    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels1; i++) {
        free(act4Result[i]);
    }
    free(act4Result);

    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels2; i++) {
        free(fc2Result[i]);
    }
    free(fc2Result);


    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels3; i++) {
        free(fc3Result[i]);
    }
    free(fc3Result);
}

int16_t **myPnet(WeightValue *weightValue, uint8_t ****imageBuffer, int input_width, int input_height) {
    int height = 12;
    int width = 12;
    int input_stride = 2;
    int padding = 0;
    int filterSize = 3;
    int mpPadding = 0;
    int stride = 1;
    int dumpFileCount = 17;
    int conv1_shift = 4;
    int act1_shift = 4;
    int conv2_shift = 4;
    int act2_shift = 4;
    int conv3_shift = 4;
    int act3_shift = 4;
    int conv4_shift = 4;
    int conv5_shift = 4;
    int bias1_shift = 0;
    int bias2_shift = 0;
    int bias3_shift = 0;
    int bias4_shift = 0;
    int bias5_shift = 0;
    // conv1, input = image shape(72 * 144), channels 3

    int max_width = (input_width - width + (2 * padding)) / input_stride + 1;
    int max_height = (input_height - height + (2 * padding)) / input_stride + 1;
    int16_t **pNetResults = (int16_t **) malloc(max_width * max_height * sizeof(int16_t *));

    // printf("act2: %d\n", weightValue->pnetWeightValue->act2[0]);
    for(int fileCount = 0; fileCount < sizeof(imageBuffer)/sizeof(uint8_t***); fileCount++){
        FILE **fp = (FILE **) malloc(dumpFileCount * sizeof(FILE *));
        for (int dump_idx=0; dump_idx < dumpFileCount; dump_idx++){
            char *s1 = malloc(sizeof(char) * 20);
            char *s2 = "_print_pnet_eujin.txt";
            sprintf(s1, "%d", dump_idx);
            strcat(s1, s2);
            fp[dump_idx] = fopen(s1, "w");
            free(s1);
        }
        for(int i_input_offset = 0; i_input_offset < max_height; i_input_offset++){
            for(int j_input_offset = 0; j_input_offset < max_width; j_input_offset++){
                pNetResults[j_input_offset + (i_input_offset * max_width)] = (int16_t *)malloc(8 * sizeof(int16_t));
                height = 12;
                width = 12;

                int16_t *Rbuffer = (int16_t *) malloc(width * height * sizeof(int16_t));
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        Rbuffer[j + (i * width)] = (int16_t) imageBuffer[fileCount][0][i+(i_input_offset*input_stride)]
                                [j+(j_input_offset*input_stride)];
                    }
                }
                int16_t *Gbuffer = (int16_t *) malloc(width * height * sizeof(int16_t));
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        Gbuffer[j + (i * width)] = (int16_t) imageBuffer[fileCount][1][i+(i_input_offset*input_stride)]
                                [j+(j_input_offset*input_stride)];
                    }
                }
                int16_t *Bbuffer = (int16_t *) malloc(width * height * sizeof(int16_t));
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        Bbuffer[j + (i * width)] = (int16_t) imageBuffer[fileCount][2][i+(i_input_offset*input_stride)]
                                [j+(j_input_offset*input_stride)];
                    }
                }

                filterSize = 3;
                stride = 1;
                padding = 0;
                mpPadding = 0;
                int16_t **rResult = my3x3Convolution(weightValue->pnetWeightValue->conv1R, Rbuffer, width, height,
                                                     filterSize, stride, padding, weightValue->pnetWeightValue->filterOutChannels1, 0, conv1_shift);
                int16_t **gResult = my3x3Convolution(weightValue->pnetWeightValue->conv1G, Gbuffer, width, height,
                                                     filterSize, stride, padding, weightValue->pnetWeightValue->filterOutChannels1, 0, conv1_shift);
                int16_t **bResult = my3x3Convolution(weightValue->pnetWeightValue->conv1B, Bbuffer, width, height,
                                                     filterSize, stride, padding, weightValue->pnetWeightValue->filterOutChannels1, 0, conv1_shift);

                int16_t ***rgbResultBuffer = (int16_t ***) malloc(3 * sizeof(int16_t **));
                rgbResultBuffer[0] = rResult;
                rgbResultBuffer[1] = gResult;
                rgbResultBuffer[2] = bResult;

                int16_t **bias1Result = myBias(rgbResultBuffer, 10, 10, weightValue->pnetWeightValue->bias1,
                                               3, weightValue->pnetWeightValue->filterOutChannels1, bias1_shift);
                int16_t **act1Result = myPrelu(bias1Result, 10, 10, weightValue->pnetWeightValue->act1,
                                               weightValue->pnetWeightValue->filterOutChannels1, act1_shift);
                int16_t **mp1Result = myMaxPooling(act1Result, 10, 10, 2, 2,
                                                   weightValue->pnetWeightValue->filterOutChannels1, 0);


                //conv2, input=feature shape(5*5), channels 8
                filterSize = 3;
                stride = 1;
                padding = 0;
                int16_t ***conv2ResultBuffer = (int16_t ***) malloc(
                        weightValue->pnetWeightValue->filterOutChannels2 * sizeof(int16_t **));
                for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels1; i++) {
                    int16_t **conv2Result = my3x3Convolution(weightValue->pnetWeightValue->conv2, mp1Result[i],
                                                             5, 5, filterSize, stride, padding, weightValue->pnetWeightValue->filterOutChannels2, i, conv2_shift);
                    conv2ResultBuffer[i] = conv2Result;
                }

                int16_t **bias2Result = myBias(conv2ResultBuffer, 3, 3, weightValue->pnetWeightValue->bias2,
                                               weightValue->pnetWeightValue->filterOutChannels1, weightValue->pnetWeightValue->filterOutChannels2, bias2_shift);
                int16_t **act2Result = myPrelu(bias2Result, 3, 3, weightValue->pnetWeightValue->act2,
                                               weightValue->pnetWeightValue->filterOutChannels2, act2_shift);

                //conv3, input=feature shape(3*3), channel 16, out shape(16 * 32 * 1)
                filterSize = 3;
                stride = 1;
                padding = 0;
                int16_t ***conv3ResultBuffer = (int16_t ***) malloc(weightValue->pnetWeightValue->filterOutChannels3 * sizeof(int16_t **));

                for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels2; i++) {
                    int16_t **conv3Result = my3x3Convolution(weightValue->pnetWeightValue->conv3, act2Result[i], 3,
                                                             3, filterSize, stride, padding, weightValue->pnetWeightValue->filterOutChannels3, i, conv3_shift);
                    conv3ResultBuffer[i] = conv3Result;
                }
                int16_t **bias3Result = myBias(conv3ResultBuffer, 1, 1, weightValue->pnetWeightValue->bias3, weightValue->pnetWeightValue->filterOutChannels2, weightValue->pnetWeightValue->filterOutChannels3, bias3_shift);
                int16_t **act3Result = myPrelu(bias3Result, 1, 1, weightValue->pnetWeightValue->act3, weightValue->pnetWeightValue->filterOutChannels3, act3_shift);

                //conv4, input=feature shape(1*1), channel 32, out shape(32 * 2 * 1)
                filterSize = 1;
                stride = 1;
                padding = 0;
                int64_t ***conv4ResultBuffer = (int64_t ***) malloc(weightValue->pnetWeightValue->filterOutChannels3 * sizeof(int64_t **));
                for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels3; i++) {
                    int64_t **conv4Result = my1x1Convolution(weightValue->pnetWeightValue->conv4, act3Result[i], weightValue->pnetWeightValue->filterOutChannels4, i);
                    conv4ResultBuffer[i] = conv4Result;
                }
                int16_t **bias4Result = my11Bias(conv4ResultBuffer, 1, 1, weightValue->pnetWeightValue->bias4, weightValue->pnetWeightValue->filterOutChannels3, weightValue->pnetWeightValue->filterOutChannels4, conv4_shift, bias4_shift);

                //conv5, input=feature shape(1*1), channel 32, out shape(32 * 4 * 1)
                filterSize = 1;
                stride = 1;
                padding = 0;
                int64_t ***conv5ResultBuffer = (int64_t ***) malloc(
                        weightValue->pnetWeightValue->filterOutChannels3 * sizeof(int64_t **));
                for (int i = 0; i < weightValue->pnetWeightValue->filterOutChannels3; i++) {
                    int64_t **conv5Result = my1x1Convolution(weightValue->pnetWeightValue->conv5, act3Result[i], weightValue->pnetWeightValue->filterOutChannels5, i);
                    conv5ResultBuffer[i] = conv5Result;
                }

                int16_t **bias5Result = my11Bias(conv5ResultBuffer, 1, 1, weightValue->pnetWeightValue->bias5, weightValue->pnetWeightValue->filterOutChannels3, weightValue->pnetWeightValue->filterOutChannels5, conv5_shift, bias5_shift);

                pNetResults[j_input_offset + (i_input_offset * max_width)][0] = bias4Result[0][0];
                pNetResults[j_input_offset + (i_input_offset * max_width)][1] = bias4Result[0][1];
                pNetResults[j_input_offset + (i_input_offset * max_width)][2] = bias5Result[0][0];
                pNetResults[j_input_offset + (i_input_offset * max_width)][3] = bias5Result[1][0];
                pNetResults[j_input_offset + (i_input_offset * max_width)][4] = bias5Result[2][0];
                pNetResults[j_input_offset + (i_input_offset * max_width)][5] = bias5Result[3][0];
                pNetResults[j_input_offset + (i_input_offset * max_width)][6] = j_input_offset + (i_input_offset * max_width);
                pNetResults[j_input_offset + (i_input_offset * max_width)][7] = max_width * max_height;

                // print each layer output
//                printPnet(fp, width, height, Rbuffer, Gbuffer, Bbuffer, weightValue,
//                          rgbResultBuffer, bias1Result, act1Result, mp1Result,
//                          conv2ResultBuffer, bias2Result, act2Result,
//                          conv3ResultBuffer, bias3Result, act3Result,
//                          conv4ResultBuffer, bias4Result, conv5ResultBuffer, bias5Result);

                // memory Free!!
                freePnet(Rbuffer, Gbuffer, Bbuffer, weightValue,
                         rgbResultBuffer, bias1Result, act1Result, mp1Result,
                         conv2ResultBuffer, bias2Result, act2Result,
                         conv3ResultBuffer, bias3Result, act3Result,
                         conv4ResultBuffer, conv5ResultBuffer);
            }
        }
        for (int dump_idx=0; dump_idx < dumpFileCount; dump_idx++){
            fclose(fp[dump_idx]);
            // free(fp[dump_idx]);
        }
        free(fp);
    }
//
//    fclose(tfp);
//    fclose(inputfp);

    return pNetResults;
}

int16_t **Threshold(int16_t **arr, int thres, int max_width, int max_height) {
    int16_t **finalResults = (int16_t **) malloc(max_width * max_height * sizeof(int16_t *));

    int16_t face_score;
    int incr = 0;
    for(int i=0; i<arr[0][7]; i++) {
        face_score = arr[i][1];
        if (face_score>=thres){
            finalResults[incr] = arr[i];
            incr+=1;
        }
    }
    return finalResults;
}

int16_t **myRnet(WeightValue *weightValue, uint8_t ****imageBuffer, int16_t **pNetResults, int input_width, int input_height) {
    int height = 24;
    int width = 24;
    int stride = 1;
    int padding = 0;
    int mpPadding = 0;
    int filterSize = 3;
    int conv1Shift = 4;
    int act1Shift = 4;
    int conv2Shift = 4;
    int act2Shift = 4;
    int conv3Shift = 4;
    int act3Shift = 4;
    int fc1Shift = 4;
    int act4Shift = 4;
    int fc2Shift = 4;
    int fc3Shift = 4;
    int bias1Shift = 0;
    int bias2Shift = 0;
    int bias3Shift = 0;
    int bias4Shift = 0;
    int bias5Shift = 0;
    int bias6Shift = 0;
    int dumpFileCount = 17;
    //conv1, input = image shape(72 * 144), channels 3

    // int max_width = (input_width - width + (2 * padding)) / stride + 1;
    // int max_height = (input_height - height + (2 * padding)) / stride + 1;
    int16_t **rNetResults = (int16_t **) malloc(96 * sizeof(int16_t *));

    FILE *weightfp = fopen("weight.txt", "w");
    FILE *inputfp = fopen("input.txt", "w");

    // FILE *fp = fopen("print_rnet.txt", "w");
    FILE **fp = (FILE **) malloc(dumpFileCount * sizeof(FILE *));
    for (int dump_idx=0; dump_idx < dumpFileCount; dump_idx++){
        char *s1 = malloc(sizeof(char) * 20);
        char *s2 = "_print_rnet.txt";
        sprintf(s1, "%d", dump_idx);
        strcat(s1, s2);
        fp[dump_idx] = fopen(s1, "w");
        free(s1);
    }
    for(int input_index=0; input_index<96; input_index++){
        int x_base_address = pNetResults[input_index][2];
        int y_base_address = pNetResults[input_index][3];
        if(x_base_address+width < input_width-1 && y_base_address+height < input_height-1 && x_base_address>=0 && y_base_address>=0){
//     for(int i_input_offset = 0; i_input_offset < max_height; i_input_offset++){
//         for(int j_input_offset = 0; j_input_offset < max_width; j_input_offset++){
            int16_t *Rbuffer = (int16_t *) malloc(width * height * sizeof(int16_t));
            for (int i = 0; i < 24; i++) {
                for (int j = 0; j < 24; j++) {
                    Rbuffer[j + (i * width)] = imageBuffer[0][0][i+y_base_address][j+x_base_address];
                }
            }

            int16_t *Gbuffer = (int16_t *) malloc(width * height * sizeof(int16_t));
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    Gbuffer[j + (i * width)] = imageBuffer[0][1][i+y_base_address][j+x_base_address];
                }
            }

            int16_t *Bbuffer = (int16_t *) malloc(width * height * sizeof(int16_t));
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    Bbuffer[j + (i * width)] = imageBuffer[0][2][i+y_base_address][j+x_base_address];
                }
            }
            filterSize = 3;
            stride = 1;
            padding = 0;
            mpPadding = 0;
            int16_t **rResult = my3x3Convolution(weightValue->rnetWeightValue->conv1R, Rbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift);
            // int16_t **rResult = fprintDecmy3x3Convolution(weightValue->rnetWeightValue->conv1R, Rbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift, weightfp, inputfp);
            // int16_t **rResult = fprintHexmy3x3Convolution(weightValue->rnetWeightValue->conv1R, Rbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift, weightfp, inputfp);

            int16_t **gResult = my3x3Convolution(weightValue->rnetWeightValue->conv1G, Gbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift);
            // int16_t **gResult = fprintDecmy3x3Convolution(weightValue->rnetWeightValue->conv1G, Gbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift, weightfp, inputfp);
            // int16_t **gResult = fprintHexmy3x3Convolution(weightValue->rnetWeightValue->conv1G, Gbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift, weightfp, inputfp);

            int16_t **bResult = my3x3Convolution(weightValue->rnetWeightValue->conv1B, Bbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift);
            // int16_t **bResult = fprintDecmy3x3Convolution(weightValue->rnetWeightValue->conv1B, Bbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift, weightfp, inputfp);
            // int16_t **bResult = fprintHexmy3x3Convolution(weightValue->rnetWeightValue->conv1B, Bbuffer, 24, 24, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels1, 0, conv1Shift, weightfp, inputfp);

            int16_t ***rgbResultBuffer = (int16_t ***) malloc(3 * sizeof(int16_t **));
            rgbResultBuffer[0] = rResult;
            rgbResultBuffer[1] = gResult;
            rgbResultBuffer[2] = bResult;

            int16_t **bias1Result = myBias(rgbResultBuffer, 22, 22, weightValue->rnetWeightValue->bias1, 3, weightValue->rnetWeightValue->filterOutChannels1, bias1Shift);
            // int16_t **bias1Result = fprintDecmyBias(rgbResultBuffer, 22, 22, weightValue->rnetWeightValue->bias1, 3, weightValue->rnetWeightValue->filterOutChannels1, bias1Shift, weightfp, inputfp);
            // int16_t **bias1Result = fprintHexmyBias(rgbResultBuffer, 22, 22, weightValue->rnetWeightValue->bias1, 3, weightValue->rnetWeightValue->filterOutChannels1, bias1Shift, weightfp, inputfp);

            int16_t **act1Result = myPrelu(bias1Result, 22, 22, weightValue->rnetWeightValue->act1, weightValue->rnetWeightValue->filterOutChannels1, act1Shift);
            // int16_t **act1Result = fprintDecmyPrelu(bias1Result, 22, 22, weightValue->rnetWeightValue->act1, weightValue->rnetWeightValue->filterOutChannels1, act1Shift, weightfp, inputfp);
            // int16_t **act1Result = fprintHexmyPrelu(bias1Result, 22, 22, weightValue->rnetWeightValue->act1, weightValue->rnetWeightValue->filterOutChannels1, act1Shift, weightfp, inputfp);

            int16_t **mp1Result = myMaxPooling(act1Result, 22, 22, 2, 2, weightValue->rnetWeightValue->filterOutChannels1, 0);
            // int16_t **mp1Result = fprintDecmyMaxPooling(act1Result, 22, 22, 2, 2, weightValue->rnetWeightValue->filterOutChannels1, 0, inputfp);

            //conv2, input=feature shape(11*11), channels 28 output=feature shape(9*9), channel 48
            filterSize = 3;
            stride = 1;
            padding = 0;
            mpPadding = 1;
            int16_t ***conv2ResultBuffer = (int16_t ***) malloc(weightValue->rnetWeightValue->filterOutChannels2 * sizeof(int16_t **));
            for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels1; i++) {
                int16_t **conv2Result = my3x3Convolution(weightValue->rnetWeightValue->conv2, mp1Result[i], 11, 11, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels2, i, conv2Shift);
                // int16_t **conv2Result = fprintDecmy3x3Convolution(weightValue->rnetWeightValue->conv2, mp1Result[i], 11, 11, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels2, i, conv2Shift, weightfp, inputfp);
                // int16_t **conv2Result = fprintHexmy3x3Convolution(weightValue->rnetWeightValue->conv2, mp1Result[i], 11, 11, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels2, i, conv2Shift, weightfp, inputfp);
                conv2ResultBuffer[i] = conv2Result;
            }

            int16_t **bias2Result = myBias(conv2ResultBuffer, 9, 9, weightValue->rnetWeightValue->bias2, weightValue->rnetWeightValue->filterOutChannels1, weightValue->rnetWeightValue->filterOutChannels2, bias2Shift);
            // int16_t **bias2Result = fprintDecmyBias(conv2ResultBuffer, 9, 9, weightValue->rnetWeightValue->bias2, weightValue->rnetWeightValue->filterOutChannels1, weightValue->rnetWeightValue->filterOutChannels2, bias2Shift, weightfp, inputfp);
            // int16_t **bias2Result = fprintHexmyBias(conv2ResultBuffer, 9, 9, weightValue->rnetWeightValue->bias2, weightValue->rnetWeightValue->filterOutChannels1, weightValue->rnetWeightValue->filterOutChannels2, bias2Shift, weightfp, inputfp);

            int16_t **act2Result = myPrelu(bias2Result, 9, 9, weightValue->rnetWeightValue->act2, weightValue->rnetWeightValue->filterOutChannels2, act2Shift);
            // int16_t **act2Result = fprintDecmyPrelu(bias2Result, 9, 9, weightValue->rnetWeightValue->act2, weightValue->rnetWeightValue->filterOutChannels2, act2Shift, weightfp, inputfp);
            // int16_t **act2Result = fprintHexmyPrelu(bias2Result, 9, 9, weightValue->rnetWeightValue->act2, weightValue->rnetWeightValue->filterOutChannels2, act2Shift, weightfp, inputfp);

            int16_t **mp2Result = myMaxPooling(act2Result, 9, 9, 2, 2, weightValue->rnetWeightValue->filterOutChannels2, 1);
            // int16_t **mp2Result = fprintDecmyMaxPooling(act2Result, 9, 9, 2, 2, weightValue->rnetWeightValue->filterOutChannels2, 1, inputfp);
            //conv2, input=feature shape(11*11), channels 28 output=feature shape(9*9), channel 48
            filterSize = 3;
            stride = 1;
            padding = 0;
            mpPadding = 1;
            int16_t ***conv3ResultBuffer = (int16_t ***) malloc(weightValue->rnetWeightValue->filterOutChannels2 * sizeof(int16_t **));
            for (int i = 0; i < weightValue->rnetWeightValue->filterOutChannels2; i++) {
                int16_t **conv3Result = my3x3Convolution(weightValue->rnetWeightValue->conv3, mp2Result[i], 5, 5, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels3, i, conv3Shift);
                // int16_t **conv3Result = fprintDecmy3x3Convolution(weightValue->rnetWeightValue->conv3, mp2Result[i], 5, 5, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels3, i, conv3Shift, weightfp, inputfp);
                // int16_t **conv3Result = fprintHexmy3x3Convolution(weightValue->rnetWeightValue->conv3, mp2Result[i], 5, 5, filterSize, stride, padding, weightValue->rnetWeightValue->filterOutChannels3, i, conv3Shift, weightfp, inputfp);
                conv3ResultBuffer[i] = conv3Result;
            }
            int16_t **bias3Result = myBias(conv3ResultBuffer, 3, 3, weightValue->rnetWeightValue->bias3, weightValue->rnetWeightValue->filterOutChannels2, weightValue->rnetWeightValue->filterOutChannels3, bias3Shift);
            // int16_t **bias3Result = fprintDecmyBias(conv3ResultBuffer, 3, 3, weightValue->rnetWeightValue->bias3, weightValue->rnetWeightValue->filterOutChannels2, weightValue->rnetWeightValue->filterOutChannels3, bias3Shift, weightfp, inputfp);
            // int16_t **bias3Result = fprintHexmyBias(conv3ResultBuffer, 3, 3, weightValue->rnetWeightValue->bias3, weightValue->rnetWeightValue->filterOutChannels2, weightValue->rnetWeightValue->filterOutChannels3, bias3Shift, weightfp, inputfp);

            int16_t **act3Result = myPrelu(bias3Result, 3, 3, weightValue->rnetWeightValue->act3, weightValue->rnetWeightValue->filterOutChannels3, act3Shift);
            // int16_t **act3Result = fprintDecmyPrelu(bias3Result, 3, 3, weightValue->rnetWeightValue->act3, weightValue->rnetWeightValue->filterOutChannels3, act3Shift, weightfp, inputfp);
            // int16_t **act3Result = fprintHexmyPrelu(bias3Result, 3, 3, weightValue->rnetWeightValue->act3, weightValue->rnetWeightValue->filterOutChannels3, act3Shift, weightfp, inputfp);


            //FC
            int16_t **fc1Result = myConvFC(act3Result, weightValue->rnetWeightValue->fc1, weightValue->rnetWeightValue->filterOutChannels3, weightValue->rnetWeightValue->fcOutChannels1, 3, 3, fc1Shift);
            // int16_t **fc1Result = fprintDecmyConvFC(act3Result, weightValue->rnetWeightValue->fc1, weightValue->rnetWeightValue->filterOutChannels3, weightValue->rnetWeightValue->fcOutChannels1, 3, 3, fc1Shift, weightfp, inputfp);
            // int16_t **fc1Result = fprintHexmyConvFC(act3Result, weightValue->rnetWeightValue->fc1, weightValue->rnetWeightValue->filterOutChannels3, weightValue->rnetWeightValue->fcOutChannels1, 3, 3, fc1Shift, weightfp, inputfp);

            int16_t **bias4Result = myFcBias(fc1Result, weightValue->rnetWeightValue->bias4, weightValue->rnetWeightValue->fcOutChannels1, bias4Shift);
            // int16_t **bias4Result = fprintDecmyFcBias(fc1Result, weightValue->rnetWeightValue->bias4, weightValue->rnetWeightValue->fcOutChannels1, bias4Shift, weightfp, inputfp);
            // int16_t **bias4Result = fprintHexmyFcBias(fc1Result, weightValue->rnetWeightValue->bias4, weightValue->rnetWeightValue->fcOutChannels1, bias4Shift, weightfp, inputfp);

            int16_t **act4Result = myPrelu(bias4Result, 1, 1, weightValue->rnetWeightValue->act4, weightValue->rnetWeightValue->fcOutChannels1, act4Shift);
            // int16_t **act4Result = fprintDecmyPrelu(bias4Result, 1, 1, weightValue->rnetWeightValue->act4, weightValue->rnetWeightValue->fcOutChannels1, act4Shift, weightfp, inputfp);
            // int16_t **act4Result = fprintHexmyPrelu(bias4Result, 1, 1, weightValue->rnetWeightValue->act4, weightValue->rnetWeightValue->fcOutChannels1, act4Shift, weightfp, inputfp);



            //FC1
            int16_t **fc2Result = myFC(act4Result, weightValue->rnetWeightValue->fc2, weightValue->rnetWeightValue->fcOutChannels1, weightValue->rnetWeightValue->fcOutChannels2, fc2Shift);
            // int16_t **fc2Result = fprintDecmyFC(act4Result, weightValue->rnetWeightValue->fc2, weightValue->rnetWeightValue->fcOutChannels1, weightValue->rnetWeightValue->fcOutChannels2, fc2Shift, weightfp, inputfp);
            // int16_t **fc2Result = fprintHexmyFC(act4Result, weightValue->rnetWeightValue->fc2, weightValue->rnetWeightValue->fcOutChannels1, weightValue->rnetWeightValue->fcOutChannels2, fc2Shift, weightfp, inputfp);

            int16_t **bias5Result = myFcBias(fc2Result, weightValue->rnetWeightValue->bias5, weightValue->rnetWeightValue->fcOutChannels2, bias5Shift);
            // int16_t **bias5Result = fprintDecmyFcBias(fc2Result, weightValue->rnetWeightValue->bias5, weightValue->rnetWeightValue->fcOutChannels2, bias5Shift, weightfp, inputfp);
            // int16_t **bias5Result = fprintHexmyFcBias(fc2Result, weightValue->rnetWeightValue->bias5, weightValue->rnetWeightValue->fcOutChannels2, bias5Shift, weightfp, inputfp);

            //FC2
            int16_t **fc3Result = myFC(act4Result, weightValue->rnetWeightValue->fc3, weightValue->rnetWeightValue->fcOutChannels1, weightValue->rnetWeightValue->fcOutChannels3, fc3Shift);
            // int16_t **fc3Result = fprintDecmyFC(act4Result, weightValue->rnetWeightValue->fc3, weightValue->rnetWeightValue->fcOutChannels1, weightValue->rnetWeightValue->fcOutChannels3, fc3Shift, weightfp, inputfp);
            // int16_t **fc3Result = fprintDecmyFC(act4Result, weightValue->rnetWeightValue->fc3, weightValue->rnetWeightValue->fcOutChannels1, weightValue->rnetWeightValue->fcOutChannels3, fc3Shift, weightfp, inputfp);

            int16_t **bias6Result = myFcBias(fc3Result, weightValue->rnetWeightValue->bias6, weightValue->rnetWeightValue->fcOutChannels3, bias6Shift);
            // int16_t **bias6Result = fprintDecmyFcBias(fc3Result, weightValue->rnetWeightValue->bias6, weightValue->rnetWeightValue->fcOutChannels3, bias6Shift, weightfp, inputfp);
            // int16_t **bias6Result = fprintDecmyFcBias(fc3Result, weightValue->rnetWeightValue->bias6, weightValue->rnetWeightValue->fcOutChannels3, bias6Shift, weightfp, inputfp);

            int16_t ***rNetResult = (int16_t ***) malloc(2 * sizeof(int16_t **));
            rNetResult[0] = bias5Result;
            rNetResult[1] = bias6Result;
            rNetResults[input_index] = (int16_t *)malloc(8 * sizeof(int16_t));
            rNetResults[input_index][0] = bias5Result[0][0];
            rNetResults[input_index][1] = bias5Result[1][0];
            rNetResults[input_index][2] = bias6Result[0][0];
            rNetResults[input_index][3] = bias6Result[1][0];
            rNetResults[input_index][4] = bias6Result[2][0];
            rNetResults[input_index][5] = bias6Result[3][0];
            rNetResults[input_index][6] = pNetResults[input_index][6];
            rNetResults[input_index][7] = pNetResults[input_index][7];


            // print layer output
            printRnet(fp, width, height, Rbuffer, Gbuffer, Bbuffer, weightValue,
                      rgbResultBuffer, bias1Result, act1Result, mp1Result,
                      conv2ResultBuffer, bias2Result, act2Result, mp2Result,
                      conv3ResultBuffer, bias3Result, act3Result,
                      fc1Result, bias4Result, act4Result,
                      fc2Result, bias5Result, fc3Result, bias6Result);

            freeRnet(Rbuffer, Gbuffer, Bbuffer, weightValue,
                     rgbResultBuffer, bias1Result, act1Result, mp1Result,
                     conv2ResultBuffer, bias2Result, act2Result, mp2Result,
                     conv3ResultBuffer, bias3Result, act3Result,
                     fc1Result, bias4Result, act4Result, fc2Result, fc3Result);
            //     }
            // }
        }else{
            rNetResults[input_index] = (int16_t *)malloc(8 * sizeof(int16_t));
            rNetResults[input_index][0] = 0;
            rNetResults[input_index][1] = 0;
            rNetResults[input_index][2] = pNetResults[input_index][2];
            rNetResults[input_index][3] = pNetResults[input_index][3];
            rNetResults[input_index][4] = pNetResults[input_index][4];
            rNetResults[input_index][5] = pNetResults[input_index][5];
            rNetResults[input_index][6] = pNetResults[input_index][6];
            rNetResults[input_index][7] = pNetResults[input_index][7];
        }
    }
    //    //resultValue, Check Return;
    //    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels2; i++) {
    //        free(bias5Result[i]);
    //    }
    //    free(bias5Result);
    //
    //    for (int i = 0; i < weightValue->rnetWeightValue->fcOutChannels3; i++) {
    //        free(bias6Result[i]);
    //    }
    //    free(bias6Result);
    for (int dump_idx=0; dump_idx < dumpFileCount; dump_idx++){
        fclose(fp[dump_idx]);
        // free(fp[dump_idx]);
    }
    free(fp);

    fclose(inputfp);
    fclose(weightfp);
    return rNetResults;
}

int main() {
    int image_width=72, image_height=144;
    char *sram4Path = "../resource/sw_weight/sram4.coe";
    char *sram5Path = "../resource/sw_weight/sram5.coe";
    char *sram6Path = "../resource/sw_weight/sram6.coe";

    int8_t **sramBuffer = loadMySram(sram4Path, sram5Path, sram6Path);
    WeightValue *weightBuffer = initWeightMemory();
    insertValueInWeightBuffer(sramBuffer, weightBuffer);

    char *imagePath = "../resource/testImage/";
    uint8_t ****imageBuffer = loadMyImage(imagePath);
    uint8_t ****imageBufferTwoThird = loadMyImageTwoThird(imagePath);
    uint8_t ****imageBufferHalf = loadMyImageHalf(imagePath);

    time_t startTime = time(NULL);
    int16_t **pNetResults = myPnet(weightBuffer, imageBuffer, 72, 144);
    int16_t **pNetResultsTwoThird = myPnet(weightBuffer, imageBufferTwoThird, 48, 96);
    int16_t **pNetResultsHalf = myPnet(weightBuffer, imageBufferHalf, 36, 72);

    ChangeCoordinatePnet(pNetResults);
    ChangeCoordinatePnet(pNetResultsTwoThird);
    ChangeCoordinatePnet(pNetResultsHalf);

    pNetResults = BoundingBoxCheck(pNetResults, image_width, image_height);
    quickSortDesc(pNetResults, 0, pNetResults[0][7] - 1);

    pNetResultsTwoThird = BoundingBoxCheck(pNetResultsTwoThird, image_width, image_height);
    quickSortDesc(pNetResultsTwoThird, 0, pNetResultsTwoThird[0][7] - 1);

    pNetResultsHalf = BoundingBoxCheck(pNetResultsHalf, image_width, image_height);
    quickSortDesc(pNetResultsHalf, 0, pNetResultsHalf[0][7] - 1);

    pNetResults = ReturnPnetTop32(pNetResults);
    pNetResultsTwoThird = ReturnPnetTop32(pNetResultsTwoThird);
    pNetResultsHalf = ReturnPnetTop32(pNetResultsHalf);

    int16_t **pNetResultsFinal = (int16_t **)malloc(96 * sizeof(int16_t *));
    for(int i=0; i<32; i++){
        pNetResultsFinal[i] = pNetResults[i];
        pNetResultsFinal[i + 32] = pNetResultsTwoThird[i];
        pNetResultsFinal[i + 64] = pNetResultsHalf[i];
    }

    int16_t **rNetResults = myRnet(weightBuffer, imageBuffer, pNetResultsFinal, 72, 144);
    time_t endTime = time(NULL);

    // freeSystemMemory(sramBuffer, weightBuffer, imageBuffer, pNetResultsFinal, rNetResults);

    return 0;
}