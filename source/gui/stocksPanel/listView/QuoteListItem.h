//
// Created by Thorsten Claus on 15.02.23.
//

#ifndef STOCKS_QUOTELISTITEM_H
#define STOCKS_QUOTELISTITEM_H

#include "ShareListItem.h"
#include "Quote.h"
#include "Observer.h"
#include "ListItemDrawer.h"
#include "QuoteFormatter.h"

#include "ListItemConstants.h"
#include <View.h>
#include <ListView.h>
#include <memory>

class QuoteListItem : public ShareListItem, public Observer {

public:
    explicit QuoteListItem(Quote *quote);

    ~QuoteListItem() override;

    void DrawItem(BView *owner, BRect frame,
                  bool complete) override;

    void DrawDividingLine(BView *owner, const BRect &frame);

    void DrawSymbol(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void DrawCompanyName(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void DrawLatestPrice(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void DrawChange(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void Update(BView *owner, const BFont *font) override;

    void UpdateStatus() override;

    Quote *GetQuote();

protected:

private:
    void DrawBackground(BListView *parent, const BRect &frame, ListItemDrawer *drawer);

    void CalcAndStoreCellHeight(const BFont *font, alignment alignment);

    void AddRowHeight(int rowNum, float cellHeight);

    float CalcTotalRowHeight();

private:
    QuoteFormatter *fQuoteFormatter;
    ListItemDrawer *listItemDrawer;
    float rowSizes[2];
    float lastWidth;

    BListView *fWeakOwner;

    void MakeLineColor(BView *owner) const;

    BPoint CalcLineLeftTop(const BRect &frame) const;

    BPoint CalcLineRightTop(const BRect &frame) const;

};

#endif //STOCKS_QUOTELISTITEM_H
