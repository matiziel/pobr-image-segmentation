//
// Created by mateusz on 14.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_SEGMENTATION_H
#define POBR_IMAGE_SEGMENTATION_SEGMENTATION_H

#include <vector>
#include <deque>
#include <algorithm>
#include <array>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ColourHLS.h"
#include "Segment.h"
#include "ColourProvider.h"
#include "BoundingBox.h"

class Segmentation {
public:
    static std::vector<Segment> FindSegments(cv::Mat &image);

private:
    static Segment FloodFill(cv::Mat &image, int xStart, int yStart, ColourHLS colour);

    static std::array<cv::Point2i, 4> GetNeighbours(int x, int y);

    static bool ValidateNeighbour(int x, int y, int rows, int cols);

    static bool DequeContains(std::deque<cv::Point2i> &deque, cv::Point2i point);
};

#endif //POBR_IMAGE_SEGMENTATION_SEGMENTATION_H
