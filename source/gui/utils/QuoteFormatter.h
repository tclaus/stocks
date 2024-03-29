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
     * Formats a number to an integer string value
     * @param number
     * @return a formatted string with groups digits.
     */
    static char *NumberToString(float number);

    /**
     * Generates a greenish color for values lesser than zero, and a black (default) color for values higher or exact
     * zero
     * @param value a float value from a negative to any positive value
     * @return a color to print out string labels
     */
    static rgb_color GainLossColor(float value);

    /**
     * Converts a large number to a human readable format by using a number name instead the large number.
     * E.g.: a number 1.234.567 will become the string 1.2 million".
     * If the provided number seems to be zero, a zero is returned. If the number is NaN an empty character is returned
     * @param largeNumber any number
     * @return A string
     */
    static char *HumanReadableLargeNumber(float largeNumber);

};

#endif //STOCKS_QUOTEFORMATTER_H
