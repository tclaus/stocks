#ifndef APP_H
#define APP_H

#include <Application.h>

class App : public BApplication {
public:
    App();

    static void checkForApiKey();

private:
    BWindow *window{};
};

#endif
