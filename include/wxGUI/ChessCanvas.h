#pragma once

#include <string>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <GL/glut.h>

#include "OGL/GLWindow.h"


class ChessCanvas : public wxGLCanvas, public GLWindow
{
public:
	ChessCanvas(wxWindow*);

	void OnPaint       (wxPaintEvent&);
	void DrawTriangle  ();


	void   WhenKeyIsPressed           (unsigned char,int,int);
	void   WhenSpecialKeysPressed     (int,int,int);
	void   TimerFunc                  (int);
	void   ControlWithMouse           (int,int,int,int);
	void   StartDrawing               ();
	void   ChangeSize                 (int,int);
	void   Render                     ();
	void   LoadAllImages              ();
	void   DisplayCards               ();
	void   Initialize();


protected:
	DECLARE_EVENT_TABLE()
private:
	//int WindowWidth=800, WindowHeight=600;
	GLuint Image[54];
	bool Flipped, Scrambled;
	int BackId=1;
	wxGLContext* MyContext;


	static const long ID_ChessCanvas;
	void OnKeyPress(wxKeyEvent&);
	GLuint LoadImageFile(std::string);
	void DisplaySinglePhoto(float,float,GLuint);
};
