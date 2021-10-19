cmake_minimum_required(VERSION 3.1)

project(mtcnn C)

set(CMAKE_C_STANDARD 99)

add_executable(mtcnn main.c loadWeightFile.c loadWeightFile.h unionHeader.h loadImageFile.c loadImageFile.h myLayerTools.c myLayerTools.h printOutput.c printOutput.h)
