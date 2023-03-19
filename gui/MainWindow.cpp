#include "MainWindow.h"

#include "NetRequester.h"

#include "chartView/ChartView.h"
#include "../api/NetRequester.h"
#include <Application.h>
#include <InterfaceKit.h>
#include <Layout.h>
#include <LayoutBuilder.h>
#include <Window.h>
#include <private/netservices2/NetServicesDefs.h>
#include <iostream>

MainWindow::MainWindow()
        : BWindow(BRect(100, 100, 500, 400), "Stocks", B_TITLED_WINDOW,
                  B_ASYNCHRONOUS_CONTROLS) {

    stocksPanelView = new StocksPanelView(); // Update wenn Suche, update, wenn Aktien aktualisert werrden
    chartView = new ChartView();                // Update des Images

    BLayoutBuilder::Group<>((BWindow *) this, B_HORIZONTAL, 0)
            .SetInsets(0)
            .Add(stocksPanelView, 1)
            .Add(chartView, 3);
}

void MainWindow::Show() {
    BWindow::Show();
    FillStocksList();
}

void MainWindow::FillStocksList() {
    stocksPanelView->FillCustomStocksList();
}

void MainWindow::MessageReceived(BMessage *msg) {
    switch (msg->what) {
        case (BPrivate::Network::UrlEvent::RequestCompleted): {
            std::cout << "Request Completed " << std::endl;
            ResultHandler(msg->GetInt32(BPrivate::Network::UrlEventData::Id, -1));
            break;
        }
        default: {
            BWindow::MessageReceived(msg);
            break;
        }
    }
}

void
MainWindow::ResultHandler(int requestId) {
    std::cout << "Request with ID " << requestId << " completed." << std::endl;
    stocksPanelView->HandleResult(requestId);
    //chartView->HandleResult(result);
    // Weiterleiten an andere Interessenten
}

bool MainWindow::QuitRequested() {
    be_app->PostMessage(B_QUIT_REQUESTED);
    return true;
}
