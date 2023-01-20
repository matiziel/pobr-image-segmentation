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

    void ProcessImage(const std::string &fileName) {
        cv::Mat bgrImage = LoadImage(fileName);

        if (!ValidateImage(bgrImage))
            return;

//        GammaCorrection(bgrImage, 1.1);
        cv::Mat image = Converter::ConvertBGRToHLS(bgrImage);

//        Histogram::HistogramEqualization(image);
        Thresholding(image);
        std::vector<Segment> segments = Segmentation::FindSegments(image);
        segments = Recognition::RecognizeLogo(segments);

//        PrintMomentums(fileName, segments);

        DrawBoundingBoxes(image, segments);

        SaveProcessedImage(fileName, Converter::ConvertHLSToBGR(image));
    }

private:
    const std::string inputDirectory;
    const std::string outputDirectory;

    cv::Mat LoadImage(const std::string &fileName);

    bool ValidateImage(const cv::Mat &image);

    void GammaCorrection(cv::Mat &image, float gamma);

    void Thresholding(cv::Mat &image);

    void PrintMomentums(const std::string fileName, const std::vector<Segment> segments) {
        std::cout << fileName << std::endl ;
        for (const auto &segment : segments) {
            auto boundingBox = segment.GetBoundingBox();

            std::cout << "M1: " << segment.M1 << " ; ";
            std::cout << "M2: " << segment.M2 << " ; ";
            std::cout << "M3: " << segment.M3 << " ; ";
            std::cout << "M4: " << segment.M4 << " ; ";
            std::cout << "M7: " << segment.M7 << std::endl;

            std::cout << "xmin: " << boundingBox.xMin << " ; ";
            std::cout << "ymin: " << boundingBox.yMin << " ; ";
            std::cout << "xmax: " << boundingBox.xMax << " ; ";
            std::cout << "ymax: " << boundingBox.yMax << std::endl;
        }
        std::cout << std::endl;
    }

    void DrawBoundingBoxes(cv::Mat &image, const std::vector<Segment> segments);

    void SaveProcessedImage(const std::string &fileName, const cv::Mat &image);
};

#endif //POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H
