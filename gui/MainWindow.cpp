#include "MainWindow.h"

#include "chartView/ChartView.h"
#include "stocksPanel/StocksPanelView.h"
#include <Application.h>
#include <InterfaceKit.h>
#include <Layout.h>
#include <LayoutBuilder.h>
#include <View.h>
#include <Window.h>

MainWindow::MainWindow()
        : BWindow(BRect(100, 100, 500, 400), "Stocks", B_TITLED_WINDOW,
                  B_ASYNCHRONOUS_CONTROLS) {

    BView *stocksPanelView = new StocksPanelView();
    BView *mainView = new ChartView();

    BLayoutBuilder::Group<>((BWindow *) this, B_HORIZONTAL, 0)
            .SetInsets(0)
            .Add(stocksPanelView, 1)
            .Add(mainView, 3);
}

void MainWindow::MessageReceived(BMessage *msg) {
    switch (msg->what) {
        default: {
            BWindow::MessageReceived(msg);
            break;
        }
    }
}

bool MainWindow::QuitRequested() {
    be_app->PostMessage(B_QUIT_REQUESTED);
    return true;
}
