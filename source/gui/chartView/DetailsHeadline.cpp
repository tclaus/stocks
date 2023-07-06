//
// Created by Thorsten Claus on 01.05.23.
//

#include "DetailsHeadline.h"
#include "QuoteFormatter.h"
#include "Portfolio.h"
#include <LayoutBuilder.h>
#include <StringView.h>

DetailsHeadline::DetailsHeadline() :
        BView(BRect(), "detailsHeadView", B_FOLLOW_ALL, B_WILL_DRAW) {

    InitStringViews();

    BLayoutBuilder::Grid<>(this, B_USE_BIG_SPACING)
            .Add(fSymbolShortNameLabel, 0, 0)
            .Add(fSymbolFullNameLabel, 1, 0)
            .AddGlue(2, 0)
            .Add(fSymbolPriceLabel, 3, 0)
            .Add(fSymbolChangeLabel, 4, 0);

    SetViewColor(255, 255, 255);

    Portfolio::Instance().Attach(this);
}

void
DetailsHeadline::SetActiveQuote(Quote *quote) {
    if (quote == fCurrentQuote) {
        return;
    }
    if (fCurrentQuote) {
        fCurrentQuote->Detach(this);
        fCurrentQuote = nullptr;
    }
    if (quote) {
        fCurrentQuote = quote;
        fCurrentQuote->Attach(this);
    }
}

void
DetailsHeadline::UpdateStatus() {
    SetActiveQuote(Portfolio::Instance().GetCurrentQuote());
    if (fCurrentQuote != nullptr) {
        //TODO: Clear, if no quote is selected
        UpdateLabels();
    }
}

void
DetailsHeadline::InitStringViews() {
    CreateSymbolShortNameLabel();
    CreateSymbolFullNameLabel();
    CreateSymbolPriceLabel();
    CreateSymbolChangeLabel();
}

void
DetailsHeadline::UpdateLabels() {
    UpdateShortSymbolName();
    UpdateFullSymbolName();
    UpdatePriceLabel();
    UpdateChangeInPercentLabel();
}

void DetailsHeadline::UpdateChangeInPercentLabel() {
    char *percentString = QuoteFormatter::PercentageToString(fCurrentQuote->changesPercentage);
    fSymbolChangeLabel->SetText(percentString);

    rgb_color *changeColor = QuoteFormatter::ColorByValue(fCurrentQuote->changesPercentage);
    fSymbolChangeLabel->SetHighColor(*changeColor);
}

void DetailsHeadline::UpdatePriceLabel() {
    char *priceString = QuoteFormatter::CurrencyToString(fCurrentQuote->latestPrice);
    fSymbolPriceLabel->SetText(priceString);
}

void DetailsHeadline::UpdateFullSymbolName() { fSymbolFullNameLabel->SetText(fCurrentQuote->companyName->String()); }

void DetailsHeadline::UpdateShortSymbolName() { fSymbolShortNameLabel->SetText(fCurrentQuote->symbol->String()); }

void
DetailsHeadline::CreateSymbolFullNameLabel() {
    fSymbolFullNameLabel = new BStringView("symbolFullNameLabel", "Symbol");
    fSymbolFullNameLabel->ResizeBy(0, 50);
}

void
DetailsHeadline::CreateSymbolPriceLabel() {
    fSymbolPriceLabel = new BStringView("symbolPriceLabel", "0,00€");
    BFont font(be_bold_font);
    font.SetFace(B_BOLD_FACE);
    fSymbolPriceLabel->SetFont(&font);
}

void DetailsHeadline::CreateSymbolChangeLabel() {
    fSymbolChangeLabel = new BStringView("symbolChangeLabel", "0%");
}

void
DetailsHeadline::CreateSymbolShortNameLabel() {
    fSymbolShortNameLabel = new BStringView("shortSymbolName", "SYM");
    BFont font(be_plain_font);
    font.SetFace(B_BOLD_FACE);
    font.SetSize(25);
    fSymbolShortNameLabel->SetFont(&font);
    // align to bottom?
}
