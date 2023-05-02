//
// Created by Thorsten Claus on 15.02.23.
//

#include "QuoteListItem.h"
#include "QuoteFormatter.h"
#include <View.h>
#include <algorithm>
#include "ListView.h"

QuoteListItem::QuoteListItem(Quote *quote)
        : ShareListItem(quote),
          listItemDrawer(nullptr),
          lastWidth(0.0) {

    fQuoteFormatter = new QuoteFormatter(quote);
    quote->Attach(this);
}

QuoteListItem::~QuoteListItem() {
    fQuote->Detach(this);
    fWeakOwner = nullptr;
    delete listItemDrawer;
    delete fQuoteFormatter;
}

void
QuoteListItem::UpdateStatus() {
    if (fWeakOwner) {
        const int32 index = fWeakOwner->IndexOf(this);
        fWeakOwner->InvalidateItem(index);
    }
}

void
QuoteListItem::DrawItem(BView *owner, BRect rect, bool complete) {
    (void) complete;
    (void) rect;

    auto *parent = dynamic_cast<BListView *>(owner);
    fWeakOwner = parent;

    const int32 index = parent->IndexOf(this);
    BRect frame = parent->ItemFrame(index);

    if (listItemDrawer == nullptr) {
        listItemDrawer = new ListItemDrawer(parent);
        listItemDrawer->SetInsets(BSize(INSETS_WIDTH, 0));
    }

    DrawBackground(parent, frame, listItemDrawer);
    parent->SetDrawingMode(B_OP_OVER);

    if (index > 0) {
        DrawDividingLine(parent, frame);
    }
    DrawSymbol(frame, B_ALIGN_LEFT, B_ALIGN_TOP);
    DrawLatestPrice(frame, B_ALIGN_RIGHT, B_ALIGN_TOP);

    DrawCompanyName(frame, B_ALIGN_LEFT, B_ALIGN_BOTTOM);
    // (DrawChart, center)
    DrawChange(frame, B_ALIGN_RIGHT, B_ALIGN_BOTTOM);

    float newHeight = CalcTotalRowHeight();
    parent->FrameResized(frame.Width(), newHeight);
}

void
QuoteListItem::DrawBackground(BListView *parent, const BRect &frame, ListItemDrawer *drawer) {

    const int32 index = parent->IndexOf(this);
    rgb_color backgroundColor = drawer->BackgroundColor(IsSelected());

    if (IsSelected()) {
        backgroundColor = ui_color(B_LIST_SELECTED_BACKGROUND_COLOR);
    } else if (index % 2 == 0) {
        backgroundColor = tint_color(backgroundColor, 1.02);
    }

    parent->SetHighColor(backgroundColor);

    parent->SetDrawingMode(B_OP_COPY);
    parent->FillRect(frame);

    parent->SetLowColor(backgroundColor);
}

void
QuoteListItem::DrawDividingLine(BView *owner, const BRect &frame) {
    MakeLineColor(owner);
    float currentPenSize = owner->PenSize();
    owner->SetPenSize(1.5f);

    BPoint leftTop = CalcLineLeftTop(frame);
    BPoint rightTop = CalcLineRightTop(frame);

    owner->StrokeLine(leftTop, rightTop);
    owner->SetPenSize(currentPenSize);
}

BPoint QuoteListItem::CalcLineRightTop(const BRect &frame) const {
    BPoint rightTop = frame.RightTop();
    rightTop.x -= INSETS_WIDTH;
    rightTop.y += 2.0;
    return rightTop;
}

BPoint QuoteListItem::CalcLineLeftTop(const BRect &frame) const {
    BPoint leftTop = frame.LeftTop();
    leftTop.x += INSETS_WIDTH;
    leftTop.y += 2.0;
    return leftTop;
}

void QuoteListItem::MakeLineColor(BView *owner) const {
    rgb_color line_color = tint_color(ui_color(B_LIST_SELECTED_BACKGROUND_COLOR), 1.2f);
    owner->SetHighColor(line_color);
}

void
QuoteListItem::Update(BView *owner, const BFont *font) {
    auto *parent = dynamic_cast<BListView *>(owner);
    fWeakOwner = parent;

    font_height fh{};
    font->GetHeight(&fh);
    float cellHeight = fh.ascent + fh.descent + fh.leading;
    cellHeight *= 3.0;
    SetHeight(cellHeight);
    if (lastWidth != owner->Frame().Width()) {
        lastWidth = owner->Frame().Width();
        owner->Invalidate();
    }
}

void
QuoteListItem::DrawCompanyName(const BRect &frame, alignment horizontal_alignment,
                               vertical_alignment vertical_alignment) {
    BFont font(be_plain_font);
    font.SetFace(B_LIGHT_FACE);
    font.SetSize(FONT_SIZE_COMPANY_NAME);
    // Color: lightGray
    CalcAndStoreCellHeight(&font, horizontal_alignment);
    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment, nullptr};
    listItemDrawer->DrawString(fQuote->companyName->String(), settings);

}

void
QuoteListItem::DrawSymbol(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment) {
    BFont font(be_plain_font);
    font.SetFace(B_REGULAR_FACE);
    font.SetSize(FONT_SIZE_SYMBOL_NAME);
    CalcAndStoreCellHeight(&font, horizontal_alignment);
    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment, nullptr};
    listItemDrawer->DrawString(fQuote->symbol->String(), settings);
}

void
QuoteListItem::DrawLatestPrice(const BRect &frame, alignment horizontal_alignment,
                               vertical_alignment vertical_alignment) {
    BFont font(be_bold_font);
    font.SetFace(B_BOLD_FACE);
    font.SetSize(FONT_SIZE_PRICE);
    char priceString[12];
    std::sprintf(priceString, "%.2f", fQuote->latestPrice);

    CalcAndStoreCellHeight(&font, horizontal_alignment);
    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment, nullptr};
    listItemDrawer->DrawString(priceString, settings);
}

void
QuoteListItem::DrawChange(const BRect &frame, alignment horizontal_alignment, vertical_alignment vertical_alignment) {
    BFont font(be_plain_font);
    font.SetFace(B_REGULAR_FACE);
    font.SetSize(FONT_SIZE_PRICE - 2); // A bit smaller than price

    const char *changeString = fQuoteFormatter->ChangePercentageToString();

    CalcAndStoreCellHeight(&font, horizontal_alignment);
    const rgb_color *whiteTextColor = new rgb_color{255, 255, 255, 255};
    const rgb_color *rectColor = fQuoteFormatter->ChangeBackground();

    DrawItemSettings settings = {frame, &font, const_cast<rgb_color *>(whiteTextColor), horizontal_alignment,
                                 vertical_alignment,
                                 const_cast<rgb_color *>(rectColor)};

    listItemDrawer->DrawString(changeString, settings);
    delete changeString;
    delete rectColor;
}

void
QuoteListItem::CalcAndStoreCellHeight(const BFont *font, alignment alignment) {
    font_height fh{};
    font->GetHeight(&fh);
    float cellHeight = fh.ascent + fh.descent + fh.leading;
    int rowNumber;
    switch (alignment) {
        case B_ALIGN_LEFT: {
            rowNumber = 0;
            break;
        }
        case B_ALIGN_RIGHT: {
            rowNumber = 1;
            break;
        }
        default: {
            break;
        }
    }
    AddRowHeight(rowNumber, cellHeight);
}

void
QuoteListItem::AddRowHeight(int rowNum, float cellHeight) {
    rowSizes[rowNum] = std::max(rowSizes[rowNum], cellHeight);
}

float
QuoteListItem::CalcTotalRowHeight() {
    float totalHeight = 0;
    totalHeight += rowSizes[0];
    totalHeight += rowSizes[1];
    return totalHeight;
}

Quote *QuoteListItem::GetQuote() {
    return fQuote;
}
