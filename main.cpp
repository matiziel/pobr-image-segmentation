#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "ImageProcessor.h"

int main(int argc, char **argv) {
    std::string inputImages[6] = {
            "Data/lidl_1.jpg",
            "Data/lidl_2.jpg",
            "Data/lidl_3.jpg",
            "Data/lidl_4.jpg",
            "Data/lidl_5.jpg",
            "Data/lidl_6.jpg"
    };
    std::string outputDirectory = "Output";

    ImageProcessor imageProcessor(outputDirectory);
    for (auto image : inputImages) {
        imageProcessor.ProcessImage(image);
    }
}