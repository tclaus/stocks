//
// Created by Thorsten Claus on 10.07.23.
//

#include <Catalog.h>
#include <NetServicesDefs.h>
#include "ChartView.h"
#include "Portfolio.h"
#include "TimeRange.h"
#include "ApiBuilder.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "ChartView"

ChartView::ChartView() :
        BView(BRect(), B_TRANSLATE("chartView"), B_FOLLOW_ALL, B_WILL_DRAW),
        fTimeRange(TimeRange::M_DAY),
        fHistoricalPriceListHandler(new HistoricalPriceResultHandler()),
        fHistoricalPriceList(new HistoricalPriceList()) {

    SetExplicitMinSize(BSize(0, 300));

    fBackgroundDrawer = new GridlineDrawer(this);
    fSeriesDrawer = new SeriesDrawer(this);
    fVerticalAxisDrawer = new VerticalAxisDrawer(this);

    Portfolio::Instance().Attach(this);
    CreateApiConnection();
};

void
ChartView::UpdateStatus() {
    SetActiveQuote(Portfolio::Instance().GetCurrentQuote());
}

void
ChartView::SetActiveQuote(Quote *quote) {
    if (quote == fQuote) {
        return;
    }

    fQuote = quote;
    RequestRedraw();
}

void
ChartView::SetTimeRange(TimeRange timeRange) {
    if (fTimeRange == timeRange) {
        return;
    }

    fTimeRange = timeRange;
    RequestRedraw();
}

void
ChartView::RequestRedraw() {
    fStockConnector->RetrieveHistoricData(fQuote->symbol->String(), fTimeRange);
}

void
ChartView::Draw(BRect updateRect) {
    BView::Draw(updateRect);

    fBackgroundDrawer->DrawGridLines(updateRect);
    fSeriesDrawer->DrawSeries(fTimeRange, fHistoricalPriceList);
    fVerticalAxisDrawer->DrawAxis(fTimeRange, fHistoricalPriceList);
    // Draw axis and labels
}

void
ChartView::CreateApiConnection() {
    ApiBuilder apiBuilder = ApiBuilder();
    fStockConnector = apiBuilder.CreateStockConnector(this);
}

void
ChartView::MessageReceived(BMessage *message) {
    switch (message->what) {
        case (BPrivate::Network::UrlEvent::RequestCompleted): {
            ResultHandler(message->GetInt32(BPrivate::Network::UrlEventData::Id, -1));
            break;
        }
        default:
            BView::MessageReceived(message);
            break;
    }
}

void
ChartView::ResultHandler(int32 requestId) {
    fHistoricalPriceList = fHistoricalPriceListHandler->GenerateHistoricalDataObject(requestId);
    Invalidate();
}