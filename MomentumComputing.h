//
// Created by mateusz on 10.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_MOMENTUMCOMPUTING_H
#define POBR_IMAGE_SEGMENTATION_MOMENTUMCOMPUTING_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ColourHLS.h"


class MomentumComputing {
public:
    MomentumComputing(cv::Mat &image);
    double GetM1(ColourHLS colour);
    double GetM7(ColourHLS colour);

private:
    cv::Mat& image;

    double Get_m(int p, int q, ColourHLS colour);
};


#endif //POBR_IMAGE_SEGMENTATION_MOMENTUMCOMPUTING_H
