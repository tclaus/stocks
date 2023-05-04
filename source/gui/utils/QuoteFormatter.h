//
// Created by Thorsten Claus on 06.03.23.
//

#ifndef STOCKS_QUOTEFORMATTER_H
#define STOCKS_QUOTEFORMATTER_H

#include "Quote.h"
#include <GraphicsDefs.h>

class QuoteFormatter {
public:
    QuoteFormatter() = delete;

    /**
     * Formats a float to a percentage string. Float: 2.25 => "2.25 %"
     * @param value a float representing a percent
     * @return a formatted string with percent sign after a space
     */
    static char *PercentageToString(float value);

    static char *CurrencyToString(float currencyValue);

    /**
     * Generates a greenish color for values lesser than zero, and a black (default) color for values higher or exact
     * zero
     * @param value a float value from a negative to any positive value
     * @return a color to print out string labels
     */
    static rgb_color *ColorByValue(float value);

};

#endif //STOCKS_QUOTEFORMATTER_H
