//
// Created by mateusz on 11.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H
#define POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H

#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ImageProcessor {

public:
    ImageProcessor(const std::string outputDirectory) : outputDirectory(outputDirectory) {}

    void ProcessImage(const std::string &fileName) {
        cv::Mat rgbImage = cv::imread(fileName);
        if (ValidateImage(rgbImage))
            return;

        cv::Mat image;
        cv::cvtColor(rgbImage, image, cv::COLOR_BGR2HLS);

        Thresholding(image);


        SaveProcessedImage(fileName, image);
    }

private:
    const std::string outputDirectory;

    bool ValidateImage(const cv::Mat &image) {
        return image.depth() != sizeof(uchar) && image.channels() == 3;
    }

    void Thresholding(const cv::Mat &image) {
        cv::Mat_<cv::Vec3b> imageVector = image;
        for (int y = 0; y < imageVector.rows; y++) {
            for (int x = 0; x < imageVector.cols; x++) {

            }
        }
    }

    void SaveProcessedImage(const std::string &fileName, const cv::Mat &image) {
        cv::imwrite(outputDirectory + fileName, image);
    }
};


#endif //POBR_IMAGE_SEGMENTATION_IMAGEPROCESSOR_H
