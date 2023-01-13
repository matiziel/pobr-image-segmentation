//
// Created by mateusz on 13.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_SEGMENT_H
#define POBR_IMAGE_SEGMENTATION_SEGMENT_H


#include "ColourHLS.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Segment {
public:
    double M1, M2, M3, M7;
    ColourHLS colour;

    void Init() {
        m00 = m(0, 0);
        m10 = m(1, 0);
        m20 = m(2, 0);
        m30 = m(3, 0);
        m01 = m(0, 1);
        m02 = m(0, 2);
        m03 = m(0, 3);
        m11 = m(1, 1);
        m21 = m(2, 1);
        m12 = m(1, 2);

        xCentral = m10 / m00;
        yCentral = m01 / m00;

        M20 = m20 - m10 * m10 / m00;
        M02 = m02 - m01 * m01 / m00;

        M30 = m30 - 3 * m20 * xCentral + 2 * m10 * xCentral * xCentral;
        M03 = m03 - 3 * m02 * yCentral + 2 * m01 * yCentral * yCentral;

        M11 = m11 - m10 * m01 / m00;
        M21 = m21 - 2 * m11 * xCentral - m20 * yCentral + 2 * m01 * xCentral * xCentral;
        M12 = m12 - 2 * m11 * yCentral - m02 * yCentral + 2 * m10 * yCentral * yCentral;

        M1 = (M02 + M20) / std::pow(m00, 2);
        M2 = (std::pow(M20 - M02, 2) + 4 * M11 * M11) / std::pow(m00, 4);
        M3 = (std::pow(M30 - 3 * M12, 2)  + std::pow(3 * M21 - M03, 2)) / pow(m00, 5);
        M7 = (M02 * M20 - M11 * M11) / pow(m00, 4);
    }

private:
    std::vector<cv::Point2i> pixels;

    double m00;
    double m10, m20, m30;
    double m01, m02, m03;
    double m11, m21, m12;

    double M20, M30;
    double M02, M03;
    double M11, M21, M12;

    int xCentral, yCentral;

    double m(int p, int q) {
        double mpq = 0;
        for (const cv::Point2i &pixel: pixels) {
            mpq += std::pow(pixel.x, p) * std::pow(pixel.y, q);
        }
        return mpq;
    }
};

#endif //POBR_IMAGE_SEGMENTATION_SEGMENT_H
