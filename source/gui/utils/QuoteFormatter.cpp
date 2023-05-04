//
// Created by Thorsten Claus on 06.03.23.
//

#include <sstream>
#include "QuoteFormatter.h"
#include <locale>

struct dottedNumber : std::numpunct<char> {
    char do_thousands_sep() const override { return '.'; } // Separate by dots
    std::string do_grouping() const override { return "\3"; } // Three numbers together
    static void imbue(std::ostream &os) {
        os.imbue(std::locale(os.getloc(), new dottedNumber));
    }
};

char *QuoteFormatter::PercentageToString(float percentValue) {
    char *changeString = new char[12];
    std::sprintf(changeString, "%+.2f%%", percentValue);
    return changeString;
}

char *QuoteFormatter::CurrencyToString(float currencyValue) {
    std::stringstream stringStream;
    dottedNumber::imbue(stringStream);
    stringStream << currencyValue;
    return stringStream.str().data();
/**
    char *currencyString = new char[12];
    std::sprintf(currencyString, "%.2f", currencyValue);
    return currencyString;
 **/
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
