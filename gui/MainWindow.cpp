#include "MainWindow.h"

#include "chartView/ChartView.h"
#include "../api/NetRequester.h"
#include "stocksPanel/SearchFieldControl.h"
#include <Application.h>
#include <InterfaceKit.h>
#include <Layout.h>
#include <LayoutBuilder.h>
#include <Window.h>
#include <private/netservices2/NetServicesDefs.h>
#include <iostream>

MainWindow::MainWindow()
        : BWindow(BRect(100, 100, 500, 400), "Stocks", B_TITLED_WINDOW,
                  B_ASYNCHRONOUS_CONTROLS){

    SetWindowSizes();
    delayedQueryTimer = new DelayedQueryTimer(BMessenger(this));
    stocksPanelView = new StocksPanelView();
    chartView = new ChartView();
    BLayoutBuilder::Group<>((BWindow *) this, B_HORIZONTAL, 0)
            .SetInsets(0)
            .Add(stocksPanelView, 1)
            .Add(chartView, 3);
}

void
MainWindow::SetWindowSizes() {
    BRect screenFrame = (BScreen(this)).Frame();
    SetSizeLimits(700.0, screenFrame.Width(),500.0, screenFrame.Height());
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
        case (M_START_SHARES_SEARCH) : {
            std::cout << "A textfield change" << std::endl;
            BString searchTerm;
            if (msg->FindString("search terms", &searchTerm) != B_OK) {
                searchTerm = "";
            }
            RequestForSearch(searchTerm);
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
}

void
MainWindow::RequestForSearch(BString searchTerm) {
    (void) searchTerm;
    delayedQueryTimer->RunQuery(new std::string(searchTerm.String()));
}

bool MainWindow::QuitRequested() {
    be_app->PostMessage(B_QUIT_REQUESTED);
    return true;
}
