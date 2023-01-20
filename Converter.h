//
// Created by mateusz on 13.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_CONVERTER_H
#define POBR_IMAGE_SEGMENTATION_CONVERTER_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Converter {
public:
    static cv::Mat ConvertHLSToBGR(const cv::Mat &image) {
        cv::Mat result;
        cv::cvtColor(image, result, cv::COLOR_HLS2BGR);
        return result;
    }

    static cv::Mat ConvertBGRToHLS(const cv::Mat &image) {
        cv::Mat result;
        cv::cvtColor(image, result, cv::COLOR_BGR2HLS);
        return result;
    }
};

#endif //POBR_IMAGE_SEGMENTATION_CONVERTER_H
