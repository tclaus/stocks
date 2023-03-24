//
// Created by Thorsten Claus on 21.03.23.
//

#include "DelayedQueryTimer.h"
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

DelayedQueryTimer::DelayedQueryTimer(const BHandler *handler)
        : fMessenger(new BMessenger(handler)),
          fStopThread(false),
          fQueryString((std::string *) ""),
          fLastSearchedQueryString((std::string *) "") {
}

void
DelayedQueryTimer::StartThread() {
    fThread = new std::thread([this]() { RunQueryAfterLastCharacterDelay(); });
}

void
DelayedQueryTimer::StopThread() {
    fStopThread = true;
}

DelayedQueryTimer::~DelayedQueryTimer() {
    fStopThread = true;
    delete fThread;
}

void
DelayedQueryTimer::RunQuery(std::string *queryString) {
    fQueryString = queryString;
    fLastCharacterReceived = std::chrono::high_resolution_clock::now();
}

void
DelayedQueryTimer::RunQueryAfterLastCharacterDelay() {
    while (!fStopThread) {
        WaitForChangedQueryString();
        WaitUntilCharacterDelayExpired();
        NotifyForQueryWhenElapsed();
    }
}

void
DelayedQueryTimer::WaitForChangedQueryString() const {
    while (fLastSearchedQueryString == fQueryString) {
        std::this_thread::sleep_for(fDelayBeforeSendQuery);
        std::cout << ".";
    }
}

void
DelayedQueryTimer::WaitUntilCharacterDelayExpired() const {
    timeDiffMs timeSinceLastCharacterReceived = CalculateElapsedTimeDifference();
    while (timeSinceLastCharacterReceived < fDelayBeforeSendQuery) {
        std::cout << "DQT: Wait until delay expired" << std::endl;
        timeDiffMs sleepTime = fDelayBeforeSendQuery - timeSinceLastCharacterReceived;
        if (sleepTime > 1ms && sleepTime < fDelayBeforeSendQuery) {
            std::this_thread::sleep_for(sleepTime);
        }
        timeSinceLastCharacterReceived = CalculateElapsedTimeDifference();
    }
}

timeDiffMs
DelayedQueryTimer::CalculateElapsedTimeDifference() const {
    timePoint now = std::chrono::high_resolution_clock::now();
    timeDiffMs timeSinceLastCharacterReceived = (now - fLastCharacterReceived);
    return timeSinceLastCharacterReceived;
}

void
DelayedQueryTimer::NotifyForQueryWhenElapsed() {
    timePoint now = std::chrono::high_resolution_clock::now();
    if ((now - fLastCharacterReceived) > fDelayBeforeSendQuery) {
        fLastSearchedQueryString = fQueryString;
        std::cout << "DQT: Run Query now" << std::endl;
        NotifyForQuery();
    }
}

void
DelayedQueryTimer::NotifyForQuery() const {
    if (IsQueryValid(fQueryString)) {
        BMessage message(CHARACTER_DELAY_EXPIRED);
        message.AddString(SEARCH_FOR_TEXT, fQueryString->c_str());
        fMessenger->SendMessage(&message);
    }
}

bool
DelayedQueryTimer::IsQueryValid(const std::string *query) const {
    if (query->empty()) {
        return false;
    }
    if (query->find(' ') != std::string::npos) {
        return false;
    }
    if (query->find('?') != std::string::npos) {
        return false;
    }
    if (query->find('&') != std::string::npos) {
        return false;
    }
    return true;
}