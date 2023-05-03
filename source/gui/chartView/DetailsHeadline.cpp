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

    BLayoutBuilder::Grid<>(this, B_HORIZONTAL)
            .Add(fSymbolShortNameLabel, 0, 0)
            .Add(fSymbolFullNameLabel, 1, 0)
            .AddGlue(2, 0)
            .Add(fSymbolPriceLabel, 3, 0)
            .Add(fSymbolChangeLabel, 3, 0);

    Portfolio::Instance().Attach(this);

}

void
DetailsHeadline::SetActiveQuote(Quote *quote) {
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
    fSymbolShortNameLabel->SetText(fCurrentQuote->symbol->String());
    fSymbolFullNameLabel->SetText(fCurrentQuote->companyName->String());

    char *priceString = QuoteFormatter::CurrencyToString(fCurrentQuote->latestPrice);
    fSymbolPriceLabel->SetText(priceString);

    char *percentString = QuoteFormatter::PercentageToString(fCurrentQuote->changesPercentage);
    fSymbolChangeLabel->SetText(percentString);

    rgb_color *changeColor = QuoteFormatter::ColorByValue(fCurrentQuote->changesPercentage);
    fSymbolChangeLabel->SetHighColor(*changeColor);
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

void
DetailsHeadline::CreateSymbolFullNameLabel() {
    fSymbolFullNameLabel = new BStringView("symbolFullNameLabel", "Symbol");
}

void
DetailsHeadline::CreateSymbolPriceLabel() {
    fSymbolPriceLabel = new BStringView("symbolPriceLabel", "0,00€");
}

void DetailsHeadline::CreateSymbolChangeLabel() {
    fSymbolChangeLabel = new BStringView("symbolChangeLabel", "0%");
}
