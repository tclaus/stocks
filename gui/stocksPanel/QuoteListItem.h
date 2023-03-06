//
// Created by Thorsten Claus on 15.02.23.
//

#ifndef STOCKS_QUOTELISTITEM_H
#define STOCKS_QUOTELISTITEM_H

#include <View.h>
#include <ListItem.h>
#include "Quote.h"
#include "ListItemDrawer.h"


static const int FONT_SIZE_COMPANY_NAME = 12;
static const int FONT_SIZE_SYMBOL_NAME = 15;
static const int FONT_SIZE_PRICE = 15;

class QuoteListItem : public BListItem {

public:
    QuoteListItem(Quote *quote);

    QuoteListItem();

    ~QuoteListItem();

    void DrawItem(BView *owner, BRect frame,
                  bool complete) override;

    void DrawSymbol(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void Update(BView *owner, const BFont *font) override;

    void DrawCompanyName(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    // (DrawChart(BRect frame))
    void DrawLatestPrice(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void DrawChange(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void DrawText(BRect frame, DrawItemSettings settings);

    void SetQuote(Quote *quote);

    Quote *GetQuote();

protected:

private:
    void CalcAndStoreCellHeight(const BFont *font, alignment alignment);

    void AddRowHeight(int rowNum, float cellHeight);

    float CalcTotalRowHeight();

private:
    Quote *fQuote;
    ListItemDrawer *listItemDrawer;
    float rowSizes[2];
};

#endif //STOCKS_QUOTELISTITEM_H
