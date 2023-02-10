#include "MainWindow.h"

#include <Application.h>
#include <StringView.h>
#include <Window.h>

MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,500,400),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	
	BRect frame(10,10,11,11);
	
	BStringView *label = new BStringView(frame, "myLabel", "Haiku Rocks!");
	label ->ResizeToPreferred();
	this->AddChild(label);
}

void
MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}


bool
MainWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
