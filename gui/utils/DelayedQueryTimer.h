//
// Created by Thorsten Claus on 21.03.23.
//

#ifndef STOCKS_TIMER_H
#define STOCKS_TIMER_H

#include <chrono>
#include <thread>
#include "Messenger.h"

using namespace std::chrono_literals;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timepoint;
typedef std::chrono::duration<double, std::milli> timeDiffInMilli;

class DelayedQueryTimer {
public:
    explicit DelayedQueryTimer(const BMessenger &messenger);

    ~DelayedQueryTimer();

    /**
     * Starts a query after a delay with the new queryString.
     * If this methods is called again with a different query string before the internal delay has been reached,
     * the delay timer restarts again.
     * @param queryString
     */
    void RunQuery(std::string *queryString);

private:
    static
    void RunQueryAfterLastCharacterDelay();

private:
    const std::thread fTheThread;

    static
    BMessenger &fMessenger;

    static
    bool fStopThread;

    static
    std::string *fQueryString;

    static
    std::string *fLastSearchedQueryString;

    static
    timepoint fLastCharacterReceived;

    constexpr static
    std::chrono::duration<double, std::milli> fDelayBeforeSendQuery = 300ms;
};


#endif //STOCKS_TIMER_H
