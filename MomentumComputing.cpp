//
// Created by mateusz on 10.01.23.
//

#include "MomentumComputing.h"
#include "ColourHLS.h"


MomentumComputing::MomentumComputing(cv::Mat &image) : image(image) {
    CV_Assert(image.depth() != sizeof(uchar));
    if (this->image.channels() != 3)
        throw std::invalid_argument("Image should have 3 channels");
}

double MomentumComputing::Get_m(int p, int q, ColourHLS colour) {
    double mpq = 0;
    cv::Mat_<cv::Vec3b> imageVector = image;
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            if (ColourHLS::GetColour(imageVector(y, x)) == colour) {
                mpq += std::pow(y, q) * std::pow(x, p);
            }
        }
    }
    image = imageVector;
    return mpq;
}

double MomentumComputing::GetM1(ColourHLS colour) {
    double m_0_0 = Get_m(0, 0, colour);

    double m_0_2 = Get_m(0, 2, colour);
    double m_0_1 = Get_m(0, 1, colour);

    double m_2_0 = Get_m(2, 0, colour);
    double m_1_0 = Get_m(1, 0, colour);


    double M_0_2 = m_0_2 - m_0_1 * m_0_1 / m_0_0;
    double M_2_0 = m_2_0 - m_1_0 * m_1_0 / m_0_0;

    return (M_0_2 + M_2_0) / (m_0_0 * m_0_0);
}

double MomentumComputing::GetM7(ColourHLS colour) {
    double m_0_0 = Get_m(0, 0, colour);

    double m_0_2 = Get_m(0, 2, colour);
    double m_0_1 = Get_m(0, 1, colour);

    double m_2_0 = Get_m(2, 0, colour);
    double m_1_0 = Get_m(1, 0, colour);

    double m_1_1 = Get_m(1, 1, colour);

    double M_1_1 = m_1_1 - m_1_0 * m_0_1 / m_0_0;

    double M_0_2 = m_0_2 - m_0_1 * m_0_1 / m_0_0;
    double M_2_0 = m_2_0 - m_1_0 * m_1_0 / m_0_0;

    return (M_0_2 * M_2_0 - M_1_1 * M_1_1) / pow(m_0_0, 4);
}


