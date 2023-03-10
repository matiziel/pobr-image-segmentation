//
// Created by mateusz on 11.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H
#define POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ColourHLS.h"
#include "Histogram.h"
#include "Converter.h"
#include "Segmentation.h"
#include "Recognition.h"

class ImageProcessor {

public:
    ImageProcessor(std::string inputDirectory, std::string outputDirectory)
            : inputDirectory(std::move(inputDirectory)), outputDirectory(std::move(outputDirectory)) {}

    void ProcessImage(const std::string &fileName);

private:
    const std::string inputDirectory;
    const std::string outputDirectory;

    cv::Mat LoadImage(const std::string &fileName);

    bool ValidateImage(const cv::Mat &image);

    void GammaCorrection(cv::Mat &image, float gamma);

    void Thresholding(cv::Mat &image);

    static void PrintMomentums(const std::string fileName, const std::vector<Segment> segments);

    void DrawBoundingBoxes(cv::Mat &image, const std::vector<Segment> segments);

    void SaveProcessedImage(const std::string &fileName, const cv::Mat &image);
};

#endif //POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H
