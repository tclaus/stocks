//
// Created by Thorsten Claus on 01.03.23.
//

#ifndef STOCKS_QUOTE_H
#define STOCKS_QUOTE_H

#include "ObservableSubject.h"
#include <String.h>
#include <string>
#include <chrono>

using namespace std::chrono_literals;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
typedef std::chrono::duration<double, std::milli> timeDiffMs;

class Quote : public ObservableSubject {

public:
    Quote();

    explicit Quote(BString &symbol);

    explicit Quote(std::string *symbol);

    Quote(const Quote &) = delete;

    void SetLastUpdatedTimePoint();

    timePoint GetLastUpdatedTimePoint();

    BString *symbol;
    BString *market;
    BString *companyName;
    BString *currency;
    float change;
    float changesPercentage;
    float latestPrice;
    float dayLow;
    float dayHigh;
    float open;
    float previousClose;
    float volume;

    bool isWaitingForRequest;

private:
    timePoint lastUpdatedAt;
};


#endif //STOCKS_QUOTE_H
