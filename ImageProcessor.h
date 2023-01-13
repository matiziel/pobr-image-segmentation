//
// Created by mateusz on 11.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H
#define POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H

#include <string>
#include <vector>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ColourHLS.h"
#include "Histogram.h"
#include "Converter.h"

class ImageProcessor {

public:
    ImageProcessor(const std::string& inputDirectory, const std::string& outputDirectory)
            : inputDirectory(inputDirectory), outputDirectory(outputDirectory) { }

    void ProcessImage(const std::string &fileName) {
        cv::Mat bgrImage = LoadImage(fileName);

        if (!ValidateImage(bgrImage))
            return;

//        GammaCorrection(bgrImage, 1.1);
        cv::Mat image = Converter::ConvertBGRToHLS(bgrImage);

        Histogram::HistogramEqualization(image);
        Thresholding(image);

        SaveProcessedImage(fileName, Converter::ConvertHLSToBGR(image));
    }

private:
    const std::string inputDirectory;
    const std::string outputDirectory;

    cv::Mat LoadImage(const std::string &fileName);
    bool ValidateImage(const cv::Mat &image);
    void GammaCorrection(cv::Mat &image, float gamma);
    void Thresholding(cv::Mat &image);
    void SaveProcessedImage(const std::string &fileName, const cv::Mat &image);
};


#endif //POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H
