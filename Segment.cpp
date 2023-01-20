//
// Created by mateusz on 20.01.23.
//
#include "Segment.h"

Segment::Segment(const std::vector<cv::Point2i> &pixels)
        : pixels(pixels), config() {}

void Segment::Init() {
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

double Segment::Area() const {
    return m00;
}

BoundingBox Segment::GetBoundingBox() const {
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

void Segment::Merge(const Segment &segment) {
    pixels.insert(pixels.end(), segment.pixels.begin(), segment.pixels.end());
    Init();
}

void Segment::SetSegmentBlack(cv::Mat &image) const {
    cv::Mat_<cv::Vec3b> imageVector = image;
    for (cv::Point2i pixel: pixels)
        ColourHLS::SetColour(imageVector(pixel.y, pixel.x), ColourHLS::GetBlack());
    image = imageVector;
}

bool Segment::IsLetterL() const {
    return M1 > config.L.M1Min &&
           M1 < config.L.M1Max &&
           M7 > config.L.M7Min &&
           M7 < config.L.M7Max &&
           M2 < config.L.M2Max;
}

bool Segment::IsLetterI() const {
    return M1 > config.I.M1Min &&
           M1 < config.I.M1Max &&
           M2 > config.I.M2Min &&
           M2 < config.I.M2Max &&
           M7 > config.I.M7Min &&
           M7 < config.I.M7Max;
}

bool Segment::IsLetterDOT() const {
    return M1 > config.DOT.M1Min &&
           M1 < config.DOT.M1Max &&
           M2 < config.DOT.M2Max &&
           M7 > config.DOT.M7Min &&
           M7 < config.DOT.M7Max;
}

bool Segment::IsLetterD() const {
    return M1 > config.D.M1Min &&
           M1 < config.D.M1Max &&
           M2 < config.D.M2Max &&
           M7 > config.D.M7Min &&
           M7 < config.D.M7Max;
}

bool Segment::IsWordLI() const {
    return M1 > config.LI.M1Min &&
           M1 < config.LI.M1Max &&
           M7 > config.LI.M7Min &&
           M7 < config.LI.M7Max &&
           M2 > config.LI.M2Min &&
           M2 < config.LI.M2Max;
}

bool Segment::IsWordID() const {
    return M1 > config.ID.M1Min &&
           M1 < config.ID.M1Max &&
           M7 > config.ID.M7Min &&
           M7 < config.ID.M7Max &&
           M2 > config.ID.M2Min &&
           M2 < config.ID.M2Max;
}

bool Segment::IsWordLID() const {
    return M1 > config.LID.M1Min &&
           M1 < config.LID.M1Max &&
           M7 > config.LID.M7Min &&
           M7 < config.LID.M7Max &&
           M2 > config.LID.M2Min &&
           M2 < config.LID.M2Max;
}

bool Segment::IsWordLIDL() const {
    return M1 > config.LIDL.M1Min &&
           M1 < config.LIDL.M1Max &&
           M7 > config.LIDL.M7Min &&
           M7 < config.LIDL.M7Max &&
           M2 > config.LIDL.M2Min &&
           M2 < config.LIDL.M2Max &&
           M3 < config.LIDL.M3Max &&
           M4 < config.LIDL.M4Max;
}

bool Segment::ArePartOfLogo(const Segment &first, const Segment &second) {
    const auto firstBox = first.GetBoundingBox();
    const auto secondBox = second.GetBoundingBox();

    const auto firstCenter = firstBox.GetCenterPoint();
    const auto secondCenter = secondBox.GetCenterPoint();

    return
            static_cast<double>(std::abs(firstCenter.y - secondCenter.y)) <=
            5.5 * static_cast<double>(std::min(firstBox.GetHeight(), secondBox.GetHeight())) &&
            static_cast<double>(std::abs(firstCenter.x - secondCenter.x)) <=
            5.5 * static_cast<double>(std::min(firstBox.GetWidth(), secondBox.GetWidth()));
}


