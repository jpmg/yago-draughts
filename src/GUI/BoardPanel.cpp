#include "BoardPanel.h"

BEGIN_EVENT_TABLE(BoardPanel, wxPanel)
    EVT_PAINT(BoardPanel::paintEvent)
END_EVENT_TABLE()

BoardPanel::BoardPanel(wxWindow* parent): wxPanel(parent)
{
    //ctor
}

BoardPanel::~BoardPanel()
{
    //dtor
}

void BoardPanel::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

// draw the game board
void BoardPanel::render(wxDC&  dc)
{
    int cellSize = 64;
    dc.SetBrush(*wxGREY_BRUSH);
    dc.SetPen(*wxTRANSPARENT_PEN);
    for(int i=0; i<10;i++)
    {
        for(int j=0; j<10;j++)
        {
            if((i+j)%2==0)
            {
                dc.DrawRectangle(i*cellSize,
                                 j*cellSize,
                                 cellSize,
                                 cellSize);
            }
        }
    }
}
