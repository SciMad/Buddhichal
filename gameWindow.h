#ifndef GAMEGRAPHICS_H_INCLUDED
#define GAMEGRAPHICS_H_INCLUDED

#include "gameBoard.h"
#include "game.h"
#include "gotti.h"

enum mouseEventPosition {inBoard, outBoard};

class myGLwindow{
    int argc;
    char** argv;

public:
    enum {mouseFunction, motionFunction};

    static chessBoard* activeBoard;                         //window ko jati wota instances banaye pani, activeBoard bhaneko eutai hunebho
    static game* activeGame;

    static float windowWidth, windowHeight;
    static int mouseX, mouseY, mouseState, mouseButton, shiftX, shiftY;
    static mouseEventPosition mouseWhere;
    static void renderGraphics();
    static void reshapeWindow(int, int);                //int width, int height
    static void handleMouse(int, int);                  //int x, int y
    static void handleMouse(int, int, int, int);        //int button, int state, int x, int y

    float initx, inity;
    char* windowTitle;
    myGLwindow();
    myGLwindow(float, float, char[]);
    myGLwindow(float, float, float, float, char[]);

    void initWindowGraphics();
    void showWindow();
    void loopWindow();

    static void respondMusa(int);                       //the argument 'int' indicates which function made the call to respondMusa
    static int xMouse(int), yMouse(int);
};

#endif // GAMEGRAPHICS_H_INCLUDED
