//
// Created by mateusz on 13.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_SEGMENT_H
#define POBR_IMAGE_SEGMENTATION_SEGMENT_H

#include <iterator>
#include <vector>
#include <cmath>
#include "ColourHLS.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "BoundingBox.h"
#include "Config.h"

class Segment {
public:
    double M1, M2, M3, M4, M7;
    const Config config;

    Segment(const std::vector<cv::Point2i> &pixels);

    void Init();

    double Area() const;

    BoundingBox GetBoundingBox() const;

    void Merge(const Segment &segment);

    void SetSegmentBlack(cv::Mat &image) const;

    bool IsLetterL() const;

    bool IsLetterI() const;

    bool IsLetterDOT() const;

    bool IsLetterD() const;

    bool IsWordLI() const;

    bool IsWordID() const;

    bool IsWordLID() const;

    bool IsWordLIDL() const;

    static bool ArePartOfLogo(const Segment &first, const Segment &second);

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
