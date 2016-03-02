#ifndef GAMEBOARD_H_INCLUDED
#define GAMEBOARD_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include "Utility/Maths.h"
#include "Base/Elements.h"
#include "Base/Gotti.h"

const float boardColor[5][4] = {  {0.4,0.4,0.3, 0.3},
                            //{0.4, 0.4, 0.3, 0.5},
                            /*{0.0, 0.1, 0.2, 0.6},*/	//Black Square
                            //{0.4,0.1,0.0, 0.3},
                            {0.8, 0.8, 0.7, 0.5},	//White Square
                            //{0.7,0.5,0.4, 0.3},
                            {0.5, 0.6, 0.7, 0.6},	//Border Color
                            {0.0, 0.0, 0.0, 0.5},	//Dividing lines
                            {0.4, 0.1, 0.3, 0.5}		//Highlighting the selected
                        };
class chessBoard{
public:
    chessBoard();
    chessBoard(float gap);


    chessBoard(float gap, vector2d* originAt, vector2d* padding);
    static float borderLineWidth, boardLineWidth, gap, xMargin, xPadding, yMargin, yPadding;
    static float boardVector[592];
    static float shiftX, shiftY;

    static void initBoardVertex();
    static void highLightSquares(), highLightThis(int, int, int);
    static void showBoard();
    static void showAllPieces();

protected:
    static void show1Piece(piece, float, float);
};

#endif // GAMEBOARD_H_INCLUDED
