#include "BoardPanel.h"

BEGIN_EVENT_TABLE(BoardPanel, wxPanel)
    EVT_PAINT(BoardPanel::paintEvent)
END_EVENT_TABLE()

BoardPanel::BoardPanel(wxWindow* parent): wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE)
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
    // get size of the parent
    int currentHeight;
    int currentWidth;
    this->GetSize(&currentWidth, &currentHeight);

    int cellSize = (currentHeight)/10;
    int offset = (currentHeight - (cellSize*10))/2;

    dc.SetBrush(*wxGREY_BRUSH);
    dc.SetPen(*wxTRANSPARENT_PEN);
    for(int i=0; i<10;i++)
    {
        for(int j=0; j<10;j++)
        {
            if((i+j)%2==0)
            {
                dc.DrawRectangle(offset+i*cellSize,
                                 offset+j*cellSize,
                                 cellSize,
                                 cellSize);
            }
        }
    }
}
