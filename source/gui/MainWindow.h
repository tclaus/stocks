#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include "stocksPanel/StocksPanelView.h"
#include "utils/DelayedQueryTimer.h"
#include "../handler/QuoteResultHandler.h"
#include "../quoteUpdateJob/QuoteUpdateJob.h"

class MainWindow : public BWindow {
public:
    MainWindow();

    ~MainWindow() override;

    void SetWindowSizeLimits();

    void InitWorker();

    void Show() override;

    void MessageReceived(BMessage *message) override;

    /**
     * Handles the completed API request
     * @param requestId
     */
    void ResultHandler(int requestId);

    /**
     * Handles a change in the search field. Starts a new search for shares.
     * @param searchTerm
     */
    void RequestForSearch(BString &searchTerm);

    bool QuitRequested() override;

private:
    StocksPanelView *fStocksPanelView;
    BView *chartView;
    DelayedQueryTimer *fDelayedQueryTimer;
    QuoteUpdateJob *fQuoteUpdateJob;
    QuoteResultHandler *fQuoteResultHandler;

    void InitViews();
};

#endif
