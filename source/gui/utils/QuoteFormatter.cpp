//
// Created by Thorsten Claus on 06.03.23.
//


#include "QuoteFormatter.h"
#include "../Colors.h"

#include <sstream>
#include <locale>
#include <cmath>
#include <vector>

struct dottedNumber : std::numpunct<char> {
    char do_thousands_sep() const override { return '.'; } // Separate by dots
    std::string do_grouping() const override { return "\3"; } // Three numbers together
    static void imbue(std::ostream &os) {
        os.imbue(std::locale(os.getloc(), new dottedNumber));
    }
};

char *
QuoteFormatter::PercentageToString(float percentValue) {
    if (percentValue == NAN) {
        return new char('-');
    }
    char *changeString = new char[12];
    std::sprintf(changeString, "%+.2f%%", percentValue);
    return changeString;
}

char *
QuoteFormatter::CurrencyToString(float currencyValue) {
    if (currencyValue == NAN) {
        return new char('-');
    }

    std::stringstream stringStream;
    dottedNumber::imbue(stringStream);
    stringStream << currencyValue;
    return stringStream.str().data();
}

rgb_color
QuoteFormatter::GainLossColor(float value) {
    if (value >= 0.0f) {
        return rgb_color(Colors::PriceGain());
    } else {
        return rgb_color(Colors::PriceLoss());
    }
}

char *
QuoteFormatter::NumberToString(float number) {
    if (number == NAN) {
        return new char('-');
    }
    std::stringstream stringStream;
    dottedNumber::imbue(stringStream);
    stringStream << number;
    return stringStream.str().data();
}

char *
QuoteFormatter::HumanReadableLargeNumber(float largeNumber) {
    if (std::isnan(largeNumber)) {
        return new char(' ');
    }

    if (largeNumber < 1.0) {
        return new char('0');
    }

    std::vector<std::string> names{"", "Thousand", "Million", "Billion", "Trillion", "Quadrillion", "Quintillion"};
    int powerOfTens = std::floor(std::log10(largeNumber) / 3.0);
    // 0.. 999 => 0
    // 1000 99999 => 1
    std::string nameForNumber = names.at(powerOfTens);

    auto reducedNumber = (float) (largeNumber / std::pow(1000L, powerOfTens));
    char *changeString = new char[30];
    std::sprintf(changeString, "%.2f %s", reducedNumber, nameForNumber.data());
    return changeString;
}
