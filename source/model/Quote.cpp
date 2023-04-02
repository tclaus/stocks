//
// Created by Thorsten Claus on 01.03.23.
//

#include "Quote.h"

Quote::Quote(BString &symbol) {
    this->symbol = new BString(symbol);
}

Quote::Quote(std::string *symbol) {
    this->symbol = new BString(symbol->c_str());
}
