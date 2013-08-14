#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <wx/wx.h>

class GameFrame : public wxFrame
{
    public:
        GameFrame(const wxString& title, const wxSize& winSize);
        virtual ~GameFrame();
    protected:
    private:
};

#endif // GAMEFRAME_H
