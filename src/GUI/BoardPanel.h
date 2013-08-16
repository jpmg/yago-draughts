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
        void paintEvent(wxPaintEvent & evt);
        void render(wxDC&  dc);
};

#endif // BOARDPANEL_H
