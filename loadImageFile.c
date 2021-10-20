#include "loadImageFile.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

uint8_t ***loadImage(char *filePath, int width, int height, int channels) {
    uint8_t ***imageBuffer;
    imageBuffer = (uint8_t ***) malloc(channels * sizeof(uint8_t **));
    for (int i = 0; i < channels; i++) {
        imageBuffer[i] = (uint8_t **) malloc(height * sizeof(uint8_t *));
        for (int j = 0; j < height; j++) {
            imageBuffer[i][j] = (uint8_t *) malloc(width * sizeof(uint8_t));
        }
    }
    FILE *fp = fopen(filePath, "r");
    for (int i = 0; i < channels; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < width; k++) {
                int temp;
                fscanf(fp, "%d", &temp);
                imageBuffer[i][j][k] = (uint8_t) temp;
            }
        }
    }
    fclose(fp);
    return imageBuffer;
}

uint8_t ****loadMyImage(char *imagePath) {
//    char *imagePaht = "C:/Users/uxfac/Desktop/workspace_clion/mtcnn/resource/testImage/imageText.txt";
    int width = 72;
    int height = 144;
    int channels = 3;

    int fileCount = 0;
    DIR *imageDir;
    uint8_t ****images;
    struct dirent *currentFile;
    imageDir = opendir(imagePath);
    if (imageDir != NULL) {
        for (int i = 0; i < 2; i++) readdir(imageDir);
        while ((currentFile = readdir(imageDir)) != NULL) {
            fileCount++;
        }

        images = (uint8_t *) malloc(fileCount * sizeof(uint8_t ***));
        imageDir = opendir(imagePath);
        int imgidx = 0;
        for (int i = 0; i < 2; i++) readdir(imageDir);
        while ((currentFile = readdir(imageDir)) != NULL) {
            char *sTemp = malloc(sizeof(char) * 200);
            char *fileName = currentFile->d_name;
            strcat(sTemp, imagePath);
            strcat(sTemp, fileName);
            printf("%s\n", sTemp);
            images[imgidx] = loadImage(sTemp, width, height, channels);
            imgidx++;
            // free(sTemp);
            // free(fileName);
        }

        // uint8_t ***image = loadImage(imagePath, width, height, channels);
        return images;
    } else {
        perror(imagePath);
        return EXIT_FAILURE;
    }
}


uint8_t ***loadImageHalf(char *filePath, int width, int height, int channels) {
    uint8_t ***imageBuffer;
    imageBuffer = (uint8_t ***) malloc(channels * sizeof(uint8_t **));
    for (int i = 0; i < channels; i++) {
        imageBuffer[i] = (uint8_t **) malloc(height * sizeof(uint8_t *));
        for (int j = 0; j < height; j++) {
            imageBuffer[i][j] = (uint8_t *) malloc(width * sizeof(uint8_t));
        }
    }
    FILE *fp = fopen(filePath, "r");
    int cnt;
    for (int i = 0; i < channels; i++) {
        for (int j = 0; j < height; j++) {
            cnt = 0;
            for (int k = 0; k < width; k++) {
                int temp1;
                int temp2;
                if (cnt == 0){
                    for (int h = 0; h < 72; h++) {
                        int temp;
                        fscanf(fp, "%d", &temp);
//                        printf("temp :  %d\n",temp);
                        cnt+=1;
                    }
                }
                fscanf(fp, "%d", &temp1);
                fscanf(fp, "%d", &temp2);
//                printf("temp1 :  %d\n",temp1);
//                printf("temp2 :  %d\n",temp2);
                imageBuffer[i][j][k] = (uint8_t) temp1;
            }
        }
    }
    fclose(fp);
    return imageBuffer;
}

// 36 72
//uint8_t ***loadImageHalf(char *filePath, int width, int height, int channels) {
//    uint8_t ***imageBuffer;
//    imageBuffer = (uint8_t ***) malloc(channels * sizeof(uint8_t **));
//    for (int i = 0; i < channels; i++) {
//        imageBuffer[i] = (uint8_t **) malloc(height * sizeof(uint8_t *));
//        for (int j = 0; j < height; j++) {
//            imageBuffer[i][j] = (uint8_t *) malloc(width * sizeof(uint8_t));
//        }
//    }
//    FILE *fp = fopen(filePath, "r");
//    for (int i = 0; i < channels; i++) {
//        for (int j = 0; j < height; j++) {
//            for (int k = 0; k < width; k++) {
//                int temp1;
//                int temp2;
//                fscanf(fp, "%d", &temp1);
//                fscanf(fp, "%d", &temp2);
//                printf("temp1 :  %d\n",temp1);
//                printf("temp2 :  %d\n",temp2);
//                imageBuffer[i][j][k] = (uint8_t) temp1;
//                if (k==35){
//                    for (int h = 0; h < 72; h++) {
//                        int temp;
//                        fscanf(fp, "%d", &temp);
//                        printf("temp :  %d\n",temp);
//                    }
//                }
//            }
//        }
//    }
//    fclose(fp);
//    return imageBuffer;
//}

uint8_t ****loadMyImageHalf(char *imagePath) {
//    char *imagePaht = "C:/Users/uxfac/Desktop/workspace_clion/mtcnn/resource/testImage/imageText.txt";
    int width = 36;
    int height = 72;
    int channels = 3;

    int fileCount = 0;
    DIR *imageDir;
    uint8_t ****images;
    struct dirent *currentFile;
    imageDir = opendir(imagePath);
    if (imageDir != NULL) {
        for(int i=0; i<2; i++) readdir(imageDir);
        while((currentFile = readdir(imageDir)) != NULL){
            fileCount++;
        }

        images = (uint8_t*)malloc(fileCount * sizeof(uint8_t***));
        imageDir = opendir(imagePath);
        int imgidx = 0;
        for(int i=0; i<2; i++) readdir(imageDir);
        while((currentFile = readdir(imageDir)) != NULL){
            char *sTemp = malloc(sizeof(char)*200);
            char *fileName = currentFile->d_name;
            strcat(sTemp, imagePath);
            strcat(sTemp, fileName);
            printf("%s\n", sTemp);
            images[imgidx] = loadImageHalf(sTemp, width, height, channels);
            imgidx++;
            // free(sTemp);
            // free(fileName);
        }

        return images;
    } else {
        perror(imagePath);
        return EXIT_FAILURE;
    }
}

//// 48 96
//uint8_t ***loadImageTwoThird(char *filePath, int width, int height, int channels) {
//    uint8_t ***imageBuffer;
//    imageBuffer = (uint8_t ***) malloc(channels * sizeof(uint8_t **));
//    for (int i = 0; i < channels; i++) {
//        imageBuffer[i] = (uint8_t **) malloc(height * sizeof(uint8_t *));
//        for (int j = 0; j < height; j++) {
//            imageBuffer[i][j] = (uint8_t *) malloc(width * sizeof(uint8_t));
//        }
//    }
//    FILE *fp = fopen(filePath, "r");
//    int inc = 0;
//    for (int i = 0; i < channels; i++) {
//        for (int j = 0; j < height; j++) {
//            for (int k = 0; k < width; k++) {
//                if (inc%2==0){
//                    int temp;
//                    fscanf(fp, "%d", &temp);
////                    printf("temp :  %d\n",temp);
//                    imageBuffer[i][j][k] = (uint8_t) temp;
//                    inc += 1;
//                }
//                else{
//                    int temp1;
//                    int temp2;
//                    fscanf(fp, "%d", &temp1);
//                    fscanf(fp, "%d", &temp2);
////                    printf("temp1 :  %d\n",temp1);
////                    printf("temp2 :  %d\n",temp2);
//                    imageBuffer[i][j][k] = (uint8_t) temp1;
//                    inc += 1;
//                }
//
//                if ((j%2==1) && (k==35)){
//                    for (int h = 0; h < 72; h++) {
//                        int temp3;
//                        fscanf(fp, "%d", &temp3);
////                        printf("temp3 :  %d\n",temp3);
//                    }
//                }
//            }
//        }
//    }
//    fclose(fp);
//    return imageBuffer;
//}

// 48 96
uint8_t ***loadImageTwoThird(char *filePath, int width, int height, int channels) {
    uint8_t ***imageBuffer;
    imageBuffer = (uint8_t ***) malloc(channels * sizeof(uint8_t **));
    for (int i = 0; i < channels; i++) {
        imageBuffer[i] = (uint8_t **) malloc(height * sizeof(uint8_t *));
        for (int j = 0; j < height; j++) {
            imageBuffer[i][j] = (uint8_t *) malloc(width * sizeof(uint8_t));
        }
    }
    FILE *fp = fopen(filePath, "r");
    int inc = 0;
    int cnt;
    for (int i = 0; i < channels; i++) {
        for (int j = 0; j < height; j++) {
            cnt = 0;
            for (int k = 0; k < width; k++) {
                if (cnt == 0){
                    for (int h = 0; h < 72; h++) {
                        int temp3;
                        fscanf(fp, "%d", &temp3);
//                        printf("temp3 :  %d\n",temp3);
                        cnt += 1;
                    }
                }
                // we keep temp and temp1
                if (inc%2==0){
                    int temp;
                    fscanf(fp, "%d", &temp);
//                    printf("temp :  %d\n",temp);
                    imageBuffer[i][j][k] = (uint8_t) temp;
                    inc += 1;
                }
                else{
                    int temp1;
                    int temp2;
                    fscanf(fp, "%d", &temp1);
                    fscanf(fp, "%d", &temp2);
//                    printf("temp1 :  %d\n",temp1);
//                    printf("temp2 :  %d\n",temp2);
                    imageBuffer[i][j][k] = (uint8_t) temp1;
                    inc += 1;
                }
            }
        }
    }
    fclose(fp);
    return imageBuffer;
}

uint8_t ****loadMyImageTwoThird(char *imagePath) {
//    char *imagePaht = "C:/Users/uxfac/Desktop/workspace_clion/mtcnn/resource/testImage/imageText.txt";
    int width = 48;
    int height = 96;
    int channels = 3;

    int fileCount = 0;
    DIR *imageDir;
    uint8_t ****images;
    struct dirent *currentFile;
    imageDir = opendir(imagePath);
    if (imageDir != NULL) {
        for(int i=0; i<2; i++) readdir(imageDir);
        while((currentFile = readdir(imageDir)) != NULL){
            fileCount++;
        }
        images = (uint8_t*)malloc(fileCount * sizeof(uint8_t***));
        imageDir = opendir(imagePath);
        int imgidx = 0;
        for(int i=0; i<2; i++) readdir(imageDir);
        while((currentFile = readdir(imageDir)) != NULL){
            char *sTemp = malloc(sizeof(char)*200);
            char *fileName = currentFile->d_name;
            strcat(sTemp, imagePath);
            strcat(sTemp, fileName);
//            printf("%s\n", sTemp);
            images[imgidx] = loadImageTwoThird(sTemp, width, height, channels);
            imgidx++;
            // free(sTemp);
            // free(fileName);
        }

        return images;
    } else {
        perror(imagePath);
        return EXIT_FAILURE;
    }
}



void freeMyImage(uint8_t ***image, int width, int height, int channels) {
    for (int i = 0; i < channels; i++) {
        for (int j = 0; j < height; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
}