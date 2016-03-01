#include "../header/gameWindow.h"
#include <iostream>

float myGLwindow::windowHeight = 722;
float myGLwindow::windowWidth = 722;
int myGLwindow::mouseX, myGLwindow::mouseY, myGLwindow::mouseState, myGLwindow::mouseButton;
mouseEventPosition myGLwindow::mouseWhere = outBoard;

//game* myGLwindow::activeGame = new game(7,vsHuman);
chessBoard* myGLwindow::activeBoard;

myGLwindow::myGLwindow(float sx, float sy, float w, float h, char title[]){
    this->initx = sx;
    this->inity = sy;
    windowHeight = w;
    windowWidth = h;
    this->windowTitle = title;
}
myGLwindow::myGLwindow(float w, float h, char title[]){
    myGLwindow(0,0,w,h,title);
}
myGLwindow::myGLwindow(){
    myGLwindow(722,722,"Welcome SciMad!");
}

void myGLwindow::initWindowGraphics(){
    this->initx = 0;                                    //Ahile ekchhin ko lagi 0,0 bata start garau na;
    this->inity = 0;

    glutInit(&argc, argv);                              //arguments of the main function, global scope
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);       //Display mode.... don't know much, but could be used for back buffering and stuffs
    glutInitWindowPosition(this->initx, this->inity);   //Size of the window
	glutInitWindowSize(windowWidth, windowHeight);      //Starts the window from ...

}

void myGLwindow::showWindow(){

    glutCreateWindow("buddhiChal v1.7");                //glutCreateWindow(this->windowTitle);  //Sets the title on the title bar, but this line of code is not working right now.
    glClearColor(0.1, 0.1, 0.2, 0.5);                   //clear the color by black
    glShadeModel(GL_FLAT);                              //



    activeBoard->initBoardVertex();
    activeGame->allGotti->initPieces();
    activeGame->start(vsHuman);
    //allGotti->initPieces();

    //Rendering the Pieces will be done in renderGraphics
    glutDisplayFunc(renderGraphics);
    glutReshapeFunc(reshapeWindow);                     //
    glutMouseFunc(handleMouse);                         //glutMouseFunction
	glutMotionFunc(handleMouse);                        //glutMotionFunction

};
void myGLwindow::loopWindow(){
    glutMainLoop();
};
void myGLwindow::reshapeWindow(int w, int h){
    windowWidth = w; windowHeight = h;
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0,(GLdouble) w, 0, (GLdouble) h);    //gluOrtho2D(-(GLdouble) w/2,(GLdouble) w/2, -(GLdouble) h/2,(GLdouble) h/2);
}
void myGLwindow::handleMouse(int x, int y){
    mouseX = x; mouseY =  windowHeight - y;
    respondMusa(motionFunction);
}
void myGLwindow::handleMouse(int button, int state, int x, int y){
	mouseX = x; 			mouseY =  windowHeight - y;
	mouseState = state;		mouseButton = button;
	respondMusa(mouseFunction);
}
void myGLwindow::renderGraphics(void){
	glClear(GL_COLOR_BUFFER_BIT);

    activeBoard->showBoard();

    if(activeGame->currentSituation == moveRequested){
       activeGame->respondRequestedMove();
    }

    activeBoard->highLightSquares();

    activeBoard->showAllPieces();

    glutPostRedisplay();
    glFlush();
}


void myGLwindow::respondMusa(int whoCalledMe){
        mouseWhere = outBoard;

		if (mouseX>chessBoard::xMargin+chessBoard::xPadding && mouseX<chessBoard::xMargin+chessBoard::xPadding+8*chessBoard::gap && mouseY>chessBoard::yMargin+chessBoard::yPadding && mouseY<chessBoard::yMargin+chessBoard::yPadding+8*chessBoard::gap){		//Apply this conditions when mouseX and mouseY are within the limit of board x, y
			activeGame->selectedX = xMouse(mouseX);												//xMouse returns the gridX of the selectedSquare
			activeGame->selectedY = yMouse(mouseY);												//Idiot, What do you think yMouse will do now?
			activeGame->selectedPos = pos(activeGame->selectedX,activeGame->selectedY);
			mouseWhere = inBoard;
		}else{
			if (whoCalledMe == mouseFunction){
				if (mouseState == GLUT_DOWN){										//mouseState == GLUT_DOWN is added to cancel current move but retain the selection !!110
					activeGame->selectedX = 99;
					activeGame->selectedY = 99;
					activeGame->selectedPos = 99;
					activeGame->currentSituation = sourceNotSelected;
                    activeBoard->shiftX = 0; activeBoard->shiftY = 0;
				}
			}else{
				mouseWhere = outBoard;
				//cout<<"Dragging Out Of board!!"<<endl;
			}
		}

    //What to do after mouse has been clicked on a valid square????
		if (mouseButton == GLUT_LEFT_BUTTON){
			switch (activeGame->currentSituation){
			case sourceNotSelected:
				if (whoCalledMe == mouseFunction && mouseState == GLUT_DOWN){
					if (activeGame->allGotti->BW[activeGame->whoIsAt(activeGame->selectedPos)].color == activeGame->currentTurn){
						activeGame->currentSituation = sourceSelected;
						activeGame->sourcedPos = activeGame->selectedPos;
						activeGame->sourcedPieceIndex = activeGame->whoIsAt(activeGame->sourcedPos);
					}else{
						activeGame->currentSituation = sourceNotSelected;
					}
				}
				break;
			case sourceSelected:

				if (whoCalledMe == mouseFunction && mouseState == GLUT_DOWN){
					if (activeGame->allGotti->BW[activeGame->whoIsAt(activeGame->selectedPos)].color==activeGame->currentTurn){
						activeGame->currentSituation = sourceSelected;
						activeGame->sourcedPos = activeGame->selectedPos;
						activeGame->sourcedPieceIndex = activeGame->whoIsAt(activeGame->sourcedPos);
						//cout<<"selectedPos == "<<selectedPos<<endl;
					}else{
						activeGame->currentSituation = destinationSelected;
						activeGame->destinedPos = activeGame->selectedPos;
						activeGame->destinedPieceIndex = activeGame->whoIsAt(activeGame->sourcedPos);

						if (mouseWhere == inBoard){							//this code is added far after the drag-drop was finalised, so this might show some unpredicted behavior
							activeBoard->shiftX = mouseX - (activeBoard->xMargin + activeBoard->xPadding + activeBoard->gap*x(activeGame->sourcedPos) + activeBoard->gap/2);
							activeBoard->shiftY = mouseY - (activeBoard->yMargin + activeBoard->yPadding + activeBoard->gap*y(activeGame->sourcedPos) + activeBoard->gap/2);
						}
					}
				}


				if (whoCalledMe == motionFunction && mouseState == GLUT_DOWN){
					if(mouseWhere == inBoard){
						activeGame->currentSituation = destinationSelected;
						activeGame->destinedPos = activeGame->selectedPos;
						activeGame->destinedPieceIndex = activeGame->whoIsAt(activeGame->sourcedPos);
					}
				}

				break;
			case destinationSelected:
				if (mouseWhere == inBoard){
					activeBoard->shiftX = mouseX - (activeBoard->xMargin + activeBoard->xPadding + activeBoard->gap*x(activeGame->sourcedPos) + activeBoard->gap/2);
					activeBoard->shiftY = mouseY - (activeBoard->yMargin + activeBoard->yPadding + activeBoard->gap*y(activeGame->sourcedPos) + activeBoard->gap/2);
					activeGame->currentSituation = destinationSelected;
					activeGame->destinedPos = activeGame->selectedPos;
					activeGame->destinedPieceIndex = activeGame->sourcedPos;
					if (mouseState == GLUT_UP){
						activeBoard->shiftX = 0;		activeBoard->shiftY = 0;
						if (activeGame->allGotti->BW[activeGame->whoIsAt(activeGame->selectedPos)].color != activeGame->currentTurn){			//If the destined square is empty or has the opposite colored piece
							activeGame->currentSituation = moveRequested;
						}else{
                            activeGame->currentSituation = sourceSelected;
							activeGame->sourcedPos = activeGame->selectedPos;
							activeGame->sourcedPieceIndex = activeGame->sourcedPos;
							std::cout<<"Never attack your own!"<<std::endl;
						}
					}
				}else{
					if (mouseState == GLUT_UP){
						activeBoard->shiftX = 0;		activeBoard->shiftY = 0;
						activeGame->selectedPos = 999;
						activeGame->currentSituation = sourceSelected;
					}
				}
				break;
			}
		}	// mouseButton == GLUT_LEFT_BUTTON
        glutPostRedisplay();
}
int myGLwindow::xMouse(int mX){
	//For 1 based system i.e. first square taken to be 1,1
	return (mX - (activeBoard->xMargin + activeBoard->xPadding))/activeBoard->gap;//+1;
}
int myGLwindow::yMouse(int mY){
	//For 1 based system i.e. first square taken to be 1,1
	return (mY - (activeBoard->yMargin + activeBoard->yPadding))/activeBoard->gap;//+1;
}
