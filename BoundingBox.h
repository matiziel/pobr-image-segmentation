//
// Created by mateusz on 10.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_BOUNDINGBOX_H
#define POBR_IMAGE_SEGMENTATION_BOUNDINGBOX_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ColourHLS.h"

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

    static BoundingBox GetBoundingBoxFromImage(cv::Mat &image, ColourHLS colour) {
        BoundingBox boundingBox = BoundingBox(image.rows, 0, image.cols, 0);

        cv::Mat_<cv::Vec3b> imageVector = image;
        for (int y = 0; y < image.rows; ++y)
            for (int x = 0; x < image.cols; ++x) {
                if (ColourHLS::GetColour(imageVector(y, x)) == colour) {

                    if (x > boundingBox.xMax)
                        boundingBox.xMax = x;

                    if (x < boundingBox.xMin)
                        boundingBox.xMin = x;

                    if (y > boundingBox.yMax)
                        boundingBox.yMax = y;

                    if (y < boundingBox.yMin)
                        boundingBox.yMax = y;
                }
            }
        image = imageVector;
        return boundingBox;
    }
};


#endif //POBR_IMAGE_SEGMENTATION_BOUNDINGBOX_H
