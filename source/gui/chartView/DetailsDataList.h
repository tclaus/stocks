//
// Created by Thorsten Claus on 01.05.23.
//

#ifndef STOCKS_DETAILSDATALIST_H
#define STOCKS_DETAILSDATALIST_H

#include <View.h>
#include "Quote.h"

class DetailsDataList : public BView {
public:

    DetailsDataList();

    /**
     * Sets the current active quote to view its details.
     * @param quote The quote to show details.
     */
    void SetActiveQuote(Quote &quote);
    
};


#endif //STOCKS_DETAILSDATALIST_H
