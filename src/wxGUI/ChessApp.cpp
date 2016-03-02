/***************************************************************
 * Name:      ChessApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#include "wxGUI/ChessApp.h"

//(*AppHeaders
#include "wxGUI/MainFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ChessApp);

bool ChessApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        MainFrame* Frame = new MainFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
