#include "Board.h"
#include "GLWindow.h"
float chessBoard::borderLineWidth=5.0, chessBoard::boardLineWidth=3.0, chessBoard::gap=80, chessBoard::xMargin=20, chessBoard::xPadding=6, chessBoard::yMargin=20, chessBoard::yPadding=6;
float chessBoard::boardVector[592];
float chessBoard::shiftX, chessBoard::shiftY;

void chessBoard::initBoardVertex(){
    //gap = squareGap
    int c=-1,i,j;
    /*----- Set vertex for 9 vertical and 9 horizontal lines  --------*/
    for (i=0; i<9; i++) {
        boardVector[++c] = xMargin + xPadding+ gap*i; boardVector[++c] = yMargin + yPadding + gap *0;
        boardVector[++c] =  boardVector[c-2]; boardVector[++c] = yMargin + yPadding+ gap *8;
    }
    for (i=0; i<9; i++) {
        boardVector[++c] = xMargin + xPadding + gap *0; boardVector[++c] = yMargin + yPadding + gap*i;
        boardVector[++c] = xMargin + xPadding+ gap *8; boardVector[++c] =  boardVector[c-2];
    }

    /*-----Set vertex of border in array (72 to 79 for 4 corners)--------*/
    boardVector[++c] = xMargin; 									boardVector [++c] = yMargin;
    boardVector[++c] = xMargin; 									boardVector [++c] = yMargin + yPadding + gap*8 + yPadding;
    boardVector[++c] = xMargin + xPadding + gap*8 + xPadding; 		boardVector[++c] = yMargin + yPadding + gap*8 + yPadding;
    boardVector[++c] = xMargin + xPadding + gap*8 + xPadding; 		boardVector[++c] =yMargin;

    /*----- Now creating 64 polygons for 64 squares (index: [80 to 591]) 64*4 vertices with 64*4*2 i.e. x,y data ------- ~101 */
    for (j=0; j<8; j++) {
        for (i=0; i<8; i++){
            boardVector[++c] = xMargin + xPadding+ boardLineWidth/2+ gap*i;		boardVector[++c] = yMargin + yPadding+ boardLineWidth/2+ gap*j;
            boardVector[++c] = xMargin + xPadding+ boardLineWidth/2+ gap*i;		boardVector[++c] = yMargin + yPadding- boardLineWidth/2+ gap*(j+1);
            boardVector[++c] = xMargin + xPadding- boardLineWidth/2+ gap*(i+1);	boardVector[++c] = yMargin + yPadding- boardLineWidth/2+ gap*(j+1);
            boardVector[++c] = xMargin + xPadding- boardLineWidth/2+ gap*(i+1);	boardVector[++c] = yMargin + yPadding+ boardLineWidth/2+ gap*j;
        }
    }
}

void  chessBoard::showBoard(){
    int i,j;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	/* ----------------------------------------------------------- Draw Border of square Chess Board ----------------------- */
	glColor4fv(boardColor[2]);
	glVertexPointer(2,GL_FLOAT,0,	boardVector /* + 72*sizeof(float) */);
	glLineWidth(borderLineWidth);
	glBegin(GL_LINE_LOOP);						//might need to replace by GL_POLYGON
		for (i=0; i<4; i++){
			glVertex2fv(boardVector + 72 + i*2);
		}
	glEnd();

	/*------------------------------------------------- Now Draw Dividing Lines ---------------------------------------------*/
	glColor4fv(boardColor[3]);
	glVertexPointer(2,GL_FLOAT,0,boardVector);	//Load 2 float elements at a time, with stride 0 from boardVector
	glLineWidth(boardLineWidth);
	glBegin(GL_LINES);
		for (i=0; i<36;i++){
			glVertex2fv(boardVector+i*2);		//glArrayElement(); can also be used (referring to single data??)
		}
	glEnd();

	/* ------------------------------------------------ Now Draw Alternate Squares -------------------------------------------- */
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_LINE);

	glFrontFace(GL_CW);
	glVertexPointer(2,GL_FLOAT,0, boardVector);
	for (i=0; i<64; i++){
		glBegin(GL_POLYGON);
			glColor4fv(boardColor[(i/8)%2!=0?(1-i%2):(i%2)]);	//Haha, trick to paint alternate white and black... ;)	:D7
			for (j=0; j<4; j++){
				glVertex2fv(boardVector + 80 + i*8 + j*2);		//The offset 80 is used since the data of the square vertex start from 80th index
			}
		glEnd();
	}
}


void chessBoard::highLightSquares(){
    if (!(game::selectedPos<0 || game::selectedPos>63)) highLightThis(game::selectedPos, lightPurple, GL_FILL);

		if (game::currentSituation >= sourceSelected){
			//highlight possible squares too :D
			game::currentPossibleSet.refresh(game::sourcedPos);						//to remove previous possible moves (by making the possibleMovesCount to zero) and to sourcedPos
			game::currentPossibleSet.listOut();
			for (int i = 0; i <game::currentPossibleSet.possibleMovesCount; ++i){
				highLightThis(game::currentPossibleSet.possibleMoves[i].toWhere, game::currentPossibleSet.possibleMoves[i].thisMove, GL_FILL);	//purple ko satta :: currentPossibleSet.possibleMoves[i].thisMove
			}

			if (game::currentPossibleSet.possibleMovesCount<=0){
				highLightThis(game::sourcedPos, yellow, GL_LINE);
			}else{
				highLightThis(game::sourcedPos, brown, GL_LINE);
			}
		}
}

void chessBoard::highLightThis(int tempPos, int tempColor, int fillStyle){	//'gameColorsIndex tempColor' was initially used. but it's changed to int for using color indexed from moveType
    int j;
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glLineWidth(10);
    glPolygonMode(GL_FRONT,fillStyle);		//fillStyle is either GL_LINE or GL_FILL
    glPolygonMode(GL_BACK,GL_LINE);

    glFrontFace(GL_CW);
    glVertexPointer(2,GL_FLOAT,0, boardVector);
    glBegin(GL_POLYGON);
    glColor4fv(gameColor[tempColor]);
    //glColor4f(1.0,0.9,0.2,0.5);
    //glColor4f(0.8,0.2,0.2,0.5);			//Red, the blood of angry men.
    //glColor4f(0.0,1.0,0.1, 0.5);			//Black, the dark of ages past.
    for (j=0; j<4; j++){
        glVertex2fv(boardVector + 80 + tempPos*8 + j*2);		//The offset 80 is used since the data of the square vertex start from 80th index
    }
    glEnd();
}

void chessBoard::showAllPieces(){
    int k;

    glDisableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);
    glLineWidth(gottiSet::pieceBorderWidth);
    glFrontFace(GL_CW);

    for (k=0; k<32;k++){
        if (k!=game::sourcedPieceIndex) show1Piece(gottiSet::BW[k],0,0);
    }

    //Now for dragging the piece if k==
    show1Piece(gottiSet::BW[game::sourcedPieceIndex], shiftX, shiftY);//show1Piece(BW[sourcedPieceIndex], shiftX, shiftY);
    //glutPostRedisplay();
}

void chessBoard::show1Piece(piece tempPiece,float originX, float originY){
    int i,j,k;
    float x,y;
    int v;				//V for vertex number, first vertex, second vertex, ...
    glColor3fv(pieceColor3f[tempPiece.color]);
    for (i=0; i<numberOfTriangles[tempPiece.whoAmI]; i++){
        glBegin(GL_TRIANGLES);
            for (j=0; j<3; j++){
                v = pieceTriangleIndices[tempPiece.whoAmI][i][j];
                //x = xMargin + xPadding+ (tempPiece.x()-1)*gap+ 1*pieceVertices[tempPiece.whoAmI][v][0];			For 1,1 based system #100
                //y =  yMargin + yPadding+ (tempPiece.y()-1)*gap + 1*pieceVertices[tempPiece.whoAmI][v][1];			For 1,1 based grid system

                x = originX + xMargin + xPadding+ tempPiece.x()*gap + 1*pieceVertices[tempPiece.whoAmI][v][0];
                y = originY + yMargin + yPadding+ tempPiece.y()*gap + 1*pieceVertices[tempPiece.whoAmI][v][1];

                glVertex2f(x,y);
            }
        glEnd();
    }

    glColor3fv(pieceColor3f[1 - tempPiece.color]);			//white pieces bordered by black lines and vice versa
    for (i=0; i<numberOfLines[tempPiece.whoAmI]; i++){
        glBegin(GL_LINES);
            for (j=0; j<2; j++){
                v = pieceLineIndices[tempPiece.whoAmI][i][j];
                //x = xMargin + xPadding+ (tempPiece.x()-1)*gap+ 1*pieceVertices[tempPiece.whoAmI][v][0];		#100
                //y =  yMargin + yPadding+ (tempPiece.y()-1)*gap + 1*pieceVertices[tempPiece.whoAmI][v][1];
                x =  xMargin + xPadding+ tempPiece.x()*gap+ 1*pieceVertices[tempPiece.whoAmI][v][0];
                y =  yMargin + yPadding+ tempPiece.y()*gap+ 1*pieceVertices[tempPiece.whoAmI][v][1];

                glVertex2f(originX+x,originY+y);
            }
        glEnd();
    }
}
