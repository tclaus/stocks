//
// Created by Thorsten Claus on 27.03.23.
//

#ifndef STOCKS_SHARELISTITEM_H
#define STOCKS_SHARELISTITEM_H

#include "Quote.h"
#include "ListItem.h"

class ShareListItem : public BListItem {

public:

    explicit ShareListItem(Quote *quote);

    /**
     * Detaches any views from parent if needed
     */
    virtual void DetachFromParent() {};

    void DrawItem(BView *owner, BRect frame,
                  bool complete) override = 0;

protected:
    Quote *fQuote;
};


#endif //STOCKS_SHARELISTITEM_H
