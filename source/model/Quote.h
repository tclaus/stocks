//
// Created by Thorsten Claus on 01.03.23.
//

#ifndef STOCKS_QUOTE_H
#define STOCKS_QUOTE_H

#include <String.h>
#include <string>
#include <chrono>

using namespace std::chrono_literals;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
typedef std::chrono::duration<double, std::milli> timeDiffMs;

class Quote {

public:
    Quote();

    explicit Quote(BString &symbol);

    explicit Quote(std::string *symbol);

    void SetLastUpdatedTimePoint();

    BString *symbol;
    BString *market;
    BString *companyName;
    BString *currency;
    timePoint lastUpdated;
    double change;
    double latestPrice;
    double high;
    double low;

    // Timestamp / Chrono / long (milliseconds?)
};


#endif //STOCKS_QUOTE_H
