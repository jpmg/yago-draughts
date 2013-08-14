#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <wx/wx.h>
#include "GameFrame.h"

class GameApp : public wxApp
{
    public:
        GameApp();
        virtual ~GameApp();
        virtual bool OnInit();
    protected:
    private:
};

#endif // GAMEAPP_H
