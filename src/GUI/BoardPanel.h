#ifndef BOARDPANEL_H
#define BOARDPANEL_H

#include <wx/wx.h>

class BoardPanel: public wxPanel
{
    public:
        BoardPanel(wxWindow* parent);
        virtual ~BoardPanel();
        void paintEvent(wxPaintEvent & evt);
        void render(wxDC&  dc);
        DECLARE_EVENT_TABLE();
    protected:
    private:
};

#endif // BOARDPANEL_H
