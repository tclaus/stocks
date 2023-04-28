//
// Created by Thorsten Claus on 28.04.23.
//

#ifndef STOCKS_BASETHREADEDJOB_H
#define STOCKS_BASETHREADEDJOB_H

#include <thread>

class BaseThreadedJob {
public:

    BaseThreadedJob();

    ~BaseThreadedJob();

    void StartThread();

    void StopThread();

    bool ShouldStopThread() const;

    virtual void ExecuteJob() = 0;

private:
    std::thread *fThread;
    bool fStopThread;
};


#endif //STOCKS_BASETHREADEDJOB_H
