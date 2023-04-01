//
// Created by Thorsten Claus on 09.03.23.
//

#include "Portfolio.h"

#include "List.h"

void Portfolio::AddQuote(Quote *quote) {
    list->AddItem(quote);
}

void Portfolio::RemoveQuote(Quote *quote) {
    list->RemoveItem(quote);
}
