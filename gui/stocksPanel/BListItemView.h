//
// Created by Thorsten Claus on 15.02.23.
//

#ifndef STOCKS_BLISTITEMVIEW_H
#define STOCKS_BLISTITEMVIEW_H

#include <View.h>
#include <ListItem.h>

class BListItemView : public BListItem {

public:
    BListItemView(BView *view);

    virtual void DrawItem(BView *owner, BRect frame,
                          bool complete = false) override;

    void SetView(BView *view);

    void Update(BView *owner, const BFont *font) override;


protected:

private:
    BListItemView(const BListItemView &item);

    BListItemView &operator=(const BListItemView &item);

private:
    BView *_view;
};


#endif //STOCKS_BLISTITEMVIEW_H
