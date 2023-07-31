//
// Created by Thorsten Claus on 30.07.23.
//

#ifndef STOCKS_CHARTCOLORS_H
#define STOCKS_CHARTCOLORS_H

#include "View.h"

class Colors {
public:
    static rgb_color PlotGain();

    static rgb_color PlotLoss();

    static rgb_color Gridline();

    static rgb_color PriceGain();

    static rgb_color PriceLoss();

    static rgb_color LowColor();

    static rgb_color HighColor();
};


#endif //STOCKS_CHARTCOLORS_H
