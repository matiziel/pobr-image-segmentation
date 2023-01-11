//
// Created by mateusz on 10.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_COLOURHLS_H
#define POBR_IMAGE_SEGMENTATION_COLOURHLS_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

struct ColourHLS {

public:
    int H;
    int L;
    int S;

    static ColourHLS GetBlack() {
        ColourHLS colour;
        colour.Black();
        return colour;
    }

    static ColourHLS GetWhite() {
        ColourHLS colour;
        colour.White();
        return colour;
    }

    static ColourHLS GetColour(const cv::Vec3b &pixel) {
        ColourHLS colour;
        colour.H = pixel[0];
        colour.L = pixel[1];
        colour.S = pixel[2];
        return colour;
    }

    bool IsBlue(const cv::Vec3b &pixel) {
        return false;
    }

    bool IsYellow(const cv::Vec3b &pixel) {
        return false;
    }

    bool IsRed(const cv::Vec3b &pixel) {
        return false;
    }

    bool operator==(const ColourHLS &colour) {
        if (H == colour.H && L == colour.L && S == colour.S)
            return true;
        return false;
    }

    bool operator!=(const ColourHLS &colour) {
        return !(*this == colour);
    }

private:
    void Black() {
        H = 0;
        L = 0;
        S = 0;
    }

    void White() {
        H = 255;
        L = 255;
        S = 255;
    }
};

#endif //POBR_IMAGE_SEGMENTATION_COLOURHLS_H
