//
// Created by Thorsten Claus on 15.02.23.
//

#ifndef STOCKS_FOUNDSHARELISTITEM_H
#define STOCKS_FOUNDSHARELISTITEM_H

#include "ShareListItem.h"
#include "ListItemDrawer.h"
#include "Quote.h"
#include <string>
#include "QuoteFormatter.h"
#include <View.h>
#include <ListView.h>
#include <CheckBox.h>

class FoundShareListItem : public ShareListItem {

public:
    explicit FoundShareListItem(Quote *quote);

    ~FoundShareListItem() override;

    void DrawItem(BView *owner, BRect frame,
                  bool complete) override;

    void DrawDividingLine(BView *owner, const BRect &frame);

    void DetachFromParent() override;

    void DrawCompanyName(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment);

    void Update(BView *owner, const BFont *font) override;

    const char *SYMBOL_NAME = "Symbol name";

protected:

private:
    void DrawTopContent(const BRect &frame);

    void DrawBackground(BListView *parent, const BRect &frame, ListItemDrawer *drawer);

    void CalcAndStoreCellHeight(const BFont *font, alignment alignment);

    void AddRowHeight(int rowNum, float cellHeight);

    float CalcTotalRowHeight();

private:

    QuoteFormatter *fQuoteFormatter;
    ListItemDrawer *fListItemDrawer;
    float fRowSizes[2];
    float fLastWidth;
    float fSpaceForCheckbox;
    bool fCheckBoxAdded;
    BCheckBox *fCheckbox;

    void InitCheckbox(const Quote &quote);

    void MakeLineColor(BView *owner) const;

    BPoint CalcPointLeftTop(const BRect &frame) const;

    BPoint CalcPointRightTop(const BRect &frame) const;

    BString *CreateTopRowString() const;

    void InitItemDrawer(const BListView *parent);

    std::string GenerateCheckBoxName(const Quote &quote) const;

    void DrawDividingLineBetweenElements(BListView *parent, const int32 index, const BRect &frame);

    bool IsCheckboxAChild(const BListView *parent) const;

    BPoint LeftHorizontalCenterForCheckbox(const BRect &rect) const;

    BRect getRectWithCheckboxOffset(const BRect &rect) const;

    void DrawSecondaryContent(const BRect &frame);
};

enum FoundShareListItemEnum {
    CHECKBOX_CLICKED = 'SLIC'
};


#endif //STOCKS_FOUNDSHARELISTITEM_H
