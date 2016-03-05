/***************************************************************
 * Name:      KittyWxMain.h
 * Purpose:   Defines Application Frame
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#ifndef KITTYWXMAIN_H
#define KITTYWXMAIN_H


//(*Headers(MainFrame)
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
#include <wx/aui/aui.h>
#include <wx/textctrl.h>
//*)

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
	static const long ID_KittyPanel;
	static const long ID_PlayerNameSText;
	static const long ID_TEXTCTRL1;
	static const long ID_STATICTEXT1;
	static const long ID_COMBOBOX1;
	static const long ID_STATICTEXT2;
	static const long ID_TEXTCTRL2;
	static const long ID_PANEL2;
	static const long ID_AboutHelpSubItem;
	//*)

	//(*Declarations(MainFrame)
	wxMenuItem* MenuItem1;
	wxStaticText* PlayerNameSText;
	wxMenu* Menu1;
	wxPanel* KittyPanel;
	wxStaticText* StaticText1;
	wxPanel* Panel2;
	wxComboBox* ComboBox1;
	wxTextCtrl* TextCtrl1;
	wxMenuBar* MenuBar1;
	wxStaticText* StaticText2;
	wxAuiManager* BaseAManager;
	wxTextCtrl* TextCtrl2;
	//*)
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* KittySBSizer;
    wxGridBagSizer* OutermostGBSizer;
    wxStaticBoxSizer* StaticBoxSizer1;


	ChessCanvas* KittyCanvas;

	DECLARE_EVENT_TABLE()
};

#endif // KITTYWXMAIN_H
