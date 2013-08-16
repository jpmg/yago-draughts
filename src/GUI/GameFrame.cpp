#include "GameFrame.h"

BEGIN_EVENT_TABLE(GameFrame, wxFrame)
    EVT_SIZE(GameFrame::sizeEvent)
END_EVENT_TABLE()

GameFrame::GameFrame(const wxString& title, const wxSize& winSize): wxFrame(NULL, wxID_ANY, _T("Best game ever !!!"), wxDefaultPosition, winSize)
{
    this->SetBackgroundColour(*wxLIGHT_GREY);
    this->SetDoubleBuffered(true);
    // create a panel for the board
    m_board = new BoardPanel(this);

    // create panel for game info
    m_datas = new InfoPanel(this);
}

GameFrame::~GameFrame()
{
    //dtor
}

void GameFrame::sizeEvent(wxSizeEvent& event)
{
    int heightPanel, widthPanel, heightFrame, widthFrame;
    m_board->GetClientSize(&widthPanel, &heightPanel);
    this->GetClientSize(&widthFrame, &heightFrame);
    if(heightPanel != widthPanel || heightPanel != heightFrame)
    {
        m_board->SetSize(0, 0, heightFrame, heightFrame);
        m_datas->SetSize(heightFrame, 0, widthFrame - heightFrame, heightFrame);
    }

    event.Skip();
}
