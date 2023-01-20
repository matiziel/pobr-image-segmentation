//
// Created by mateusz on 20.01.23.
//

#include "Recognition.h"

std::vector<Segment> Recognition::RecognizeLogo(cv::Mat &image, const std::vector<Segment> &segments) {
    std::vector<Segment> logoSegments = GetLogoSegments(image, segments);
    std::vector<Segment> mergedSegments = MergeCommonSegments(logoSegments);
    return RecognizeSegments(image, mergedSegments);
}

std::vector<Segment> Recognition::GetLogoSegments(cv::Mat &image, const std::vector<Segment> &segments) {
    std::vector<Segment> logoSegments;

    for (const auto &segment: segments) {
        if (segment.IsLetterL())
            logoSegments.push_back(segment);
        else if (segment.IsLetterI())
            logoSegments.push_back(segment);
        else if (segment.IsLetterDOT())
            logoSegments.push_back(segment);
        else if (segment.IsLetterD())
            logoSegments.push_back(segment);
        else if (segment.IsWordLI())
            logoSegments.push_back(segment);
        else if (segment.IsWordID())
            logoSegments.push_back(segment);
        else if (segment.IsWordLID())
            logoSegments.push_back(segment);
        else
            segment.SetSegmentBlack(image);

    }
    return logoSegments;
}

std::vector<Segment> Recognition::MergeCommonSegments(std::vector<Segment> &segments) {
    std::vector<Segment> newSegments;

    std::deque<Segment> segmentQueue;
    segmentQueue.push_back(segments.back());
    segments.pop_back();

    while (!segmentQueue.empty()) {
        auto current = segmentQueue.front();
        segmentQueue.pop_front();

        std::vector<Segment> notCommonLogoSegments;

        for (auto &segment: segments) {
            if (Segment::ArePartOfLogo(current, segment))
                current.Merge(segment);
            else
                notCommonLogoSegments.push_back(segment);
        }
        newSegments.push_back(current);

        segments.clear();
        if (notCommonLogoSegments.empty())
            continue;

        for (auto &segment: notCommonLogoSegments)
            segments.push_back(segment);

        segmentQueue.push_back(segments.back());
        segments.pop_back();
    }
    return newSegments;
}

std::vector<Segment> Recognition::RecognizeSegments(cv::Mat &image, std::vector<Segment> &segments) {
    std::vector<Segment> logoSegments;
    for (const Segment &segment: segments) {
        if (segment.IsWordLIDL())
            logoSegments.push_back(segment);
        else
            segment.SetSegmentBlack(image);
    }
    return logoSegments;
}
