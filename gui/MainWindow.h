#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>

class MainWindow : public BWindow {
public:
  MainWindow();
  void MessageReceived(BMessage *msg);
  bool QuitRequested();

private:
};

#endif
