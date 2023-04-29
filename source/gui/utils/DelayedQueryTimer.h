//
// Created by Thorsten Claus on 21.03.23.
//

#ifndef STOCKS_TIMER_H
#define STOCKS_TIMER_H

#include "BaseThreadedJob.h"
#include <chrono>
#include "Messenger.h"

using namespace std::chrono_literals;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
typedef std::chrono::duration<double, std::milli> timeDiffMs;

class DelayedQueryTimer : public BaseThreadedJob {
public:
    explicit DelayedQueryTimer(const BHandler *handler);

    void ExecuteJob() override;

    /**
     * Starts a query after a delay with the new queryString.
     * If this methods is called again with a different query string before the internal delay has been reached,
     * the delay timer restarts again.
     * @param queryString
     */
    void RunQuery(std::string *queryString);

private:

    void RunQueryAfterLastCharacterDelay();

    void WaitUntilCharacterDelayExpired() const;

    void WaitForChangedQueryString() const;

    timeDiffMs CalculateElapsedTimeDifference() const;

    void NotifyForQuery() const;

    void NotifyForQueryWhenElapsed();

    bool IsQueryValid(const std::string *query) const;

private:

    BMessenger *fMessenger;

    std::string *fQueryString;
    std::string *fLastSearchedQueryString;
    timePoint fLastCharacterReceived;
    constexpr static
    std::chrono::duration<double, std::milli> fDelayBeforeSendQuery = 400ms;
};

enum DelayedQueryTimerMessages {
    CHARACTER_DELAY_EXPIRED = 'DTSS'
};

static const char *const SEARCH_FOR_TEXT = "SearchForText";
#endif //STOCKS_TIMER_H
