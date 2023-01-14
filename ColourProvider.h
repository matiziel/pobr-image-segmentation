//
// Created by mateusz on 14.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_COLOURPROVIDER_H
#define POBR_IMAGE_SEGMENTATION_COLOURPROVIDER_H

#include "ColourHLS.h"


class ColourProvider {
public:
    ColourProvider() : colour(0, 0, 0) {}

    ColourHLS GetColour() {
        if (colour.H < ColourHLS::MaxH() - 1)
            colour.H++;
        else if (colour.L < ColourHLS::MaxL())
            colour.L++;
        else if (colour.L < ColourHLS::MaxS())
            colour.S++;
        else
            throw std::out_of_range("End of colour range");

        return colour;
    }

private:
    ColourHLS colour;
};


#endif //POBR_IMAGE_SEGMENTATION_COLOURPROVIDER_H
