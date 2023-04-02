//
// Created by Thorsten Claus on 02.04.23.
//

#include "SelectionOfSymbols.h"

SelectionOfSymbols::SelectionOfSymbols()
        :
        fUsersSelectionOfSymbols(new std::map<char, bool>) {
}

SelectionOfSymbols::~SelectionOfSymbols() {
    delete fUsersSelectionOfSymbols;
}

void
SelectionOfSymbols::Clear() {
    fUsersSelectionOfSymbols->clear();
}

void
SelectionOfSymbols::ToggleUserSelection(const char &symbol) {
    auto value = fUsersSelectionOfSymbols->find(symbol);
    if (value == fUsersSelectionOfSymbols->end()) {
        fUsersSelectionOfSymbols->insert_or_assign(symbol, true);
        return;
    }
    fUsersSelectionOfSymbols->insert_or_assign(symbol, !value->second);
}