//
// Created by Thorsten Claus on 15.02.23.
//

#include "FoundShareListItem.h"
#include "QuoteFormatter.h"
#include "ListItemConstants.h"
#include <iostream>
#include <View.h>
#include <algorithm>
#include "ListView.h"

FoundShareListItem::FoundShareListItem(Quote *quote)
        : BListItem(),
          fQuote(quote),
          fListItemDrawer(nullptr),
          fLastWidth(0.0),
          fCheckBoxAdded(false),
          fCheckbox(nullptr) {

    fQuoteFormatter = new QuoteFormatter(quote);

    InitCheckbox(*quote);
}

void FoundShareListItem::InitCheckbox(const Quote &quote) {
    BMessage *chkBoxMessage = new BMessage(CHECKBOX_CLICKED);
    chkBoxMessage->SetString(SYMBOL_NAME, *quote.symbol);

    std::string checkBoxName = GenerateCheckBoxName(quote);

    fCheckbox = new BCheckBox(BRect(), checkBoxName.c_str(), "", chkBoxMessage);

    fCheckbox->ResizeToPreferred();
    fCheckbox->SetValue(B_CONTROL_OFF);
}

std::string FoundShareListItem::GenerateCheckBoxName(const Quote &quote) const {
    std::string prefix = "chk";
    std::string symbolName = quote.symbol->String();
    std::string checkBoxName = (prefix + symbolName);
    return checkBoxName;
}

FoundShareListItem::FoundShareListItem()
        : BListItem() {
}

FoundShareListItem::~FoundShareListItem() {
    delete fQuote;
    delete fListItemDrawer;
    delete fQuoteFormatter;
    delete fCheckbox;
}

Quote *
FoundShareListItem::GetQuote() {
    return fQuote;
}

void
FoundShareListItem::DrawItem(BView *owner, BRect rect, bool complete) {
    (void) complete;

    auto *parent = dynamic_cast<BListView *>(owner);
    const int32 index = parent->IndexOf(this);

    if (!IsCheckboxAChild(parent)) {
        BPoint checkboxPoint = LeftHorizontalCenterForCheckbox(rect);
        checkboxPoint.Set(checkboxPoint.x + INSETS_WIDTH, checkboxPoint.y);
        fCheckbox->MoveTo(checkboxPoint);
        parent->AddChild(fCheckbox);
    }
    fCheckBoxAdded = true;
    fSpaceForCheckbox = fCheckbox->Bounds().Width() + INSETS_WIDTH;

    InitItemDrawer(parent);

    BRect frame = getRectWithCheckboxOffset(rect);

    DrawBackground(parent, rect, fListItemDrawer);
    parent->SetDrawingMode(B_OP_OVER);

    DrawDividingLineBetweenElements(parent, index, rect);

    DrawTopContent(frame);
    DrawSecondaryContent(frame);

    float newHeight = CalcTotalRowHeight();
    parent->FrameResized(rect.Width(), newHeight);
}

void FoundShareListItem::DrawSecondaryContent(const BRect &frame) {
    DrawCompanyName(frame, B_ALIGN_LEFT, B_ALIGN_BOTTOM);
}

BRect FoundShareListItem::getRectWithCheckboxOffset(const BRect &rect) const {
    auto frame = BRect(rect);
    frame.left += fSpaceForCheckbox;
    return frame;
}

BPoint FoundShareListItem::LeftHorizontalCenterForCheckbox(const BRect &rect) const {
    BPoint center(rect.LeftTop());
    center.Set(center.x, rect.top + rect.Height() / 2 - fCheckbox->Bounds().Height() / 2);
    return center;
}

bool
FoundShareListItem::IsCheckboxAChild(const BListView *parent) const {
    return fCheckBoxAdded || parent->FindView(fCheckbox->Name());
}

void FoundShareListItem::DrawDividingLineBetweenElements(BListView *parent, const int32 index, const BRect &frame) {
    if (index > 0) {
        DrawDividingLine(parent, frame);
    }
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

    fCheckbox->SetHighColor(backgroundColor);
    fCheckbox->SetLowColor(backgroundColor);

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
FoundShareListItem::DrawTopContent(const BRect &frame) {
    BFont font(be_plain_font);
    font.SetFace(B_REGULAR_FACE);
    font.SetSize(FONT_SIZE_SYMBOL_NAME);
    CalcAndStoreCellHeight(&font, B_ALIGN_LEFT);
    DrawItemSettings settings = {frame, &font, nullptr, B_ALIGN_LEFT, B_ALIGN_TOP, nullptr};

    BString *lineText = CreateTopRowString();

    fListItemDrawer->DrawString(lineText->String(), settings);
}

BString *FoundShareListItem::CreateTopRowString() const {
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