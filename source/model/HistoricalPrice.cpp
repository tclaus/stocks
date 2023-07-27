//
// Created by Thorsten Claus on 19.07.23.
//

#include "HistoricalPrice.h"

HistoricalPrice::HistoricalPrice() :
        date(new BString()),
        open(0.0),
        low(0.0),
        high(0.0),
        close(0.0),
        volume(0.0) {}

void HistoricalPrice::SetDate(BString *dateValue) {
    date = dateValue;
}

BString *HistoricalPrice::GetDate() {
    return date;
}

float HistoricalPrice::GetOpen() {
    return open;
}

void HistoricalPrice::SetOpen(float openValue) {
    open = openValue;
}

void HistoricalPrice::SetLow(float lowValue) {
    low = lowValue;
}

float HistoricalPrice::GetLow() {
    return low;
}

void HistoricalPrice::SetHigh(float highValue) {
    high = highValue;
}

float HistoricalPrice::GetHigh() {
    return high;
}

void HistoricalPrice::SetClose(float closeValue) {
    close = closeValue;
}

float HistoricalPrice::GetClose() {
    return close;
}

