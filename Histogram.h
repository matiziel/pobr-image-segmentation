//
// Created by mateusz on 13.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_HISTOGRAM_H
#define POBR_IMAGE_SEGMENTATION_HISTOGRAM_H

#include <cmath>
#include <vector>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Utils.h"


class Histogram {
public:
    static void HistogramEqualization(cv::Mat &image) {

        std::vector<double> histogram = GetHistogram(image);
        std::vector<double> cdf = GetCDF(histogram);

        cv::Mat_<cv::Vec3b> imageVector = image;
        for (int y = 0; y < imageVector.rows; y++) {
            for (int x = 0; x < imageVector.cols; x++) {
                int value = static_cast<int>(
                        std::round(cdf[imageVector(y, x)[ChanelHLS::L]] * 255)
                );
                imageVector(y, x)[ChanelHLS::L] = Normalize(value);
            }
        }
    }

private:
    const static int histogramSize = 256;

    static std::vector<double> GetHistogram(const cv::Mat &image) {

        std::vector<double> histogram(histogramSize, 1.0);

        cv::Mat_<cv::Vec3b> imageVector = image;
        for (int y = 0; y < imageVector.rows; y++) {
            for (int x = 0; x < imageVector.cols; x++) {
                histogram[imageVector(y, x)[ChanelHLS::L]] += 1.0;
            }
        }

        double pixelCount = imageVector.rows * imageVector.cols;
        for (int i = 0; i < histogram.size(); i++)
            histogram[i] /= pixelCount;

        return histogram;
    }

    static std::vector<double> GetCDF(const std::vector<double> histogram) {
        std::vector<double> cdf(histogramSize, 0);

        cdf[0] = histogram[0];
        for (int i = 1; i < histogramSize; i++) {
            cdf[i] = histogram[i] + cdf[i - 1];
        }
        return cdf;
    }

    static int Normalize(int value) {
        if (value > 255)
            return 255;
        else if (value < 0)
            return 0;
        else
            return value;
    }

};


#endif //POBR_IMAGE_SEGMENTATION_HISTOGRAM_H
