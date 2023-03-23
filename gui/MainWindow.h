#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include "stocksPanel/StocksPanelView.h"

class MainWindow : public BWindow {
public:
    MainWindow();

    void SetWindowSizes();

    void Show() override;

    void FillStocksList();

    void MessageReceived(BMessage *msg) override;

    /**
     * Handles the completed api request
     * @param requestId
     */
    void ResultHandler(int requestId);

    /**
     * Handles a change in the search field. Starts a new search for shares.
     * @param searchTerm
     */
    void RequestForSearch(BString searchTerm);

    bool QuitRequested() override;

private:
    StocksPanelView *stocksPanelView;
    BView *chartView;
    // letzter Zeitstempel für die Suche
};

#endif
