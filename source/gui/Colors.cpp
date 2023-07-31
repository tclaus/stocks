//
// Created by Thorsten Claus on 30.07.23.
//

#include "Colors.h"

rgb_color
Colors::Gridline() {
    return rgb_color{100, 100, 200, 255};
}

rgb_color
Colors::PlotGain() {
    return PriceGain();
}

rgb_color
Colors::PlotLoss() {
    return PriceLoss();
}

rgb_color
Colors::PriceGain() {
    return rgb_color{101, 196, 102, 255};
}

rgb_color
Colors::PriceLoss() {
    return rgb_color{235, 78, 61, 255};
}

rgb_color
Colors::LowColor() {
    return rgb_color{255, 255, 255, 255};
}

rgb_color
Colors::HighColor() {
    return rgb_color{0, 0, 0, 255};;
}