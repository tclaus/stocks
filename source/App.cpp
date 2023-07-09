#ifndef APP_CPP_
#define APP_CPP_

#include "App.h"
#include "gui/MainWindow.h"
#include "FinancialmodelingApiKey.h"

App::App() : BApplication("application/x-vnd.tclaus-StocksApp") {
    window = new MainWindow();
    window->Show();
}

int main() {
    App::checkForApiKey();

    App *app = new App();
    app->Run();
    delete app;
    return 0;
}

void
App::checkForApiKey() {
    if (FinancialmodelingApiKey::GetApiKey().empty()) {
        const char *no_api_key_set = "No API key set in build. Rebuild app with API key set in the environment. "
                                     "Have a look in the readme file.";
        throw std::invalid_argument(no_api_key_set);
    }
}

#endif // APP_CPP_
