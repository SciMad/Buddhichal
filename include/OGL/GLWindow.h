#ifndef GAMEGRAPHICS_H_INCLUDED
#define GAMEGRAPHICS_H_INCLUDED

#include<string>

#include "Base/Board.h"
#include "Base/Game.h"
#include "Base/Gotti.h"

enum mouseEventPosition {inBoard, outBoard};

class GLWindow{
    int argc;
    char** argv;

public:
    enum {mouseFunction, motionFunction};

    static chessBoard* activeBoard;                         //window ko jati wota instances banaye pani, activeBoard bhaneko eutai hunebho
    static game* activeGame;

    static float windowWidth, windowHeight;
    static int mouseX, mouseY, mouseState, mouseButton, shiftX, shiftY;
    static mouseEventPosition mouseWhere;
    static void OnPaint();
    static void OnReshape(int, int);                //int width, int height
    static void OnMouseMotion(int, int);                  //int x, int y
    static void OnMouseClick(int, int, int, int);        //int button, int state, int x, int y

    float initx, inity;
    std::string windowTitle;
    GLWindow();
    GLWindow(float, float, std::string Title);
    GLWindow(float, float, float, float,std::string Title); 

    void initWindowGraphics();
    void showWindow();
    void loopWindow();

    static void respondMusa(int);                       //the argument 'int' indicates which function made the call to respondMusa
    static int xMouse(int), yMouse(int);
};

#endif // GAMEGRAPHICS_H_INCLUDED
