#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include "stocksPanel/StocksPanelView.h"

class MainWindow : public BWindow {
public:
    MainWindow();

    void Show() override;

    void FillStocksList();

    void MessageReceived(BMessage *msg) override;

    /**
     * Handles the completed api request
     * @param requestId
     */
    void ResultHandler(int requestId);

    bool QuitRequested() override;

private:
    StocksPanelView *stocksPanelView;
    BView *chartView;
};

#endif
