//
// Created by mateusz on 14.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_COLOURPROVIDER_H
#define POBR_IMAGE_SEGMENTATION_COLOURPROVIDER_H

#include "ColourHLS.h"


class ColourProvider {
public:
    ColourProvider() : colour(180, 255, 255) {}

    ColourHLS GetColour() {
        if (colour.S > 0) {
            colour.S--;
        }
        else if (colour.L > 0) {
            colour.L--;
            colour.S = 255;
        }
        else if (colour.H > 1) {
            colour.H--;
            colour.L = 255;
            colour.S = 255;
        }
        else
            throw std::out_of_range("End of colour range");

        return colour;
    }


private:
    ColourHLS colour;
};


#endif //POBR_IMAGE_SEGMENTATION_COLOURPROVIDER_H
