//
// Created by Thorsten Claus on 01.05.23.
//

#include <LayoutBuilder.h>
#include <StringView.h>
#include "DetailsDataList.h"
#include "GraphicsDefs.h"

DetailsDataList::DetailsDataList() :
        BView(BRect(), "detailsDataList", B_FOLLOW_ALL, B_WILL_DRAW) {

    BLayoutBuilder::Group<>(this, B_HORIZONTAL)
            .AddGroup(B_VERTICAL)
            .AddGrid()
            .Add(new BStringView("strOpen", "Open"), 0, 0)
            .Add(new BStringView("strOpenValue", "-"), 1, 0)
            .Add(new BStringView("strHigh", "High"), 0, 1)
            .Add(new BStringView("strHighValue", "-"), 1, 1)
            .Add(new BStringView("strLow", "Low"), 0, 2)
            .Add(new BStringView("strLowValue", "-"), 1, 2)
            .End()
            .End()
            .AddGroup(B_VERTICAL)
            .AddGrid()
            .Add(new BStringView("strVolume", "Volume"), 0, 0)
            .Add(new BStringView("strVolumeValue", "-"), 1, 0)
            .Add(new BStringView("strPe", "PE"), 0, 1) // Price earnings, KGV in german
            .Add(new BStringView("strPeValue", "-"), 1, 1)
            .Add(new BStringView("strMarketCap", "Cap"), 0, 2)
            .Add(new BStringView("strMarketCapValue", "-"), 1, 2)
            .End()
            .End()
            .AddGroup(B_VERTICAL)
            .AddGrid()
            .Add(new BStringView("strYearHigh", "52W-H"), 0, 0)
            .Add(new BStringView("strYearHighValue", "-"), 1, 0)
            .Add(new BStringView("strYearLow", "52-W-L"), 0, 1)
            .Add(new BStringView("strYearLowValue", "-"), 1, 1)
            .Add(new BStringView("strAvgVolume", "Avg. Vol"), 0, 2)
            .Add(new BStringView("strAvgVolValue", "-"), 1, 2)
            .End()
            .End();
    SetViewColor(200, 200, 200);

}



// 1. Block
// Eröffnung (Open)
// Hoch (dayHigh)
// Tief( day Low)

// 2. Block
// Volumen (volume)
// KGV ??
// MarktKap (marketCap)

// 3. Block
// 52W-H (Year High)
// 52W-T (Year Low)
// Durch. Volumen (avgVolume)

// 4. Block
//  Rendite?
// Beta ?
// EPS (eps)

// Interessant: prev close