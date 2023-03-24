//
// Created by Thorsten Claus on 21.03.23.
//

#include "DelayedQueryTimer.h"
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

DelayedQueryTimer::DelayedQueryTimer(const BMessenger &messenger) {
    DelayedQueryTimer::fMessenger = messenger;
    std::thread worker(RunQueryAfterLastCharacterDelay);
}

DelayedQueryTimer::~DelayedQueryTimer() {
    fStopThread = true;
}

void DelayedQueryTimer::RunQueryAfterLastCharacterDelay() {
    while (!fStopThread) {

        // Warte bis der Query string sich verändert hat
        while (fLastSearchedQueryString->compare(*fQueryString)) {
            std::this_thread::sleep_for(DelayedQueryTimer::fDelayBeforeSendQuery);
            std::cout << "Query string changed" << std::endl;
        }

        // Ist die Zeitspanne abgelaufen? wenn nein, warte noch ein bischen
        timepoint now = std::chrono::high_resolution_clock::now();
        while ((now - fLastCharacterReceived) < fDelayBeforeSendQuery) {
            std::cout << "Wait until delay reached" << std::endl;
            timeDiffInMilli sleepTime =
                    fDelayBeforeSendQuery - (now - fLastCharacterReceived);
            if (sleepTime > 0ms) {
                std::this_thread::sleep_for(sleepTime);
            }
        }
        // Zweite Schranke, in de Zwischenzeit könnte ja ein neues Zeichen reingekommn sein
        if ((now - fLastCharacterReceived) < fDelayBeforeSendQuery) {
            fLastSearchedQueryString = fQueryString;
            std::cout << "Run Query now" << std::endl;
            // Run Query
        }
    }
}

void DelayedQueryTimer::RunQuery(std::string *queryString) {
    fQueryString = queryString;
    fLastCharacterReceived = std::chrono::high_resolution_clock::now();
}