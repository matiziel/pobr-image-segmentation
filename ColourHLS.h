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

    ColourHLS() {}

    ColourHLS(int h, int l, int s) {
        H = h;
        L = l;
        S = s;
    }

    static ColourHLS GetBlack() { return ColourHLS(0, 0, 0); }

    static ColourHLS GetWhite() { return ColourHLS(180, 255, 255); }

    static ColourHLS GetRed() { return ColourHLS(0, 128, 255); }

    static ColourHLS GetColour(const cv::Vec3b &pixel) { return ColourHLS(pixel[0], pixel[1], pixel[2]); }

    static void SetColour(cv::Vec3b &pixel, ColourHLS colour) {
        pixel[0] = colour.H;
        pixel[1] = colour.L;
        pixel[2] = colour.S;
    }

    bool IsBlue() {
        return *this >= BlueMin() && *this <= BlueMax();
    }

    bool IsRed() {
        return (*this >= RedMinLow() && *this <= RedMaxLow()) ||
               (*this >= RedMinHigh() && *this <= RedMaxHigh());
    }

    bool IsWhite() {
        return *this == GetWhite();
    }

    bool operator==(const ColourHLS &colour) {
        return H == colour.H && L == colour.L && S == colour.S;
    }

    bool operator!=(const ColourHLS &colour) {
        return !(*this == colour);
    }

    bool operator>(const ColourHLS &colour) {
        return this->H > colour.H &&
               this->L > colour.L &&
               this->S > colour.S;
    }

    bool operator>=(const ColourHLS &colour) {
        return this->H >= colour.H &&
               this->L >= colour.L &&
               this->S >= colour.S;
    }

    bool operator<(const ColourHLS &colour) {
        return this->H < colour.H &&
               this->L < colour.L &&
               this->S < colour.S;
    }

    bool operator<=(const ColourHLS &colour) {
        return this->H <= colour.H &&
               this->L <= colour.L &&
               this->S <= colour.S;
    }

private:

    static ColourHLS BlueMin() {
        return ColourHLS(70, 25, 40);
    }

    static ColourHLS BlueMax() {
        return ColourHLS(130, 240, 255);
    }

    static ColourHLS RedMinLow() {
        return ColourHLS(0, 25, 40);
    }

    static ColourHLS RedMaxLow() {
        return ColourHLS(8, 240, 255);
    }

    static ColourHLS RedMinHigh() {
        return ColourHLS(165, 25, 40);
    }

    static ColourHLS RedMaxHigh() {
        return ColourHLS(180, 240, 255);
    }
};

#endif //POBR_IMAGE_SEGMENTATION_COLOURHLS_H
