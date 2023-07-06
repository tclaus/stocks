//
// Created by Thorsten Claus on 01.05.23.
//

#include <LayoutBuilder.h>
#include <StringView.h>
#include "DetailsDataList.h"
#include "GraphicsDefs.h"
#include "Portfolio.h"
#include "QuoteFormatter.h"

DetailsDataList::DetailsDataList() :
        BView(BRect(), "detailsDataList", B_FOLLOW_ALL, B_WILL_DRAW) {

    InitStringViews();

    printf("Layout detail strings");
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
    SetViewColor(200, 200, 200);

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
    printf("InitStringViews");
    fOpenStringView = new BStringView("strOpen", "Open");
    fOpenValueStringView = new BStringView("strOpenValue", "-");
    FormatValueLabel(fOpenValueStringView);

    fHighStringView = new BStringView("strHigh", "High");
    fHighValueStringView = new BStringView("strHighValue", "-");
    FormatValueLabel(fHighValueStringView);

    fLowStringView = new BStringView("strLow", "Low");
    fLowValueStringView = new BStringView("strLowValue", "-");
    FormatValueLabel(fLowValueStringView);

    fVolumeStringView = new BStringView("strVolume", "Volume");
    fVolumeValueStringView = new BStringView("strVolumeValue", "-");
    FormatValueLabel(fVolumeValueStringView);

    fPeStringView = new BStringView("strPe", "PE");
    fPeValueStringView = new BStringView("strPeValue", "-");
    FormatValueLabel(fPeValueStringView);

    fMarketCapStringView = new BStringView("strMarketCap", "Cap");
    fMarketCapValueStringView = new BStringView("strMarketCapValue", "-");
    FormatValueLabel(fMarketCapValueStringView);

    fYearHighStringView = new BStringView("strYearHigh", "52W-H");
    fYearHighValueValueStringView = new BStringView("strYearHighValue", "-");
    FormatValueLabel(fYearHighValueValueStringView);

    fYearLowStringView = new BStringView("strYearLow", "52-W-L");
    fYearLowValueStringView = new BStringView("strYearLowValue", "-");
    FormatValueLabel(fYearLowValueStringView);

    fAvgVolumeStringView = new BStringView("strAvgVolume", "Avg. Vol");
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
