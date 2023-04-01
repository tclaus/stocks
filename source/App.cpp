#ifndef APP_CPP_
#define APP_CPP_

#include "App.h"
#include "gui/MainWindow.h"

App::App() : BApplication("application/x-vnd.tclaus-StocksApp") {
    window = new MainWindow();
    window->Show();
}

int main() {
    App *app = new App();
    app->Run();
    delete app;
    return 0;
}

#endif // APP_CPP_
