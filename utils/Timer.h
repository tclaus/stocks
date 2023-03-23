//
// Created by Thorsten Claus on 21.03.23.
//

#ifndef STOCKS_TIMER_H
#define STOCKS_TIMER_H

#include <chrono>
#include <thread>

using namespace std::chrono_literals;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timepoint;
typedef std::chrono::duration<double, std::milli> timeDiffInMilli;

class Timer {
public:
    Timer();

    ~Timer();

    void RunQuery(std::string *queryString);

private:
    static
    void RunQueryAfterLastCharacterDelay();

private:
    std::thread fTheThread;

    static
    bool fStopThread;

    static
    std::string *fQueryString;

    static
    std::string *fLastSearchedQueryString;

    static
    timepoint fLastCharacterReceived;

    static
    std::thread fThread;

    constexpr static
    std::chrono::duration<double, std::milli> fDelayBeforeSendQuery = 300ms;
};


#endif //STOCKS_TIMER_H
