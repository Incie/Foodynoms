#include<wx/app.h>
#include"MainFrame.h"


class FoodyNoms : public wxApp
{
public:
	FoodyNoms()
		:mainFrame()
	{
	}

	bool OnInit()
	{
		mainFrame = new MainFrame();
		return true;
	}

	int OnExit()
	{
		//if(mainFrame)
			//delete mainFrame;

		return 1;
	}

private:
	MainFrame *mainFrame;
};


IMPLEMENT_APP(FoodyNoms);