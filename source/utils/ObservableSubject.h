//
// Created by Thorsten Claus on 09.04.23.
//

#ifndef STOCKS_OBSERVABLESUBJECT_H
#define STOCKS_OBSERVABLESUBJECT_H

# include "Observer.h"
#include <list>

class ObservableSubject {
public:

    virtual void Attach(Observer *observer);

    virtual void Detach(Observer *observer);

    void Notify();

protected:
    ObservableSubject();

    ~ObservableSubject();

private:
    std::list<Observer *> fObservers;
};


#endif //STOCKS_OBSERVABLESUBJECT_H
