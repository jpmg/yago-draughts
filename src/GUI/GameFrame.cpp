#include "BoardPanel.h"
#include "GameFrame.h"
#include "InfoPanel.h"

GameFrame::GameFrame(const wxString& title, const wxSize& winSize): wxFrame(NULL, wxID_ANY, _T("Best game ever !!!"), wxDefaultPosition, winSize)
{
    // create a sizer
    wxBoxSizer *sizer_horizontal = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(sizer_horizontal);

    // create a panel for the board
    BoardPanel *board = new BoardPanel(this);
    sizer_horizontal->Add(board, 2, wxALL | wxEXPAND, 2);

    // create panel for game info
    InfoPanel *datas = new InfoPanel(this);
    sizer_horizontal->Add(datas, 1, wxALL | wxEXPAND, 2);
}

GameFrame::~GameFrame()
{
    //dtor
}
