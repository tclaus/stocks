//
// Created by Thorsten Claus on 15.02.23.
//

#include "FoundShareListItem.h"
#include "QuoteFormatter.h"
#include "ListItemConstants.h"
#include <View.h>
#include <algorithm>
#include "ListView.h"

FoundShareListItem::FoundShareListItem(Quote *quote)
        : BListItem(),
          fQuote(quote),
          fListItemDrawer(nullptr),
          fLastWidth(0.0),
          fCheckbox(nullptr) {

    fQuoteFormatter = new QuoteFormatter(quote);

}

FoundShareListItem::FoundShareListItem()
        : BListItem() {
}

FoundShareListItem::~FoundShareListItem() {
    delete fQuote;
    delete fListItemDrawer;
    delete fQuoteFormatter;
}

void
FoundShareListItem::SetQuote(Quote *quote) {
    delete fQuote;
    fQuote = quote;
}

Quote *
FoundShareListItem::GetQuote() {
    return fQuote;
}

void
FoundShareListItem::DrawItem(BView *owner, BRect rect, bool complete) {
    (void) complete;
    (void) rect;

    auto *parent = dynamic_cast<BListView *>(owner);
    const int32 index = parent->IndexOf(this);
    BRect frame = parent->ItemFrame(index);

    InitItemDrawer(parent);

    if (fCheckbox == nullptr) {
        fCheckbox = new BCheckBox(rect, "chk", "", new BMessage(32));
    }

    DrawBackground(parent, frame, fListItemDrawer);
    parent->SetDrawingMode(B_OP_OVER);

    if (index > 0) {
        DrawDividingLine(parent, frame);
    }

    // DrawCheckbox (linke seite

    //TODO: Etwas nach rechts verschieben, eine Checkbox muss noch rein !
    // Der Draw-Funktion ein Offset mitgeben

    DrawFirstLine(frame);
    DrawCompanyName(frame, B_ALIGN_LEFT, B_ALIGN_BOTTOM);

    float newHeight = CalcTotalRowHeight();
    parent->FrameResized(frame.Width(), newHeight);
}

void FoundShareListItem::InitItemDrawer(const BListView *parent) {
    if (fListItemDrawer == nullptr) {
        fListItemDrawer = new ListItemDrawer((BView *) parent);
        fListItemDrawer->SetInsets(BSize(INSETS_WIDTH, 0));
    }
}

void
FoundShareListItem::DrawBackground(BListView *parent, const BRect &frame, ListItemDrawer *drawer) {

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
FoundShareListItem::DrawDividingLine(BView *owner, const BRect &frame) {
    MakeLineColor(owner);
    float currentPenSize = owner->PenSize();
    owner->SetPenSize(1.5f);

    BPoint leftTop = CalcPointLeftTop(frame);
    BPoint rightTop = CalcPointRightTop(frame);

    owner->StrokeLine(leftTop, rightTop);
    owner->SetPenSize(currentPenSize);
}

BPoint
FoundShareListItem::CalcPointRightTop(const BRect &frame) const {
    BPoint rightTop = frame.RightTop();
    rightTop.x -= INSETS_WIDTH;
    rightTop.y += 2.0;
    return rightTop;
}

BPoint
FoundShareListItem::CalcPointLeftTop(const BRect &frame) const {
    BPoint leftTop = frame.LeftTop();
    leftTop.x += INSETS_WIDTH;
    leftTop.y += 2.0;
    return leftTop;
}

void
FoundShareListItem::MakeLineColor(BView *owner) const {
    rgb_color line_color = tint_color(ui_color(B_LIST_SELECTED_BACKGROUND_COLOR), 1.2f);
    owner->SetHighColor(line_color);
}

void
FoundShareListItem::Update(BView *owner, const BFont *font) {
    font_height fh{};
    font->GetHeight(&fh);
    float cellHeight = fh.ascent + fh.descent + fh.leading;
    cellHeight *= 3.0;
    SetHeight(cellHeight);
    if (fLastWidth != owner->Frame().Width()) {
        fLastWidth = owner->Frame().Width();
        owner->Invalidate();
    }
}

void
FoundShareListItem::DrawFirstLine(const BRect &frame) {
    BFont font(be_plain_font);
    font.SetFace(B_REGULAR_FACE);
    font.SetSize(FONT_SIZE_SYMBOL_NAME);
    CalcAndStoreCellHeight(&font, B_ALIGN_LEFT);
    DrawItemSettings settings = {frame, &font, nullptr, B_ALIGN_LEFT, B_ALIGN_TOP, nullptr};

    BString *lineText = CreateFirstLineText();

    fListItemDrawer->DrawString(lineText->String(), settings);
}

BString *FoundShareListItem::CreateFirstLineText() const {
    auto *lineText = new BString(fQuote->symbol->String());
    lineText->Append(" * ");
    lineText->Append(fQuote->market->String());
    lineText->Append(" * ");
    lineText->Append(fQuote->currency->String());
    return lineText;
}

void
FoundShareListItem::DrawCompanyName(const BRect &frame, alignment horizontal_alignment,
                                    vertical_alignment vertical_alignment) {
    BFont font(be_plain_font);
    font.SetFace(B_LIGHT_FACE);
    font.SetSize(FONT_SIZE_COMPANY_NAME);
    // Color: lightGray
    CalcAndStoreCellHeight(&font, horizontal_alignment);
    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment, nullptr};
    fListItemDrawer->DrawString(fQuote->companyName->String(), settings);
}

void
FoundShareListItem::CalcAndStoreCellHeight(const BFont *font, alignment alignment) {
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
FoundShareListItem::AddRowHeight(int rowNum, float cellHeight) {
    fRowSizes[rowNum] = std::max(fRowSizes[rowNum], cellHeight);
}

float
FoundShareListItem::CalcTotalRowHeight() {
    float totalHeight = 0;
    totalHeight += fRowSizes[0];
    totalHeight += fRowSizes[1];
    return totalHeight;
}