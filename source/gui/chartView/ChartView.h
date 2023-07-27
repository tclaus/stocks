//
// Created by Thorsten Claus on 10.07.23.
//

#ifndef STOCKS_CHARTVIEW_H
#define STOCKS_CHARTVIEW_H

#include "Observer.h"
#include "Quote.h"
#include "ChartTimeRangeBar.h"
#include "TimeRange.h"
#include "drawer/GridlineDrawer.h"
#include "drawer/SeriesDrawer.h"

#include "View.h"
#include "StockConnector.h"
#include "HistoricalPriceList.h"
#include "../../handler/HistoricalPriceResultHandler.h"

/**
 * Handles the inner chart view with the symbol plot area, the background grid line and the description for x- and <- axis
 */
class ChartView : public BView, Observer {

public:
    ChartView();

    void Draw(BRect updateRect) override;

    void SetTimeRange(TimeRange timeRange);

    void MessageReceived(BMessage *message) override;

private:

    void UpdateStatus() override;

    /**
 * Sets the current active quote to view its details.
 * @param quote The quote to show details.
 */
    void SetActiveQuote(Quote *quote);

    /**
     * Requests a redraw if anything changes like the quote or the time range.
     * Takes care about loaded data and inits a load of the data.
     */
    void RequestRedraw();

private:
    void CreateApiConnection();

    void ResultHandler(int32 requestId);

    Quote *fQuote{};
    TimeRange fTimeRange;
    GridlineDrawer *fBackgroundDrawer;
    SeriesDrawer *fSeriesDrawer;
    StockConnector *fStockConnector{};
    HistoricalPriceResultHandler *fHistoricalPriceListHandler;
    HistoricalPriceList *fHistoricalPriceList;
    uint32 fLastRequestId = 0;
};


#endif //STOCKS_CHARTVIEW_H
