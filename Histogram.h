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
    static void HistogramEqualization(cv::Mat &image);

private:
    const static int histogramSize = 256;

    static std::vector<double> GetHistogram(const cv::Mat &image);

    static std::vector<double> GetCDF(const std::vector<double> &histogram);

    static int Normalize(int value);
};

#endif //POBR_IMAGE_SEGMENTATION_HISTOGRAM_H
