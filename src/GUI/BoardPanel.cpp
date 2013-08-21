#include "BoardPanel.h"

BEGIN_EVENT_TABLE(BoardPanel, wxPanel)
    EVT_PAINT(BoardPanel::render)
    EVT_MOUSE_EVENTS(BoardPanel::mouseEvent)
END_EVENT_TABLE()

BoardPanel::BoardPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE),
        m_whiteSquareBrush(*wxWHITE_BRUSH), m_blackSquareBrush(*wxBLACK_BRUSH), m_whiteManBrush(230, 235, 255), m_whiteManPen(220, 227, 245), m_blackManBrush(120, 55, 10), m_blackManPen(40, 15, 0), m_kingColor(20, 20, 20), m_kingFont(3 / 5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD)
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

    m_isMoving = false;
    m_previousX = m_previousY = 0;
    m_numOriginSquare = -1;
}

BoardPanel::~BoardPanel()
{
    //dtor
    delete m_gameBoard; // PLACEHOLDER
}

// draw the game board
void BoardPanel::render(wxPaintEvent & evt)
{
    // get size of the parent
    int currentHeight;
    int currentWidth;
    this->GetSize(&currentWidth, &currentHeight);

    // compute offset
    m_cellSize = currentHeight/10;
    m_offset = (currentHeight - (m_cellSize*10))/2;

    wxPaintDC whiteSquareDC(this);
    wxPaintDC blackSquareDC(this);
    wxPaintDC whiteManDC(this);
    wxPaintDC blackManDC(this);
    wxPaintDC kingDC(this);

    // Set square painters
    whiteSquareDC.SetBrush(m_whiteSquareBrush);
    whiteSquareDC.SetPen(*wxTRANSPARENT_PEN);
    blackSquareDC.SetBrush(m_blackSquareBrush);
    blackSquareDC.SetPen(*wxTRANSPARENT_PEN);
    
    // Set men painters
    whiteManDC.SetBrush(m_whiteManBrush);
    whiteManDC.SetPen(m_whiteManPen);
    blackManDC.SetBrush(m_blackManBrush);
    blackManDC.SetPen(m_blackManPen);
    kingDC.SetTextForeground(m_kingColor);
    m_kingFont.SetPointSize(m_cellSize * 3 / 5);
    kingDC.SetFont(m_kingFont);

    // Paint the board in white
    whiteSquareDC.DrawRectangle(0,
                     m_offset,
                     10 * m_cellSize,
                     10 * m_cellSize);
    // Paint the black squares
    for(int x=0; x<10;++x)
    {
        for(int y = (x + 1) % 2; y < 10; y += 2)
        {
            blackSquareDC.DrawRectangle(x*m_cellSize,
                             m_offset+y*m_cellSize,
                             m_cellSize,
                             m_cellSize);

            // Draw the men, if any
            int gameBoardAddress(((9 - y) * 10 + x) / 2); // The columns are drawned from top to bottom but the board is save from white's point of view, so we have to correct the y value
            wxRect drawingArea(x * m_cellSize + 2, m_offset + y * m_cellSize + 2, m_cellSize - 4, m_cellSize - 4);

            if(m_gameBoard[gameBoardAddress] & WHITE)
                whiteManDC.DrawEllipse(drawingArea);
            else if(m_gameBoard[gameBoardAddress] & BLACK)
                blackManDC.DrawEllipse(drawingArea);
            if(m_gameBoard[gameBoardAddress] & KING)
                kingDC.DrawLabel(wxT("K"), drawingArea, wxALIGN_CENTER);
        }
    }
}

void BoardPanel::mouseEvent(wxMouseEvent& evt)
{
    int numCol(evt.GetX() / m_cellSize), numRow((evt.GetY() - m_offset) / m_cellSize);

    // Square being clicked
    int gameBoardAddress(((9 - numRow) * 10 + numCol) / 2);

    // If no man is being moved and the user left-clicked a square that is not empty, we'll move the man on it
    if(!m_isMoving && evt.LeftDown() && m_gameBoard[gameBoardAddress] != EMPTY)
    {
        m_isMoving = true;
        m_numOriginSquare = gameBoardAddress;
    }
    // When the user release the click, stop moving the man and validate the move if the target square is empty
    else if(evt.LeftUp())
    {
        m_isMoving = false;
        if(m_gameBoard[gameBoardAddress] == EMPTY)
        {
            m_gameBoard[gameBoardAddress] = m_gameBoard[m_numOriginSquare];
            m_gameBoard[m_numOriginSquare] = EMPTY;
        }
        this->Refresh();
    }

    // If nothing is moving, we're done
    if(!m_isMoving)
        return;
        
    wxPaintDC whiteSquareDC(this);
    wxPaintDC blackSquareDC(this);
    wxPaintDC whiteManDC(this);
    whiteManDC.SetClippingRegion(0, m_offset, 10 * m_cellSize, 10 * m_cellSize); // Forbids drawing outside the board
    wxPaintDC blackManDC(this);
    blackManDC.SetClippingRegion(0, m_offset, 10 * m_cellSize, 10 * m_cellSize); // Forbids drawing outside the board
    wxPaintDC kingDC(this);

    // Set square painters
    whiteSquareDC.SetBrush(m_whiteSquareBrush);
    whiteSquareDC.SetPen(*wxTRANSPARENT_PEN);
    blackSquareDC.SetBrush(m_blackSquareBrush);
    blackSquareDC.SetPen(*wxTRANSPARENT_PEN);
    
    // Set men painters
    whiteManDC.SetBrush(m_whiteManBrush);
    whiteManDC.SetPen(m_whiteManPen);
    blackManDC.SetBrush(m_blackManBrush);
    blackManDC.SetPen(m_blackManPen);
    kingDC.SetTextForeground(m_kingColor);
    m_kingFont.SetPointSize(m_cellSize * 3 / 5);
    kingDC.SetFont(m_kingFont);

    // Clean the area : we may have drawn the moving man on at most 4 squares, we need to repaint them before painting the moving man at the mouse's position
    numCol = (m_previousX - m_cellSize / 2) / m_cellSize;
    numRow = (m_previousY - m_offset - m_cellSize / 2) / m_cellSize;
    for(int x = (numCol >= 0) ? numCol : 0; x < 10 && x < numCol + 2 ; ++x)
    {
        for(int y = (numRow >= 0) ? numRow : 0 ; y < 10 && y < numRow + 2 ; ++y)
        {
            if((x + y) % 2)
            {
                blackSquareDC.DrawRectangle(x*m_cellSize,
                                 m_offset+y*m_cellSize,
                                 m_cellSize,
                                 m_cellSize);

                // Draw the men, if any
                int gameBoardAddress(((9 - y) * 10 + x) / 2); // The columns are drawned from top to bottom but the board is save from white's point of view, so we have to correct the y value
                wxRect drawingArea(x * m_cellSize + 2, m_offset + y * m_cellSize + 2, m_cellSize - 4, m_cellSize - 4);

                // If the square contains the man being moved, don't draw it
                if(gameBoardAddress == m_numOriginSquare)
                    continue;

                if(m_gameBoard[gameBoardAddress] & WHITE)
                    whiteManDC.DrawEllipse(drawingArea);
                else if(m_gameBoard[gameBoardAddress] & BLACK)
                    blackManDC.DrawEllipse(drawingArea);
                if(m_gameBoard[gameBoardAddress] & KING)
                    kingDC.DrawLabel(wxT("K"), drawingArea, wxALIGN_CENTER);
            }
            else
            {
                whiteSquareDC.DrawRectangle(x*m_cellSize,
                                 m_offset+y*m_cellSize,
                                 m_cellSize,
                                 m_cellSize);
            }
        }
    }

    // Compute the drawing area
    wxRect drawingArea(evt.GetX() - m_cellSize / 2, evt.GetY() - m_cellSize / 2, m_cellSize - 4, m_cellSize - 4);

    // Draw the man
    if(m_gameBoard[m_numOriginSquare] & WHITE)
        whiteManDC.DrawEllipse(drawingArea);
    else if(m_gameBoard[m_numOriginSquare] & BLACK)
        blackManDC.DrawEllipse(drawingArea);
    if(m_gameBoard[m_numOriginSquare] & KING)
        kingDC.DrawLabel(wxT("K"), drawingArea, wxALIGN_CENTER);

    m_previousX = evt.GetX();
    m_previousY = evt.GetY();
}
