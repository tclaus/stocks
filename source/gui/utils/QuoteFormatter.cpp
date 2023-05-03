//
// Created by Thorsten Claus on 06.03.23.
//

#include "QuoteFormatter.h"

char *QuoteFormatter::PercentageToString(float percentValue) {
    char *changeString = new char[12];
    std::sprintf(changeString, "%+.2f%%", percentValue);
    return changeString;
}

char *QuoteFormatter::CurrencyToString(float currencyValue) {
    char *currencyString = new char[12];
    std::sprintf(currencyString, "%.2f", currencyValue);
    return currencyString;
}

rgb_color *
QuoteFormatter::ColorByValue(float value) {
    auto *rectColor = new rgb_color();
    if (value >= 0.0f) {
        rectColor->set_to(101, 196, 102); // A green tone TODO: make a constant
    } else {
        rectColor->set_to(235, 78, 61); // A red tone
    }

    return rectColor;
}
