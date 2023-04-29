//
// Created by Thorsten Claus on 28.04.23.
//

#ifndef STOCKS_QUOUTEUPDATEJOB_H
#define STOCKS_QUOUTEUPDATEJOB_H

#include "BaseThreadedJob.h"
#include "Quote.h"
#include "StockConnector.h"

#include <chrono>
#include "Messenger.h"

using namespace std::chrono_literals;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;

class QuoteUpdateJob : public BaseThreadedJob {
public:
    explicit QuoteUpdateJob(BHandler *handler);

    void ExecuteJob() override;

private:
    void UpdateLoop();

    void CheckQuotesToUpdate();

    bool IsQuoteUpdateExpired(Quote &quote);

private:
    StockConnector *fStockConnector;

    constexpr static
    std::chrono::duration<double, std::milli> fDelayBeforeNextLoop = 1s;

    // every 5 minutes
    // Am Wochenende kann das Update-Interval länger sein
    std::chrono::duration<double, std::milli> fUpdateCycleTime = 1s * 60 * 5;

    void RequestUpdateQuoteDetails(Quote *const &quote);

    bool IsQuoteUpdateInProgress(Quote &quote);
};


#endif //STOCKS_QUOUTEUPDATEJOB_H
