#include "GLWindow.h"

int main(int argc, char** argv){

    myGLwindow* window1 = new myGLwindow(722,722, "Hello Brother Bro");


    window1->initWindowGraphics();

    window1->showWindow();

    window1->loopWindow();


}
