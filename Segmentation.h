//
// Created by mateusz on 14.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_SEGMENTATION_H
#define POBR_IMAGE_SEGMENTATION_SEGMENTATION_H

#include <vector>
#include <deque>
#include <algorithm>
#include <array>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ColourHLS.h"
#include "Segment.h"
#include "ColourProvider.h"
#include "BoundingBox.h"

class Segmentation {
public:

    static std::vector<Segment> FindSegments(cv::Mat &image) {
        ColourProvider colourProvider;
        std::vector<Segment> segments;

        cv::Mat_<cv::Vec3b> imageVector = image;
        for (int y = 0; y < imageVector.rows; y++) {
            for (int x = 0; x < imageVector.cols; x++) {
                if (!ColourHLS::GetColour(imageVector(y, x)).IsWhite())
                    continue;

                ColourHLS colour = colourProvider.GetColour();
                Segment segment = FloodFill(image, x, y, colour);

                if (segment.Area() < 32) {
                    SetSegmentBlack(image, segment);
                }
                else {
                    segments.push_back(segment);
//                    BoundingBox::DrawBoundingBox(image, ColourHLS::GetRed(), segment.GetBoundingBox());
                }
            }
        }
        image = imageVector;
        return segments;
    }

private:
    static Segment FloodFill(cv::Mat &image, int xStart, int yStart, ColourHLS colour) {
        std::vector<cv::Point2i> segmentPixels;
        std::deque<cv::Point2i> pixels;
        pixels.push_back(cv::Point2i(xStart, yStart));

        cv::Mat_<cv::Vec3b> imageVector = image;


        while (!pixels.empty()) {
            auto current = pixels.front();
            pixels.pop_front();
            ColourHLS::SetColour(imageVector(current.y, current.x), colour);

            segmentPixels.push_back(current);

            std::array<cv::Point2i, 4> neighbours = GetNeighbours(current.x, current.y);
            for (cv::Point2i neighbour: neighbours) {
                if (!ValidateNeighbour(neighbour.x, neighbour.y, imageVector.rows, imageVector.cols))
                    continue;

                if (!DequeContains(pixels, neighbour) &&
                    ColourHLS::GetColour(imageVector(neighbour.y, neighbour.x)).IsWhite()) {
                    pixels.push_back(neighbour);
                }
            }
        }
        image = imageVector;
        auto segment = Segment(segmentPixels, colour);
        segment.Init();
        return segment;
    }

    static std::array<cv::Point2i, 4> GetNeighbours(int x, int y) {
        return {
                cv::Point2i(x + 1, y),
                cv::Point2i(x - 1, y),
                cv::Point2i(x, y + 1),
                cv::Point2i(x, y - 1)
        };
    }

    static bool ValidateNeighbour(int x, int y, int rows, int cols) {
        return x >= 0 && x < cols && y >= 0 && y < rows;
    }

    static bool DequeContains(std::deque<cv::Point2i> deque, cv::Point2i point) {
        return std::any_of(
                deque.cbegin(),
                deque.cend(),
                [&](cv::Point2i p) {
                    return p.x == point.x && p.y == point.y;
                });
    }

    static void SetSegmentBlack(cv::Mat &image, Segment segment) {
        cv::Mat_<cv::Vec3b> imageVector = image;
        for (cv::Point2i pixel: segment.GetPixels())
            ColourHLS::SetColour(imageVector(pixel.y, pixel.x), ColourHLS::GetBlack());
        image = imageVector;
    }
};


#endif //POBR_IMAGE_SEGMENTATION_SEGMENTATION_H
