#include <GL/glut.h>


#include "wxGUI/GLPanel.h"

BEGIN_EVENT_TABLE(ChessCanvas,wxGLCanvas)

END_EVENT_TABLE()

ChessCanvas::ChessCanvas(wxWindow*Parent):
	wxGLCanvas(Parent, wxID_ANY,  wxDefaultPosition, wxSize(150,200), 0, wxT("GLCanvas"))
{
	int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc,argv);
    MyContext = new wxGLContext(this);
}

ChessCanvas::~ChessCanvas()
{
	//dtor
}

void ChessCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	SetCurrent();
	static bool OneTime = false;
	if(OneTime == false)
	{
        //Do tasks that's needee during creationg
	}
    glClearColor(0.0f,0.5f,0.4f,0);
    glClear(GL_COLOR_BUFFER_BIT);
    //DrawTriangle();
    Render();
    glFlush();
    SwapBuffers();
}

void ChessCanvas::OnKeyPress(wxKeyEvent& event)
{

    int Key = event.GetUnicodeKey();
    if(Key == 13)
    {
        //Enter pressed
    }

    switch(event.GetKeyCode())
    {
    case WXK_LEFT:
        break;
    case WXK_RIGHT:
        break;
    case WXK_UP:
        break;
    case WXK_DOWN:
        break;
    default:
        break;

    }
    wxPaintEvent Dummy = wxPaintEvent();
    OnPaint(Dummy);
}


void ChessCanvas::DrawTriangle()
{
    glPushMatrix();

    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
        glColor3ub((GLubyte)255,(GLubyte)0,(GLubyte)0);
        glVertex3f(0.0f,0.5f,0.0f);
        // Green on the right bottom corner
        glColor3ub((GLubyte)0,(GLubyte)255,(GLubyte)0);
        glVertex3f(0.50f,-0.90f,0.0f);
        // Blue on the left bottom corner
        glColor3ub((GLubyte)0,(GLubyte)0,(GLubyte)255);
        glVertex3f(-0.50f, -0.9000f, -0.0f);
    glEnd();
    glColor3ub((GLubyte)255,(GLubyte)255,(GLubyte)255); //reset white color.
    glPopMatrix();
}




void ChessCanvas::Render()
{

    DrawTriangle();
}

void ChessCanvas::StartDrawing(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ChessCanvas::ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.2, 200.0);
}


void ChessCanvas::TimerFunc(int value)
{
    glutPostRedisplay();
    //glutTimerFunc(10, TimerFunc, 0);
}



