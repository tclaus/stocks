//
// Created by Thorsten Claus on 01.05.23.
//

#ifndef STOCKS_DETAILSDATALIST_H
#define STOCKS_DETAILSDATALIST_H

#include <View.h>
#include "Quote.h"

class DetailsDataList : public BView, Observer {
public:

    DetailsDataList();

    /**
     * Sets the current active quote to view its details.
     * @param quote The quote to show details.
     */
    void SetActiveQuote(Quote *quote);

private:
    Quote *fCurrentQuote;

    BStringView *fOpenStringView;
    BStringView *fOpenValueStringView;
    BStringView *fHighStringView;
    BStringView *fHighValueStringView;
    BStringView *fLowStringView;
    BStringView *fLowValueStringView;
    BStringView *fVolumeStringView;
    BStringView *fVolumeValueStringView;
    BStringView *fPeStringView;
    BStringView *fPeValueStringView;
    BStringView *fMarketCapStringView;
    BStringView *fMarketCapValueStringView;
    BStringView *fYearHighStringView;
    BStringView *fYearHighValueValueStringView;
    BStringView *fYearLowStringView;
    BStringView *fYearLowValueStringView;
    BStringView *fAvgVolumeStringView;
    BStringView *fAvgVolumeValueStringView;

    void InitStringViews();

    void UpdateStatus() override;

    void UpdateLabels();

    void FormatValueLabel(BStringView *stringView);
};


#endif //STOCKS_DETAILSDATALIST_H
