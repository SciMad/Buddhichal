#ifndef DISPLAYCANVAS_H
#define DISPLAYCANVAS_H

#include <wx/glcanvas.h>
//#include <wx/wx.h>


class ChessCanvas : public wxGLCanvas
{
	public:
       	ChessCanvas(wxWindow*);
        virtual ~ChessCanvas();
	protected:
        DECLARE_EVENT_TABLE()
	private:
        wxGLContext* MyContext;

        void OnPaint(wxPaintEvent&);
        void OnKeyPress(wxKeyEvent&);
        void DrawTriangle();
        void Render();
        void StartDrawing(void);
        void TimerFunc(int); 
        void ChangeSize(int,int);

};

#endif // DISPLAYCANVAS_H
