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

        //PLACEHOLDER
        enum STATE
        {
            VOID = 0, WHITE = 1, BLACK = 2, KING = 4, CAPTURED = 8
        };
        int* m_gameBoard;
        //END PLACEHOLDER
};

#endif // BOARDPANEL_H
