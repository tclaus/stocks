//
// Created by Thorsten Claus on 15.02.23.
//

#ifndef STOCKS_QUOTELISTITEM_H
#define STOCKS_QUOTELISTITEM_H

#include "ListItemDrawer.h"
#include "QuoteFormatter.h"
#include "ListItemConstants.h"

#include <View.h>
#include <ListItem.h>
#include <ListView.h>
#include "Quote.h"

class QuoteListItem : public BListItem {

public:
    explicit QuoteListItem(Quote *quote);

    QuoteListItem();

    ~QuoteListItem() override;

    void DrawItem(BView *owner, BRect frame,
                  bool complete) override;

    void DrawDividingLine(BView *owner, const BRect &frame);

    void DrawSymbol(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void Update(BView *owner, const BFont *font) override;

    void DrawCompanyName(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void DrawLatestPrice(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void DrawChange(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void SetQuote(Quote *quote);

    Quote *GetQuote();

protected:

private:
    void DrawBackground(BListView *parent, const BRect &frame, ListItemDrawer *drawer);

    void CalcAndStoreCellHeight(const BFont *font, alignment alignment);

    void AddRowHeight(int rowNum, float cellHeight);

    float CalcTotalRowHeight();

private:
    Quote *fQuote;
    QuoteFormatter *fQuoteFormatter;
    ListItemDrawer *listItemDrawer;
    float rowSizes[2];
    float lastWidth;

    void MakeLineColor(BView *owner) const;

    BPoint CalcLineLeftTop(const BRect &frame) const;

    BPoint CalcLineRightTop(const BRect &frame) const;

};

#endif //STOCKS_QUOTELISTITEM_H
