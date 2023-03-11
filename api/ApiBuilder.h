//
// Created by Thorsten Claus on 11.03.23.
//

#ifndef STOCKS_APIBUILDER_H
#define STOCKS_APIBUILDER_H


#include "StockConnector.h"

class ApiBuilder {
public:
    StockConnector *CreateStockConnector();
};


#endif //STOCKS_APIBUILDER_H
