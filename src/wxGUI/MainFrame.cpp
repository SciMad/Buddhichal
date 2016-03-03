/***************************************************************
 * Name:      TestGLMinimalMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#include <wx/msgdlg.h>

#include "wxGUI/MainFrame.h"

//(*InternalHeaders(MainFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/sizer.h>
//*)

//(*IdInit(MainFrame)
const long MainFrame::idMenuQuit = wxNewId();
const long MainFrame::idMenuAbout = wxNewId();
const long MainFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long MainFrame::ID_ChessPanel= wxNewId();

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    //(*EventTable(MainFrame)
    //*)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent,wxWindowID id)
{
    
    wxStaticBoxSizer* GLSBSizer;

    //(*Initialize(MainFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, _("We are making chess here baby"),
            wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));

    ChessPanel = new wxPanel(this,ID_ChessPanel,wxDefaultPosition,wxDefaultSize,
            wxTAB_TRAVERSAL,_T("ID_ChessPanel"));
    
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"),
            _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"),
            _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrame::OnAbout);
    //*)
    
    GLSBSizer = new wxStaticBoxSizer(wxHORIZONTAL, ChessPanel, _("Move Cards"));
    ChessBoardArea = new ChessCanvas(ChessPanel);
    GLSBSizer->Add(ChessBoardArea,1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL,5);
    ChessBoardArea->Initialize();

}

MainFrame::~MainFrame()
{
    //(*Destroy(MainFrame)
    //*)
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("Hello"), _("Welcome to..."));
}
