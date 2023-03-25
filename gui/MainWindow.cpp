#include "MainWindow.h"

#include "chartView/ChartView.h"
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
                  B_ASYNCHRONOUS_CONTROLS) {

    SetWindowSizes();
    stocksPanelView = new StocksPanelView();
    chartView = new ChartView();
    delayedQueryTimer = new DelayedQueryTimer(this);

    BLayoutBuilder::Group<>((BWindow *) this, B_HORIZONTAL, 0)
            .SetInsets(0)
            .Add(stocksPanelView, 1)
            .Add(chartView, 3);
    Init();
}

MainWindow::~MainWindow() {
    delayedQueryTimer->StopThread();
}

void MainWindow::Init() {
    delayedQueryTimer->StartThread();
}

void
MainWindow::SetWindowSizes() {
    BRect screenFrame = (BScreen(this)).Frame();
    SetSizeLimits(700.0, screenFrame.Width(), 500.0, screenFrame.Height());
}

void MainWindow::Show() {
    BWindow::Show();
}

void MainWindow::MessageReceived(BMessage *msg) {
    switch (msg->what) {
        case (BPrivate::Network::UrlEvent::RequestCompleted): {
            std::cout << "Request Completed " << std::endl;
            ResultHandler(msg->GetInt32(BPrivate::Network::UrlEventData::Id, -1));
            break;
        }
        case (SearchFieldMessages::M_START_SHARES_SEARCH) : {
            BString searchTerm;
            if (msg->FindString(SEARCH_TERM, &searchTerm) != B_OK) {
                searchTerm = "";
            }
            RequestForSearch(searchTerm);
            break;
        }
        case (DelayedQueryTimerMessages::CHARACTER_DELAY_EXPIRED) : {
            const char *searchQuery = msg->FindString(SEARCH_FOR_TEXT);
            std::cout << "Now run the query with: " << searchQuery << std::endl;
            stocksPanelView->SearchForSymbol(searchQuery);
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
MainWindow::RequestForSearch(BString &searchTerm) {
    delayedQueryTimer->RunQuery(new std::string(searchTerm.String()));
}

bool MainWindow::QuitRequested() {
    be_app->PostMessage(B_QUIT_REQUESTED);
    return true;
}
