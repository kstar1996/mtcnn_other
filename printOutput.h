#include "unionHeader.h"
#include "loadWeightFile.h"

void printInput(FILE **fp, int16_t *buffer, int height, int width);

void printAfterConv(FILE **fp, int16_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int height, int width, int stride, int padding, int filterSize);

void printDecAfterConv(FILE **fp, int16_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int height, int width, int stride, int padding, int filterSize);

void printAfter11Conv(FILE **fp, int64_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int stride, int padding, int filterSize);

void printDecAfter11Conv(FILE **fp, int64_t ***convResultBuffer, int filterInChannels, int filterOutChannels, int stride, int padding, int filterSize);

void printAfterBias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width);

void printDecAfterBias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width);

void printAfter11Bias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width);

void printDecAfter11Bias(FILE **fp, int16_t **biasResult, int filterOutChannels, int height, int width);

void printAfterAct(FILE **fp, int16_t **actResult, int filterOutChannels, int height, int width);

void printDecAfterAct(FILE **fp, int16_t **actResult, int filterOutChannels, int height, int width);

void printAfterMp(FILE **fp, int16_t **mpResult, int filterOutChannels, int height, int width, int kernelSize, int stride, int paddingSize);

void printDecAfterMp(FILE **fp, int16_t **mpResult, int filterOutChannels, int height, int width, int kernelSize, int stride, int paddingSize);

void printAfterFc(FILE **fp, int16_t **fcResult, int filterOutChannels);

void printDecAfterFc(FILE **fp, int16_t **fcResult, int filterOutChannels);

void printAfterFcBias(FILE **fp, int16_t **biasResult, int filterOutChannels);

void printDecAfterFcBias(FILE **fp, int16_t **biasResult, int filterOutChannels);

void printPnet(FILE **fp, int width, int height, int16_t *Rbuffer, int16_t *Gbuffer, int16_t *Bbuffer, WeightValue *weightValue,
               int16_t ***rgbResultBuffer, int16_t **bias1Result, int16_t **act1Result, int16_t **mp1Result,
               int16_t ***conv2ResultBuffer, int16_t **bias2Result, int16_t **act2Result,
               int16_t ***conv3ResultBuffer, int16_t **bias3Result, int16_t **act3Result,
               int64_t ***conv4ResultBuffer, int16_t **bias4Result, int64_t ***conv5ResultBuffer, int16_t **bias5Result);

void printRnet(FILE **fp, int width, int height, int16_t *Rbuffer, int16_t *Gbuffer, int16_t *Bbuffer, WeightValue *weightValue,
              int16_t ***rgbResultBuffer, int16_t **bias1Result, int16_t **act1Result, int16_t **mp1Result,
              int16_t ***conv2ResultBuffer, int16_t **bias2Result, int16_t **act2Result, int16_t **mp2Result,
              int16_t ***conv3ResultBuffer, int16_t **bias3Result, int16_t **act3Result,
              int16_t **fc1Result, int16_t **bias4Result, int16_t **act4Result,
              int16_t **fc2Result, int16_t **bias5Result, int16_t **fc3Result, int16_t **bias6Result);
