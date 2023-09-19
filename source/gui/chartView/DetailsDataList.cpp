//
// Created by Thorsten Claus on 01.05.23.
//

#include <Catalog.h>
#include <LayoutBuilder.h>
#include <StringView.h>
#include "DetailsDataList.h"
#include "Portfolio.h"
#include "QuoteFormatter.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "DetailsDataList"

DetailsDataList::DetailsDataList() :
        BView(BRect(), "detailsDataList", B_FOLLOW_ALL, B_WILL_DRAW) {

    InitStringViews();

    BLayoutBuilder::Group<>(this, B_HORIZONTAL)
            .AddGroup(B_VERTICAL, B_USE_SMALL_SPACING)
            .AddGrid()
            .Add(fOpenStringView, 0, 0)
            .Add(fOpenValueStringView, 1, 0)
            .Add(fHighStringView, 0, 1)
            .Add(fHighValueStringView, 1, 1)
            .Add(fLowStringView, 0, 2)
            .Add(fLowValueStringView, 1, 2)
            .End()
            .End()
            .AddGroup(B_VERTICAL, B_USE_SMALL_SPACING)
            .AddGrid()
            .Add(fVolumeStringView, 0, 0)
            .Add(fVolumeValueStringView, 1, 0)
            .Add(fPeStringView, 0, 1) // Price earnings, KGV in german
            .Add(fPeValueStringView, 1, 1)
            .Add(fMarketCapStringView, 0, 2)
            .Add(fMarketCapValueStringView, 1, 2)
            .End()
            .End()
            .AddGroup(B_VERTICAL, B_USE_SMALL_SPACING)
            .AddGrid()
            .Add(fYearHighStringView, 0, 0)
            .Add(fYearHighValueValueStringView, 1, 0)
            .Add(fYearLowStringView, 0, 1)
            .Add(fYearLowValueStringView, 1, 1)
            .Add(fAvgVolumeStringView, 0, 2)
            .Add(fAvgVolumeValueStringView, 1, 2)
            .End()
            .End();

    Portfolio::Instance().Attach(this);
}

void DetailsDataList::UpdateStatus() {
    SetActiveQuote(Portfolio::Instance().GetCurrentQuote());
    if (fCurrentQuote != nullptr) {
        //TODO: Clear, if no quote is selected
        UpdateLabels();
    }
}

void
DetailsDataList::InitStringViews() {
    fOpenStringView = new BStringView("strOpen", B_TRANSLATE_COMMENT("Open", "Last daily opening price"));
    fOpenValueStringView = new BStringView("strOpenValue", "-");
    FormatValueLabel(fOpenValueStringView);

    fHighStringView = new BStringView("strHigh", B_TRANSLATE_COMMENT("High", "Highest price for current or last day"));
    fHighValueStringView = new BStringView("strHighValue", "-");
    FormatValueLabel(fHighValueStringView);

    fLowStringView = new BStringView("strLow", B_TRANSLATE_COMMENT("Low", "Lowest price for current or last day"));
    fLowValueStringView = new BStringView("strLowValue", "-");
    FormatValueLabel(fLowValueStringView);

    fVolumeStringView = new BStringView("strVolume", B_TRANSLATE("Volume"));
    fVolumeValueStringView = new BStringView("strVolumeValue", "-");
    FormatValueLabel(fVolumeValueStringView);

    fPeStringView = new BStringView("strPe", B_TRANSLATE_COMMENT("P/E ratio",
                                                                 "The price-earnings ratio, also known as P/E, or PER, is the ratio of a company's share price to the company's earnings per share. Keep as short as possible. "));
    fPeValueStringView = new BStringView("strPeValue", "-");
    FormatValueLabel(fPeValueStringView);

    fMarketCapStringView = new BStringView("strMarketCap",
                                           B_TRANSLATE_COMMENT("Cap",
                                                               "Abbreviation for the total value of shares owned by stockholders."));
    fMarketCapValueStringView = new BStringView("strMarketCapValue", "-");
    FormatValueLabel(fMarketCapValueStringView);

    fYearHighStringView = new BStringView("strYearHigh", B_TRANSLATE_COMMENT("52W-H",
                                                                             "Abbreviation for the highest price in last 52 weeks."));
    fYearHighValueValueStringView = new BStringView("strYearHighValue", "-");
    FormatValueLabel(fYearHighValueValueStringView);

    fYearLowStringView = new BStringView("strYearLow", B_TRANSLATE_COMMENT("52-W-L",
                                                                           "Abbreviation for the lowest price in last 52 weeks."));
    fYearLowValueStringView = new BStringView("strYearLowValue", "-");
    FormatValueLabel(fYearLowValueStringView);

    fAvgVolumeStringView = new BStringView("strAvgVolume",
                                           B_TRANSLATE_COMMENT("Avg. Vol", "Abbreviation for the average volume."));
    fAvgVolumeValueStringView = new BStringView("strAvgVolValue", "-");
    FormatValueLabel(fAvgVolumeValueStringView);
}

void
DetailsDataList::FormatValueLabel(BStringView *stringView) {
    stringView->SetAlignment(B_ALIGN_RIGHT);
    BFont font(be_bold_font);
    font.SetFace(B_BOLD_FACE);
    stringView->SetFont(&font);
}

void
DetailsDataList::SetActiveQuote(Quote *quote) {
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

void DetailsDataList::UpdateLabels() {
    fOpenValueStringView->SetText(QuoteFormatter::CurrencyToString(fCurrentQuote->open));

    fHighValueStringView->SetText(QuoteFormatter::CurrencyToString(fCurrentQuote->dayHigh));
    fLowValueStringView->SetText(QuoteFormatter::CurrencyToString(fCurrentQuote->dayLow));

    fVolumeValueStringView->SetText(QuoteFormatter::HumanReadableLargeNumber(fCurrentQuote->volume));
    fPeValueStringView->SetText(QuoteFormatter::CurrencyToString(fCurrentQuote->pe));
    fMarketCapValueStringView->SetText(QuoteFormatter::HumanReadableLargeNumber(fCurrentQuote->marketCap));

    fYearHighValueValueStringView->SetText(QuoteFormatter::CurrencyToString(fCurrentQuote->yearHigh));
    fYearLowValueStringView->SetText(QuoteFormatter::CurrencyToString(fCurrentQuote->yearLow));
    fAvgVolumeValueStringView->SetText((QuoteFormatter::HumanReadableLargeNumber(fCurrentQuote->avgVolume)));
}
