//
// Created by Thorsten Claus on 10.07.23.
//

#include <NetServicesDefs.h>
#include "ChartView.h"
#include "Portfolio.h"
#include "TimeRange.h"
#include "ApiBuilder.h"

ChartView::ChartView() :
        BView(BRect(), "chartView", B_FOLLOW_ALL, B_WILL_DRAW),
        fTimeRange(TimeRange::M_DAY),
        fHistoricalPriceListHandler(new HistoricalPriceResultHandler()),
        fHistoricalPriceList(new HistoricalPriceList()) {

    SetExplicitMinSize(BSize(0, 300));

    fBackgroundDrawer = new GridlineDrawer(this);
    fSeriesDrawer = new SeriesDrawer(this);

    Portfolio::Instance().Attach(this);
    CreateApiConnection();
};

void
ChartView::UpdateStatus() {
    SetActiveQuote(Portfolio::Instance().GetCurrentQuote());
    RequestRedraw();
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
    printf("Set new timeRange: %d\n", timeRange);
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
            printf("Received historic Data from request \n");
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
    printf(" RequestId: %d \n", requestId);
    fHistoricalPriceList = fHistoricalPriceListHandler->GenerateHistoricalDataObject(requestId);
    Invalidate();
}