#include "BoardPanel.h"

BEGIN_EVENT_TABLE(BoardPanel, wxPanel)
    EVT_PAINT(BoardPanel::render)
END_EVENT_TABLE()

BoardPanel::BoardPanel(wxWindow* parent): wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE)
{
    //ctor
}

BoardPanel::~BoardPanel()
{
    //dtor
}

// draw the game board
void BoardPanel::render(wxPaintEvent & evt)
{
    wxPaintDC dcWhite(this);
    wxPaintDC dcBlack(this);

    // get size of the parent
    int currentHeight;
    int currentWidth;
    this->GetSize(&currentWidth, &currentHeight);

    // compute offset
    int cellSize = currentHeight/10;
    int offset = (currentHeight - (cellSize*10))/2;

    dcWhite.SetBrush(*wxWHITE_BRUSH);
    dcWhite.SetPen(*wxTRANSPARENT_PEN);
    dcBlack.SetBrush(*wxGREY_BRUSH);
    dcBlack.SetPen(*wxTRANSPARENT_PEN);
    for(int i=0; i<10;i++)
    {
        for(int j=0; j<10;j++)
        {
            if((i+j)%2==0)
            {
                dcWhite.DrawRectangle(offset+i*cellSize,
                                 offset+j*cellSize,
                                 cellSize,
                                 cellSize);
            }
            else
            {
                dcBlack.DrawRectangle(offset+i*cellSize,
                                 offset+j*cellSize,
                                 cellSize,
                                 cellSize);
            }
        }
    }
}
