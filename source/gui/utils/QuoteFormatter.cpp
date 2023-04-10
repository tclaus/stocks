//
// Created by Thorsten Claus on 06.03.23.
//

#include "QuoteFormatter.h"
#include <iostream>

QuoteFormatter::QuoteFormatter(Quote *quote)
        : fQuote(quote) {
}

const char *
QuoteFormatter::ChangePercentageToString() const {
    char *changeString = new char[12];
    std::sprintf(changeString, "%+.2f%%", fQuote->changesPercentage);
    return changeString;
}

const rgb_color *
QuoteFormatter::ChangeBackground() const {
    rgb_color *rectColor = new rgb_color();

    if (fQuote->change >= 0.0f) {
        rectColor->set_to(101, 196, 102); // A green tone TODO: make a constant
    } else {
        rectColor->set_to(235, 78, 61); // A red tone
    }

    return rectColor;
}