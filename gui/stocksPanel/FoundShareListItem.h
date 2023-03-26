//
// Created by Thorsten Claus on 15.02.23.
//

#ifndef STOCKS_FOUNDSHARELISTITEM_H
#define STOCKS_FOUNDSHARELISTITEM_H

#include "ListItemDrawer.h"
#include "../../model/Quote.h"

#include "QuoteFormatter.h"
#include <View.h>
#include <ListItem.h>
#include <ListView.h>
#include <CheckBox.h>

class FoundShareListItem : public BListItem {

public:
    explicit FoundShareListItem(Quote *quote);

    FoundShareListItem();

    ~FoundShareListItem() override;

    void DrawItem(BView *owner, BRect frame,
                  bool complete) override;

    void DrawDividingLine(BView *owner, const BRect &frame);


    void Update(BView *owner, const BFont *font) override;

    void DrawCompanyName(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void SetQuote(Quote *quote);

    Quote *GetQuote();

protected:

private:
    void DrawFirstLine(const BRect &frame);

    void DrawBackground(BListView *parent, const BRect &frame, ListItemDrawer *drawer);

    void CalcAndStoreCellHeight(const BFont *font, alignment alignment);

    void AddRowHeight(int rowNum, float cellHeight);

    float CalcTotalRowHeight();

private:
    Quote *fQuote;
    QuoteFormatter *fQuoteFormatter;
    ListItemDrawer *fListItemDrawer;
    float fRowSizes[2];
    float fLastWidth;

    BCheckBox *fCheckbox;

    void MakeLineColor(BView *owner) const;

    BPoint CalcPointLeftTop(const BRect &frame) const;

    BPoint CalcPointRightTop(const BRect &frame) const;

    BString *CreateFirstLineText() const;

    void InitItemDrawer(const BListView *parent);
};

#endif //STOCKS_FOUNDSHARELISTITEM_H
