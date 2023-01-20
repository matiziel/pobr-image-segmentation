//
// Created by mateusz on 20.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_RECOGNITION_H
#define POBR_IMAGE_SEGMENTATION_RECOGNITION_H

#include <vector>
#include <deque>
#include "Segment.h"

class Recognition {

public:
    static std::vector<Segment> RecognizeLogo(const std::vector<Segment> &segments) {
        std::vector<Segment> logoSegments = GetLogoSegments(segments);
        return segments;
//        return MergeCommonSegments(logoSegments);
    }
private:

    static std::vector<Segment> GetLogoSegments(const std::vector<Segment> &segments) {
        std::vector<Segment> logoSegments;

        for (const auto &segment : segments) {
            if (segment.IsLetterL())
                logoSegments.push_back(segment);
            else if (segment.IsLetterI())
                logoSegments.push_back(segment);
            else if (segment.IsLetterD())
                logoSegments.push_back(segment);
            else if (segment.IsWordLI())
                logoSegments.push_back(segment);
            else if (segment.IsWordID())
                logoSegments.push_back(segment);
            else if (segment.IsWordLID())
                logoSegments.push_back(segment);
        }
        return logoSegments;
    }

    static std::vector<Segment> MergeCommonSegments(std::vector<Segment> &segments) {
        std::vector<Segment> newSegments;

        std::deque<Segment> segmentQueue;
        segmentQueue.push_back(segments.back());
        segments.pop_back();

        while (!segmentQueue.empty()) {
            auto current = segmentQueue.front();
            segmentQueue.pop_front();

            std::vector<Segment> notCommonLogoSegments;

            for (auto segment : segments) {
                if (Segment::ArePartOfLogo(current, segment))
                    newSegments.push_back(current.Merge(segment));
                else
                    notCommonLogoSegments.push_back(segment);
            }

            segments.clear();
            if (notCommonLogoSegments.empty())
                continue;

            for (auto &segment : notCommonLogoSegments)
                segments.push_back(segment);

            segmentQueue.push_back(segments.back());
            segments.pop_back();
        }

        return newSegments;
    }

};


#endif //POBR_IMAGE_SEGMENTATION_RECOGNITION_H
