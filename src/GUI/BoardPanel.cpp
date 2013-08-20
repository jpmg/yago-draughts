#include "BoardPanel.h"

BEGIN_EVENT_TABLE(BoardPanel, wxPanel)
    EVT_PAINT(BoardPanel::render)
END_EVENT_TABLE()

BoardPanel::BoardPanel(wxWindow* parent): wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE)
{
    //ctor
    //PLACEHOLDER
    m_gameBoard = new int[50];
    for(int i = 0 ; i < 50 ; ++i)
        m_gameBoard[i] = EMPTY;
    m_gameBoard[1] = m_gameBoard[8] = WHITE | KING;
    m_gameBoard[16] = m_gameBoard[17] = m_gameBoard[18] = m_gameBoard[25] = m_gameBoard[33] = m_gameBoard[44] = WHITE;
    m_gameBoard[21] = m_gameBoard[38] = BLACK | KING;
    m_gameBoard[35] = m_gameBoard[37] = m_gameBoard[42] = m_gameBoard[43] = BLACK;
    //END PLACEHOLDER
}

BoardPanel::~BoardPanel()
{
    //dtor
    delete m_gameBoard; // PLACEHOLDER
}

// draw the game board
void BoardPanel::render(wxPaintEvent & evt)
{
    wxPaintDC dcWhiteSquare(this);
    wxPaintDC dcBlackSquare(this);
    wxPaintDC dcWhiteMan(this);
    wxPaintDC dcBlackMan(this);
    wxPaintDC dcKing(this);

    // get size of the parent
    int currentHeight;
    int currentWidth;
    this->GetSize(&currentWidth, &currentHeight);

    // compute offset
    int cellSize = currentHeight/10;
    int offset = (currentHeight - (cellSize*10))/2;

    // Set square painters
    dcWhiteSquare.SetBrush(*wxWHITE_BRUSH);
    dcWhiteSquare.SetPen(*wxTRANSPARENT_PEN);
    dcBlackSquare.SetBrush(*wxBLACK_BRUSH);
    dcBlackSquare.SetPen(*wxTRANSPARENT_PEN);
    
    // Set men painters
    dcWhiteMan.SetBrush(wxColor(230, 235, 255));
    dcWhiteMan.SetPen(wxColor(220, 227, 245));
    dcBlackMan.SetBrush(wxColor(120, 55, 10));
    dcBlackMan.SetPen(wxColor(40, 15, 0));
    dcKing.SetTextForeground(wxColor(20, 20, 20));
    dcKing.SetFont(wxFont(cellSize * 3 / 5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // Paint the board
    for(int x=0; x<10;++x)
    {
        for(int y=0; y<10;++y)
        {
            if((x+y)%2==0)
            {
                dcWhiteSquare.DrawRectangle(offset+x*cellSize,
                                 offset+y*cellSize,
                                 cellSize,
                                 cellSize);
            }
            else
            {
                dcBlackSquare.DrawRectangle(offset+x*cellSize,
                                 offset+y*cellSize,
                                 cellSize,
                                 cellSize);

                // Draw the men, if any
                int gameBoardAddress(((9 - y) * 10 + x) / 2); // The columns are drawned from top to bottom but the board is save from white's point of view, so we have to correct the y value
                wxRect drawingArea(offset + x * cellSize + 2, offset + y * cellSize + 2, cellSize - 4, cellSize - 4);
                if(m_gameBoard[gameBoardAddress] & WHITE)
                    dcWhiteMan.DrawEllipse(drawingArea);
                else if(m_gameBoard[gameBoardAddress] & BLACK)
                    dcBlackMan.DrawEllipse(drawingArea);
                if(m_gameBoard[gameBoardAddress] & KING)
                    dcKing.DrawLabel(wxT("K"), drawingArea, wxALIGN_CENTER);
            }
        }
    }
}
