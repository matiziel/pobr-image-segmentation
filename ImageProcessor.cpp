//
// Created by mateusz on 11.01.23.
//

#include "ImageProcessor.h"

void ImageProcessor::ProcessImage(const std::string &fileName) {
    cv::Mat bgrImage = LoadImage(fileName);

    if (!ValidateImage(bgrImage))
        return;

//        GammaCorrection(bgrImage, 1.1);
    cv::Mat image = Converter::ConvertBGRToHLS(bgrImage);

    Histogram::HistogramEqualization(image);

    Thresholding(image);

    std::vector<Segment> segments = Segmentation::FindSegments(image);

    std::vector<Segment> logoSegments = Recognition::RecognizeLogo(image, segments);

    PrintMomentums(fileName, logoSegments);

    DrawBoundingBoxes(image, logoSegments);

    SaveProcessedImage(fileName, Converter::ConvertHLSToBGR(image));
}

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

void ImageProcessor::PrintMomentums(const std::string fileName, const std::vector<Segment> segments) {
    std::cout << fileName << std::endl;
    for (const auto &segment: segments) {
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






