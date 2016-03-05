#include <sstream>

#include <wx/msgdlg.h>

#include "wxGUI/ChessCanvas.h"

const long ChessCanvas::ID_ChessCanvas = wxNewId();

BEGIN_EVENT_TABLE(ChessCanvas,wxGLCanvas)
    EVT_PAINT(ChessCanvas::OnPaint)
    EVT_KEY_DOWN(ChessCanvas::OnKeyPress)
END_EVENT_TABLE()


ChessCanvas::ChessCanvas(wxWindow*Parent):
    wxGLCanvas(Parent, ID_ChessCanvas,  wxDefaultPosition, 
    wxSize(150,100), 0, wxT("GLCanvas"))
{
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc,argv);
    MyContext = new wxGLContext(this);
    //Initialize();
}

void ChessCanvas::Initialize()
{
	SetCurrent(*MyContext);
}


void ChessCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    SetCurrent();
	static bool OneTime = false;
	if(OneTime == false)
	{
		//LoadAllImages();
	    OneTime = true;
	}
    glClearColor(0.0f,0.5f,0.4f,0);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawTriangle();
    showWindow();
    ShowChess();
    //Render();
    glFlush();
    SwapBuffers();
}

void ChessCanvas::RegisterHandlers()
{
    //Overriding the base class function
}


void ChessCanvas::OnKeyPress(wxKeyEvent& event)
{
    //wxMessageBox(wxT(" You pressed a key "),wxT("Bravoo "));
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
    //glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
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


void ChessCanvas::DisplayCards()
{
    //glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
}

void ChessCanvas::LoadAllImages()
{

}

void ChessCanvas::Render()
{
    std::ostringstream Info;
    Info<<"Press 1 through  9 to select corresponding card ";
    //Cout(const_cast<char*>(Info.str().c_str()),-.8,0,0); //Printing function
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

GLuint ChessCanvas::LoadImageFile(std::string FileName)
{
	//wxImage* img = new wxImage(wxString::FromUTF8(FileName.c_str()));
	wxImage* img = new wxImage(wxString::FromUTF8(FileName.c_str()));

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLubyte *bitmapData=img->GetData();
	GLubyte *alphaData=img->GetAlpha();

	int bytesPerPixel = img->HasAlpha() ?  4 : 3;
	int imageWidth = img->GetWidth();
	int imageHeight = img->GetHeight();

	int imageSize = imageWidth * imageHeight * bytesPerPixel;
	GLubyte *imageData=new GLubyte[imageSize];

	int rev_val=imageHeight-1;

	for(int y=0; y<imageHeight; y++)
	{
		for(int x=0; x<imageWidth; x++)
		{
			imageData[(x+y*imageWidth)*bytesPerPixel+0]=
					bitmapData[( x+(rev_val-y)*imageWidth)*3];

			imageData[(x+y*imageWidth)*bytesPerPixel+1]=
					bitmapData[( x+(rev_val-y)*imageWidth)*3 + 1];

			imageData[(x+y*imageWidth)*bytesPerPixel+2]=
					bitmapData[( x+(rev_val-y)*imageWidth)*3 + 2];

			if(bytesPerPixel==4) imageData[(x+y*imageWidth)*bytesPerPixel+3]=
					alphaData[ x+(rev_val-y)*imageWidth ];
		}
	}

	glTexImage2D(GL_TEXTURE_2D,
					0,
					bytesPerPixel,
					imageWidth,
					imageHeight,
					0,
					img->HasAlpha() ?  GL_RGBA : GL_RGB,
					GL_UNSIGNED_BYTE,
					imageData);

	delete[] imageData;
	wxDELETE(img);
	return texture;
}
