#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <wx/wx.h>

#include "BoardPanel.h"
#include "InfoPanel.h"

class GameFrame : public wxFrame
{
    public:
        GameFrame(const wxString& title, const wxSize& winSize);
        virtual ~GameFrame();
        DECLARE_EVENT_TABLE();
    protected:
    private:
        void sizeEvent(wxSizeEvent& event);
        BoardPanel* m_board;
        InfoPanel* m_datas;
};

#endif // GAMEFRAME_H
