//
// Created by mateusz on 20.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_RECOGNITION_H
#define POBR_IMAGE_SEGMENTATION_RECOGNITION_H

#include <vector>
#include <deque>
#include "Segment.h"

class Recognition {
public:
    static std::vector<Segment> RecognizeLogo(cv::Mat &image, const std::vector<Segment> &segments);

private:
    static std::vector<Segment> GetLogoSegments(cv::Mat &image, const std::vector<Segment> &segments);

    static std::vector<Segment> MergeCommonSegments(std::vector<Segment> &segments);

    static std::vector<Segment> RecognizeSegments(cv::Mat &image, std::vector<Segment> &segments);
};

#endif //POBR_IMAGE_SEGMENTATION_RECOGNITION_H
