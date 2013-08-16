#include "GameFrame.h"

BEGIN_EVENT_TABLE(GameFrame, wxFrame)
    EVT_SIZE(GameFrame::sizeEvent)
END_EVENT_TABLE()

void GameFrame::sizeEvent(wxSizeEvent& event)
{
    int heightPanel, widthPanel, heightFrame, widthFrame;
    m_board->GetSize(&widthPanel, &heightPanel);
    this->GetSize(&widthFrame, &heightFrame);
    heightFrame -= 10; // Set a margin
    widthFrame -= 10;
    if(heightPanel != widthPanel || heightPanel != heightFrame)
    {
        m_board->SetSize(5, 5, heightFrame, heightFrame);
        m_datas->SetSize(heightFrame + 7, 5, widthFrame - heightFrame - 2, heightFrame);
    }

    event.Skip();
}

GameFrame::GameFrame(const wxString& title, const wxSize& winSize): wxFrame(NULL, wxID_ANY, _T("Best game ever !!!"), wxDefaultPosition, winSize)
{
    this->SetBackgroundColour(*wxWHITE);
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
