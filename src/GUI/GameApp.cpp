#include "GameApp.h"

IMPLEMENT_APP(GameApp);

GameApp::GameApp()
{
    //ctor
}

GameApp::~GameApp()
{
    //dtor
}

bool GameApp::OnInit()
{
    // create a 800x600 window
    wxFrame *frm=new wxFrame(NULL, wxID_ANY, _T("Best game ever !!!"), wxDefaultPosition, wxSize(800, 600));
    frm->Show();
    return true;
}
