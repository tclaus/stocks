#ifndef _APP_CPP_
#define _APP_CPP_

#include "App.h"
#include "gui/MainWindow.h"

App::App(void) : BApplication("application/x-vnd.dw-StocksApp") {
  window = new MainWindow();
  window->Show();
}

int main(void) {
  App *app = new App();
  app->Run();
  delete app;
  return 0;
}

#endif // _APP_CPP_
