//
// Created by Thorsten Claus on 19.07.23.
//

#ifndef STOCKS_HISTORICALPRICE_H
#define STOCKS_HISTORICALPRICE_H

#include <String.h>

/**
 * A single datapoint for a historical price.
 * The longer time periods dont have the detailed open, low, high and volume tags.
 * The yearly timeframe only have the date and closing tag.
 */
class HistoricalPrice {

public:
    HistoricalPrice();

    void SetDate(BString *dateValue);

    BString *GetDate();

    void SetOpen(float openValue);

    float GetOpen();

    void SetLow(float lowValue);

    float GetLow();

    void SetHigh(float highValue);

    float GetHigh();

    void SetClose(float closeValue);

    float GetClose();

private:
    BString *date;
    float open;
    float low;
    float high;
    float close;
    float volume;
};


#endif //STOCKS_HISTORICALPRICE_H
