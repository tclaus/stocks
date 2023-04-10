//
// Created by Thorsten Claus on 09.04.23.
//

#include <cstdio>
#include "ObservableSubject.h"


ObservableSubject::ObservableSubject() = default;

ObservableSubject::~ObservableSubject() {
    fObservers.clear();
}

void
ObservableSubject::Attach(Observer *observer) {
    fObservers.push_back(observer);
}

void
ObservableSubject::Detach(Observer *observer) {
    fObservers.remove(observer);
}

void
ObservableSubject::Notify() {
    printf("Notify for change in quote!\n");
    for (auto const &iterator: fObservers) {
        iterator->UpdateStatus();
    }
}