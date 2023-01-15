//
// Created by mateusz on 10.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_BOUNDINGBOX_H
#define POBR_IMAGE_SEGMENTATION_BOUNDINGBOX_H

#include <algorithm>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ColourHLS.h"
#include "Segment.h"

class BoundingBox {
public:
    int xMin;
    int xMax;
    int yMin;
    int yMax;

    BoundingBox(int xMin, int xMax, int yMin, int yMax) {
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMin = yMin;
        this->yMax = yMax;
    }

    cv::Mat GetBoundingImage(cv::Mat &image) {
        return image(cv::Rect(xMin, yMin, GetWidth(), GetHeight()));
    }

    int GetWidth() {
        return xMax - xMin;
    }

    int GetHeight() {
        return yMax - yMin;
    }

    static void DrawBoundingBox(cv::Mat &image, ColourHLS colour, BoundingBox boundingBox) {
        cv::Mat_<cv::Vec3b> imageVector = image;
        for (int x = boundingBox.xMin; x <= boundingBox.xMax; x++) {
            ColourHLS::SetColour(imageVector(boundingBox.yMin, x), colour);
            ColourHLS::SetColour(imageVector(boundingBox.yMax, x), colour);
        }

        for (int y = boundingBox.yMin; y <= boundingBox.yMax; y++) {
            ColourHLS::SetColour(imageVector(y, boundingBox.xMin), colour);
            ColourHLS::SetColour(imageVector(y, boundingBox.xMax), colour);
        }
        image = imageVector;
    }
};


#endif //POBR_IMAGE_SEGMENTATION_BOUNDINGBOX_H
