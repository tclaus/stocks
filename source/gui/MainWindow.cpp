#include "MainWindow.h"

#include "chartView/ChartView.h"
#include "stocksPanel/SearchFieldControl.h"
#include <Application.h>
#include <InterfaceKit.h>
#include <LayoutBuilder.h>
#include "utils/EscapeCancelFilter.h"
#include "QuoteRequestStore.h"
#include <Window.h>
#include <private/netservices2/NetServicesDefs.h>

MainWindow::MainWindow()
        : BWindow(BRect(100, 100, 500, 400), "Stocks", B_TITLED_WINDOW,
                  B_ASYNCHRONOUS_CONTROLS),
          fQuoteResultHandler( new QuoteResultHandler()){

    SetWindowSizes();
    fStocksPanelView = new StocksPanelView();
    chartView = new ChartView();
    delayedQueryTimer = new DelayedQueryTimer(this);

    BLayoutBuilder::Group<>((BWindow *) this, B_HORIZONTAL, 0)
            .SetInsets(0)
            .Add(fStocksPanelView, 1)
            .Add(chartView, 3);
    Init();
}

MainWindow::~MainWindow() {
    delayedQueryTimer->StopThread();
    delete fQuoteResultHandler;
}

void
MainWindow::Init() {
    delayedQueryTimer->StartThread();
    AddCommonFilter(new EscapeCancelFilter());
}

void
MainWindow::SetWindowSizes() {
    BRect screenFrame = (BScreen(this)).Frame();
    SetSizeLimits(700.0, screenFrame.Width(), 500.0, screenFrame.Height());
}

void
MainWindow::Show() {
    BWindow::Show();
}

void
MainWindow::MessageReceived(BMessage *message) {
    switch (message->what) {
        case (SearchFieldMessages::M_START_SHARES_SEARCH) : {
            BString searchTerm;
            if (message->FindString(SEARCH_TERM, &searchTerm) != B_OK) {
                searchTerm = "";
            }
            RequestForSearch(searchTerm);
            break;
        }
        case (BPrivate::Network::UrlEvent::RequestCompleted): {
            ResultHandler(message->GetInt32(BPrivate::Network::UrlEventData::Id, -1));
            break;
        }
        case (SearchFieldMessages::M_DISMISS_SEARCH) : {
            fStocksPanelView->DismissSearch();
            break;
        }
        case (SearchFieldMessages::M_ACCEPT_SELECTION) : {
            fStocksPanelView->AcceptSearch();
            break;
        }

        case (DelayedQueryTimerMessages::CHARACTER_DELAY_EXPIRED) : {
            const char *searchQuery = message->FindString(SEARCH_FOR_TEXT);
            fStocksPanelView->SearchForSymbol(searchQuery);
            break;
        }
        default: {
            BWindow::MessageReceived(message);
            break;
        }
    }
}

void
MainWindow::ResultHandler(int requestId) {
    fStocksPanelView->HandleResult(requestId);
    fQuoteResultHandler->HandleQuoteResults(requestId);
}
void
MainWindow::RequestForSearch(BString &searchTerm) {
    delayedQueryTimer->RunQuery(new std::string(searchTerm.String()));
}

bool
MainWindow::QuitRequested() {
    be_app->PostMessage(B_QUIT_REQUESTED);
    return true;
}
