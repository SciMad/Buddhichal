/***************************************************************
 * Name:      TestGLMinimalMain.h
 * Purpose:   Defines Application Frame
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#ifndef TESTGLMINIMALMAIN_H
#define TESTGLMINIMALMAIN_H

//(*Headers(MainFrame)
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

#include "OGL/GLWindow.h"
#include "wxGUI/GLPanel.h"
#include "wxGUI/ChessCanvas.h"

class MainFrame: public wxFrame 
{
    public:

        MainFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~MainFrame();

    private:

        //(*Handlers(MainFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(MainFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(MainFrame)
        wxStatusBar* StatusBar1;
        //*)
        //
        ChessCanvs* ChessBoardArea;

        DECLARE_EVENT_TABLE()
};

#endif // TESTGLMINIMALMAIN_H
