//
// Created by Thorsten Claus on 01.05.23.
//

#ifndef STOCKS_DETAILSCHART_H
#define STOCKS_DETAILSCHART_H

#include <View.h>
#include "Quote.h"

class DetailsChart : public BView {
public:
    DetailsChart();

/**
 * Sets the current active quote to view its details.
 * @param quote The quote to show details.
 */
    void SetActiveQuote(Quote &quote);

};


#endif //STOCKS_DETAILSCHART_H
