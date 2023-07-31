//
// Created by Thorsten Claus on 28.04.23.
//

#include "BaseThreadedJob.h"

BaseThreadedJob::BaseThreadedJob() :
        fThread(nullptr),
        fStopThread(false) {}

BaseThreadedJob::~BaseThreadedJob() {
    fStopThread = true;
    delete fThread;
}

bool
BaseThreadedJob::ShouldStopThread() const {
    return fStopThread;
}

void
BaseThreadedJob::StartThread() {
    fThread = new std::thread([this]() { ExecuteJob(); });
}

void
BaseThreadedJob::StopThread() {
    fStopThread = true;
}