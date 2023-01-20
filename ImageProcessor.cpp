//
// Created by mateusz on 11.01.23.
//

#include "ImageProcessor.h"

cv::Mat ImageProcessor::LoadImage(const std::string &fileName) {
    return cv::imread(inputDirectory + fileName);
}

bool ImageProcessor::ValidateImage(const cv::Mat &image) {
    return image.depth() != sizeof(uchar) && image.channels() == 3;
}

void ImageProcessor::GammaCorrection(cv::Mat &image, float gamma) {
    cv::Mat_<cv::Vec3b> imageVector = image;
    for (int y = 0; y < imageVector.rows; y++) {
        for (int x = 0; x < imageVector.cols; x++) {
            for (int c = 0; c < imageVector.channels(); c++) {
                imageVector(y, x)[c] = pow(imageVector(y, x)[c] / 255.0, gamma) * 255;
            }
        }
    }
    image = imageVector;
}

void ImageProcessor::Thresholding(cv::Mat &image) {
    cv::Mat_<cv::Vec3b> imageVector = image;
    for (int y = 0; y < imageVector.rows; y++) {
        for (int x = 0; x < imageVector.cols; x++) {
            ColourHLS colour = ColourHLS::GetColour(imageVector(y, x));
            if (colour.IsBlue() || colour.IsRed())
                ColourHLS::SetColour(imageVector(y, x), ColourHLS::GetWhite());
            else
                ColourHLS::SetColour(imageVector(y, x), ColourHLS::GetBlack());
        }
    }
    image = imageVector;
}

void ImageProcessor::DrawBoundingBoxes(cv::Mat &image, const std::vector<Segment> segments) {
    std::for_each(
            segments.cbegin(),
            segments.cend(),
            [&](const Segment &segment) {
                BoundingBox::DrawBoundingBox(image, ColourHLS::GetRed(), segment.GetBoundingBox());
            });
}

void ImageProcessor::SaveProcessedImage(const std::string &fileName, const cv::Mat &image) {
    cv::imwrite(outputDirectory + fileName, image);
}


