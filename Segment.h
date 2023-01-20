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
    const ColourHLS colour;
    const Config config;

    Segment(const std::vector<cv::Point2i> &pixels, const ColourHLS &colour)
            : pixels(pixels), colour(colour), config() {}

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
        M3 = (std::pow(M30 - 3 * M12, 2) + std::pow(3 * M21 - M03, 2)) / pow(m00, 5);
        M4 = (std::pow(M30 - M12, 2) + std::pow(M21 - M03, 2)) / pow(m00, 5);
        M7 = (M02 * M20 - M11 * M11) / pow(m00, 4);
    }

    double Area() {
        return m00;
    }

    std::vector<cv::Point2i> GetPixels() const {
        return pixels;
    }

    BoundingBox GetBoundingBox() const {
        auto xComparator =
                [](const cv::Point2i &l, const cv::Point2i &r) {
                    return l.x < r.x;
                };

        auto yComparator =
                [](const cv::Point2i &l, const cv::Point2i &r) {
                    return l.y < r.y;
                };

        auto xMin = std::min_element(pixels.cbegin(), pixels.cend(), xComparator);
        auto xMax = std::max_element(pixels.cbegin(), pixels.cend(), xComparator);
        auto yMin = std::min_element(pixels.cbegin(), pixels.cend(), yComparator);
        auto yMax = std::max_element(pixels.cbegin(), pixels.cend(), yComparator);

        return BoundingBox((*xMin).x, (*xMax).x, (*yMin).y, (*yMax).y);
    }

    Segment Merge(const Segment &segment) {
        std::vector<cv::Point2i> mergedPixels;
        mergedPixels.insert(mergedPixels.end(), pixels.begin(), pixels.end());
        mergedPixels.insert(mergedPixels.end(), segment.pixels.begin(), segment.pixels.end());

        Segment mergedSegments = Segment(mergedPixels, colour);
        mergedSegments.Init();
        return mergedSegments;
    }

    static bool ArePartOfLogo(const Segment &first, const Segment &second) {
        const auto firstBox = first.GetBoundingBox();
        const auto secondBox = second.GetBoundingBox();

        const auto firstCenter = firstBox.GetCenterPoint();
        const auto secondCenter = secondBox.GetCenterPoint();

        return
                static_cast<double>(std::abs(firstCenter.y - secondCenter.y)) <
                3.5 * static_cast<double>(firstBox.GetHeight() + secondBox.GetHeight()) / 2.0 &&
                static_cast<double>(std::abs(firstCenter.x - secondCenter.x)) <
                3.5 * static_cast<double>(firstBox.GetWidth() + secondBox.GetWidth()) / 2.0;
    }

    bool IsLetterL() const {
        return M1 > config.L.M1Min &&
               M1 < config.L.M1Max &&
               M7 > config.L.M7Min &&
               M7 < config.L.M7Max &&
               M2 < config.L.M2Max;
    }

    bool IsLetterI() const {
        return M1 > config.I.M1Min &&
               M1 < config.I.M1Max &&
               M2 > config.I.M2Min &&
               M2 < config.I.M2Max &&
               M7 > config.I.M7Min &&
               M7 < config.I.M7Max;
    }

    bool IsLetterD() const {
        return M1 > config.D.M1Min &&
               M1 < config.D.M1Max &&
               M2 < config.D.M2Max &&
               M7 > config.D.M7Min &&
               M7 < config.D.M7Max;
    }

    bool IsWordLI() const {
        return M1 > config.LI.M1Min &&
               M1 < config.LI.M1Max &&
               M7 > config.LI.M7Min &&
               M7 < config.LI.M7Max &&
               M2 > config.LI.M2Min &&
               M2 < config.LI.M2Max;
    }

    bool IsWordID() const {
        return M1 > config.ID.M1Min &&
               M1 < config.ID.M1Max &&
               M7 > config.ID.M7Min &&
               M7 < config.ID.M7Max &&
               M2 > config.ID.M2Min &&
               M2 < config.ID.M2Max;
    }

    bool IsWordLID() const {
        return M1 > config.LID.M1Min &&
               M1 < config.LID.M1Max &&
               M7 > config.LID.M7Min &&
               M7 < config.LID.M7Max &&
               M2 > config.LID.M2Min &&
               M2 < config.LID.M2Max;
    }

private:
    const std::vector<cv::Point2i> pixels;

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
