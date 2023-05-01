//
// Created by Thorsten Claus on 01.05.23.
//

#include "DetailsHeadline.h"

#include <LayoutBuilder.h>
#include <StringView.h>

DetailsHeadline::DetailsHeadline() :
        BView(BRect(), "detailsHeadView", B_FOLLOW_ALL, B_WILL_DRAW) {

    BLayoutBuilder::Grid<>(this, B_HORIZONTAL)
            .Add(new BStringView("shortSymbolName", "LHA.DE"), 0, 0)
            .Add(new BStringView("detailsSymbolName", "Deutsche Lufthansa AG"), 1, 0)
            .AddGlue(2, 0)
            .Add(new BStringView("symbolCurrentPrice", "9,73€ +1.66%"), 3, 0);

};