//
// Created by Thorsten Claus on 02.04.23.
//

#include "SelectionOfSymbols.h"

SelectionOfSymbols::SelectionOfSymbols()
        :
        fUsersSelectionOfSymbols(new std::map<std::string, bool>) {
}

SelectionOfSymbols::~SelectionOfSymbols() {
    delete fUsersSelectionOfSymbols;
}

void
SelectionOfSymbols::Clear() {
    fUsersSelectionOfSymbols->clear();
}

std::list<std::string> *
SelectionOfSymbols::ListToBeAdded() {
    auto *listOfSymbols = new std::list<std::string>();
    for (auto const &pair: *fUsersSelectionOfSymbols) {
        if (pair.second) {
            listOfSymbols->push_back(
                    std::string(pair.first)
            );
        }
    }
    return listOfSymbols;
}

std::list<std::string> *
SelectionOfSymbols::ListToBeRemoved() {
    auto *listOfSymbols = new std::list<std::string>();
    for (auto const &pair: *fUsersSelectionOfSymbols) {
        if (!pair.second) {
            listOfSymbols->push_back(
                    std::string(pair.first)
            );
        }
    }
    return listOfSymbols;
}

void
SelectionOfSymbols::ToggleUserSelection(const std::string &symbol) {
    auto value = fUsersSelectionOfSymbols->find(symbol);
    if (value == fUsersSelectionOfSymbols->end()) {
        fUsersSelectionOfSymbols->insert_or_assign(symbol, true);
        return;
    }
    fUsersSelectionOfSymbols->insert_or_assign(symbol, !value->second);
}