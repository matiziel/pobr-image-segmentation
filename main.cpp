#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "ImageProcessor.h"

int main(int argc, char **argv) {
    std::string inputImages[8] = {
            "lidl_1.png",
            "lidl_2.png",
            "lidl_3.png",
            "lidl_4.png",
            "lidl_4.1.png",
            "lidl_5.png",
            "lidl_6.png",
            "lidl_6.1.png"
    };
    ImageProcessor imageProcessor("../Data_copy/", "../Output/");

//    std::string inputImages[6] = {
//            "lidl_1.png",
//            "lidl_2.png",
//            "lidl_3.png",
//            "lidl_4.png",
//            "lidl_5.png",
//            "lidl_6.png"
//    };
//    ImageProcessor imageProcessor("../Data/", "../Output/");

    for (auto image: inputImages) {
        imageProcessor.ProcessImage(image);
    }
}