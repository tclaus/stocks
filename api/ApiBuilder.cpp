//
// Created by Thorsten Claus on 11.03.23.
//

#include "ApiBuilder.h"
#include "Financialmodelingprep.h"

StockConnector *ApiBuilder::CreateStockConnector(BHandler *handler) {
    // A kind of factory here
    return new Financialmodelingprep(handler);
}