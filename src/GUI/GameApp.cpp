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
    // create the game window
    GameFrame *frm=new GameFrame(_T("Best game ever !!!"), wxSize(989, 685));
    frm->Show();
    return true;
}
