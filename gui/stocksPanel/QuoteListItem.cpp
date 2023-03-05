//
// Created by Thorsten Claus on 15.02.23.
//

#include "QuoteListItem.h"
#include <View.h>
#include <iostream>
#include "ListView.h"

QuoteListItem::QuoteListItem(Quote *quote)
        : BListItem(),
          fQuote(quote) {
}

QuoteListItem::QuoteListItem()
        : BListItem() {}

QuoteListItem::~QuoteListItem() {
    delete fQuote;
    delete listItemDrawer;
}

void
QuoteListItem::SetQuote(Quote *quote) {
    delete fQuote;
    fQuote = quote;
}

Quote *QuoteListItem::GetQuote() {
    return fQuote;
}

void
QuoteListItem::DrawItem(BView *owner, BRect rect, bool complete) {
    (void) complete;
    (void) rect;

    auto *parent = dynamic_cast<BListView *>(owner);
    const int32 index = parent->IndexOf(this);
    BRect frame = parent->ItemFrame(index);

    if (listItemDrawer == nullptr) {
        listItemDrawer = new ListItemDrawer(parent);
        listItemDrawer->SetInsets(BSize(10, 0));
    }

    if (IsSelected()) {

    }
    // Setze Höhe
    BFont font(be_plain_font);
    font.SetFace(B_REGULAR_FACE);
    font.SetSize(FONT_SIZE_SYMBOL_NAME);
    // Color: white
    DrawItemSettings settings = {frame, &font, nullptr, B_ALIGN_LEFT, B_ALIGN_TOP};
    frame.OffsetBySelf(0, listItemDrawer->Height(settings));

    DrawSymbol(frame, B_ALIGN_LEFT, B_ALIGN_TOP);
    DrawLatestPrice(frame, B_ALIGN_RIGHT, B_ALIGN_TOP);

    DrawCompanyName(frame, B_ALIGN_LEFT, B_ALIGN_BOTTOM);
    // (DrawChart, middle)
    DrawChange(frame, B_ALIGN_RIGHT, B_ALIGN_BOTTOM);
}

void
QuoteListItem::Update(BView *owner, const BFont *font) {
    (void) owner;

    font_height fh{};
    font->GetHeight(&fh);
    float height = fh.ascent + fh.descent + fh.leading;
    SetHeight(height);
}

void
QuoteListItem::DrawCompanyName(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment) {
    BFont font(be_plain_font);
    font.SetFace(B_LIGHT_FACE);
    font.SetSize(FONT_SIZE_COMPANY_NAME);
    // Color: lightGray
    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment};
    listItemDrawer->DrawString(fQuote->companyName->String(), settings);

}

void
QuoteListItem::DrawSymbol(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment) {
    BFont font(be_plain_font);
    font.SetFace(B_REGULAR_FACE);
    font.SetSize(FONT_SIZE_SYMBOL_NAME);
    // Color: white
    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment};
    listItemDrawer->DrawString(fQuote->symbol->String(), settings);

}

void
QuoteListItem::DrawLatestPrice(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment) {
    BFont font(be_bold_font);
    font.SetFace(B_BOLD_FACE);
    font.SetSize(FONT_SIZE_PRICE);

    std::string priceString = std::to_string(fQuote->latestPrice);

    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment};
    listItemDrawer->DrawString(priceString.c_str(), settings);
}

void
QuoteListItem::DrawChange(BRect frame, alignment horizontal_alignment, vertical_alignment vertical_alignment) {
    BFont font(be_plain_font);
    font.SetFace(B_REGULAR_FACE);
    font.SetSize(FONT_SIZE_PRICE - 2); // A bit smaller than price

    std::string priceString = std::to_string(fQuote->change);

    DrawItemSettings settings = {frame, &font, nullptr, horizontal_alignment, vertical_alignment};
    listItemDrawer->DrawString(priceString.c_str(), settings);
}
