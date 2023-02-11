#include "MainWindow.h"

#include "stocksPanel/StocksPanelView.h"
#include "chartView/ChartView.h"
#include <Application.h>
#include <GroupLayout.h>
#include <InterfaceKit.h>
#include <Layout.h>
#include <LayoutBuilder.h>
#include <StringView.h>
#include <View.h>
#include <Window.h>

MainWindow::MainWindow(void)
    : BWindow(BRect(100, 100, 500, 400), "Stocks", B_TITLED_WINDOW,
              B_ASYNCHRONOUS_CONTROLS) {

  BView *stocksPanelView = new StocksPanelView();
  BView *mainView = new ChartView();

  mainView->SetViewColor(0, 200, 0);

  BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
  .Add(stocksPanelView)
  .Add(mainView);
}

void MainWindow::MessageReceived(BMessage *msg) {
  switch (msg->what) {
  default: {
    BWindow::MessageReceived(msg);
    break;
  }
  
  
  }
}

bool MainWindow::QuitRequested(void) {
  be_app->PostMessage(B_QUIT_REQUESTED);
  return true;
}
