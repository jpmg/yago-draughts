#ifndef BOARDPANEL_H
#define BOARDPANEL_H

#include <wx/wx.h>

class BoardPanel: public wxPanel
{
    public:
        BoardPanel(wxWindow* parent);
        virtual ~BoardPanel();
        DECLARE_EVENT_TABLE();
    protected:
    private:
        void render(wxPaintEvent & evt);
        void mouseEvent(wxMouseEvent& evt);

        //PLACEHOLDER
        enum STATE
        {
            EMPTY = 0, WHITE = 1, BLACK = 2, KING = 4, CAPTURED = 8
        };
        int* m_gameBoard;
        //END PLACEHOLDER

        // Device Contexts
        wxBrush m_whiteSquareBrush;
        wxBrush m_blackSquareBrush;
        wxColor m_whiteManBrush;
        wxColor m_whiteManPen;
        wxColor m_blackManBrush;
        wxColor m_blackManPen;
        wxColor m_kingColor;
        wxFont m_kingFont;

        // Drawing variables
        int m_offset;
        int m_cellSize;

        // Moving variables
        bool m_isMoving;
        int m_numOriginSquare;
        long m_previousX;
        long m_previousY;
};

#endif // BOARDPANEL_H
