#include "game.h"
#include <iostream>

gameMode game::currentGameMode;
situation game::currentSituation = sourceNotSelected;
int game::selectedPos=99, game::sourcedPos=99, game::destinedPos=99, game::selectedX=99, game::selectedY=99;
int game::sourcedPieceIndex = 32, game::destinedPieceIndex;
pieceMove game::lastMove;
pieceColor game::currentTurn=whiteWalker;
possibleMovesSet game::currentPossibleSet;

gottiSet *game::allGotti;

game::game(int gameLevel, gameMode vsWho){									//Constructor
    gameLevel = gameLevel;
    currentGameMode = vsWho;
}


void game::start(gameMode mode){
    currentGameMode = mode;
    currentTurn = white;
}

void game::respondRequestedMove(){
    std::cout<<"current turn of"<<currentTurn<<std::endl;
    if (whatIsThisMove() >= legalMove){
        allGotti->BW[game::whoIsAt(destinedPos)].capture();					//if there is something in the destined square then, make it whiteWalker :d
        allGotti->BW[game::whoIsAt(sourcedPos)].changeTo(destinedPos);
        allGotti->BW[game::whoIsAt(destinedPos)].hasMovedYet = true;
        lastMove = pieceMove(sourcedPos, destinedPos, whatIsThisMove());
        std::cout<<"Last move was a --> "<<lastMove.thisMove<<std::endl;
        if (currentTurn == white){
            currentTurn = black;
            std::cout<<"Now Black's Turn."<<std::endl;
        }else{
            std::cout<<"Now White's Turn."<<std::endl;
            currentTurn = white;
        }
        currentSituation = sourceNotSelected;
    }else{
        std::cout<<"Illegal Move"<<std::endl;
        currentSituation = sourceSelected;
    }
}

moveType game::whatIsThisMove(){
    //firstCheck... if the movetempGotti = allGotti leaves own king on Check
    moveType tempThisMove = illegalMove;
    for (int i=0; i<currentPossibleSet.possibleMovesCount;i++){
        if (currentPossibleSet.possibleMoves[i].fromWhere == sourcedPos && currentPossibleSet.possibleMoves[i].toWhere == destinedPos){
             tempThisMove = currentPossibleSet.possibleMoves[i].thisMove;
            break;
        }
    }
    return tempThisMove;
}
int game::whoIsAt(int sx, int sy){
    int i;
    for (i=0; i<32; i++){
        if (allGotti->BW[i].x()==sx && allGotti->BW[i].y()==sy && allGotti->BW[i].state==alive)
            return i;
    }
    return 32;
}
int game::whoIsAt(int sPos){
	//return the whoIsAt by calling the overloaded function
	return whoIsAt(x(sPos), y(sPos));
}
void possibleMovesSet::refresh(int srcPos){
	this->sPos = srcPos;
	this->possibleMovesCount=0;
	this->sPiece = game::allGotti->BW[game::whoIsAt(srcPos)];
	this->tempThisMove = illegalMove;

}
void possibleMovesSet::listOut(){									//Adds moves to possibleMovesSet of the sPiece (parameterised in ::refresh())
	switch (sPiece.whoAmI){
	case pawn:
		getPawnMoves();
	break;
	case knight:
		getKnightMoves(game::sourcedPos, game::allGotti, game::currentTurn);
	break;
	case rook:
		getRookMoves(game::sourcedPos, game::allGotti, game::currentTurn);
	break;
	case bishop:
		getBishopMoves();
	break;
	case queen:
		getQueenMoves();
	break;
	case king:
		getKingMoves();
	break;
	}
}

void possibleMovesSet::getQueenMoves(){
	this->getRookMoves(game::selectedPos, game::allGotti, game::currentTurn);
	this->getBishopMoves();
}
void possibleMovesSet::getPawnMoves(){
	direction=1;
	if (sPiece.color == black){
		direction =-1;
	}
	oneStepForward = pos(x(sPos),y(sPos)+1*direction);
	oneStepForwardPiece = game::allGotti->BW[game::whoIsAt(oneStepForward)];
	if (oneStepForwardPiece.color == whiteWalker){
		tempThisMove = legalMove;
		if ((sPiece.color == white && y(oneStepForward) == 7) || (sPiece.color == black && y(oneStepForward) == 0)){
			tempThisMove = promotion;
		}
		this->addPossibleMove(sPos,oneStepForward, tempThisMove);			//if pawn then one step front
	}


	if (sPiece.hasMovedYet == false && oneStepForwardPiece.color == whiteWalker){
		twoStepsForward = pos(x(sPos),y(sPos)+2*direction);
		twoStepsForwardPiece = game::allGotti->BW[game::whoIsAt(twoStepsForward)];
		if (twoStepsForwardPiece.color == whiteWalker){
			this->addPossibleMove(sPos,twoStepsForward, legalMove);			//if pawn & not moved, then two steps
		}
	}

	if (sPiece.x()>0){														//checking if there is something to capture in left diagonal
		leftDiagonalPos = pos(sPiece.x()-1, sPiece.y()+1*direction);
		leftDiagonalPiece = game::allGotti->BW[game::whoIsAt(leftDiagonalPos)];
		if (leftDiagonalPiece.color == 1 - sPiece.color){
			tempThisMove = capture;
			if ((sPiece.color == white && y(oneStepForward) == 7) || (sPiece.color == black && y(oneStepForward) == 0)){
				tempThisMove = promotion;
			}
			//cout<<"There is an opponent in leftDiagonalPos"<<endl;
			this->addPossibleMove(sPos,leftDiagonalPos, tempThisMove);
		}

		//checking the possibility of En passant capture towards left
		leftPos = pos(sPiece.x()-1, sPiece.y());
		leftPiece = game::allGotti->BW[game::whoIsAt(leftPos)];
		if (leftPiece.color == 1 - sPiece.color){
			if (game::lastMove.fromWhere == pos(sPiece.x()-1,sPiece.y()+2*direction) && game::lastMove.toWhere == leftPos ){
				this->addPossibleMove(sPos, leftDiagonalPos, enPassant);			//enPassant capture occurs in left diagonal
				//cout<<"enPassant!"<<endl;
			}
		}
	}
	if (sPiece.x()<7){
		rightDiagonalPos = pos(sPiece.x()+1, sPiece.y()+1*direction);
		rightDiagonalPiece = game::allGotti->BW[game::whoIsAt(rightDiagonalPos)];
		if (rightDiagonalPiece.color == 1 - sPiece.color){
			tempThisMove = capture;
			if ((sPiece.color == white && y(oneStepForward) == 7) || (sPiece.color == black && y(oneStepForward) == 0)){
				tempThisMove = promotion;
			}
			//cout<<"There is an opponent in rightDiagonalPos"<<endl;
			this->addPossibleMove(sPos,rightDiagonalPos, tempThisMove);
		}

		//En passant move towards right
		rightPos = pos(sPiece.x()+1, sPiece.y());
		rightPiece = game::allGotti->BW[game::whoIsAt(rightPos)];
		if (rightPiece.color == 1 - sPiece.color){
			if (game::lastMove.fromWhere == pos(sPiece.x()+1,sPiece.y()+2*direction) && game::lastMove.toWhere == rightPos ){
				this->addPossibleMove(sPos, rightDiagonalPos, enPassant);			//enPassant capture occurs in right diagonal
				//cout<<"En passant re ni ta"<<endl;
			}
		}

	}
}

void possibleMovesSet::getRookMoves(int tempS, gottiSet* tempGotti, pieceColor tempColor){
	tempPos = sPos;
	while(1) {
		if (x(tempPos)>0){
			tempPos = pos(x(tempPos) - 1,y(tempPos));
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)

	}

	tempPos = sPos;
	while(1) {
		if (x(tempPos)<7){
			tempPos = pos(x(tempPos) + 1,y(tempPos));
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)

	}

	tempPos = sPos;
	while(1) {
		if (y(tempPos)<7){
			tempPos = pos(x(tempPos),y(tempPos) + 1);
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)

	}

	tempPos = sPos;
	while(1) {
		if (y(tempPos)>0){
			tempPos = pos(x(tempPos),y(tempPos) - 1);
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)

	}
}
void possibleMovesSet::getKingMoves(){
	for (int i = (x(sPos)-1>0?x(sPos)-1:0); i<= (x(sPos)+1<7?x(sPos)+1:7); ++i){
		for (int j = (y(sPos)-1>0?y(sPos)-1:0); j<= (y(sPos)+1<7?y(sPos)+1:7); ++j){
			if (sPos == pos(i,j)){
				continue;		//can't move to the same location yar
			}
			tempPos = pos(i,j);
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				continue;
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);
			}
		}
	}
}

void possibleMovesSet::getKnightMoves(int tempS, gottiSet* tempGotti, pieceColor tempColor){
	for (int i = (x(tempS)-2>0?x(tempS)-2:0); i<= (x(tempS)+2<7?x(tempS)+2:7); ++i){
		for (int j = (y(tempS)-2>0?y(tempS)-2:0); j<= (y(tempS)+2<7?y(tempS)+2:7); ++j){
			if ((tempS-pos(i,j))%9 == 0 || (tempS-pos(i,j))%7 == 0 || y(tempS)==j || x(tempS) == i){
				// nearest squares that are not on y=x +c diagonal or y=-x +c diagonal or on same rank or on same file.......
				continue;
			}
			tempPos = pos(i,j);
			tempPiece = tempGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				continue;
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(tempS, tempPos, capture);
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(tempS, tempPos, legalMove);
			}
		}
	}
}

void possibleMovesSet::getBishopMoves(){
	tempPos = sPos;
	while(1) {
		if (x(tempPos)>0 && y(tempPos)>0){
			tempPos = pos(x(tempPos) - 1, y(tempPos) - 1);
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			} else	if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)

	}
	tempPos = sPos;
	while(1) {
		if (x(tempPos)>0 && y(tempPos)<7){
			tempPos = pos(x(tempPos) - 1, y(tempPos) + 1);
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)

	}
	tempPos = sPos;
	while(1) {
		if (x(tempPos)<7 && y(tempPos)>0){
			tempPos = pos(x(tempPos) + 1, y(tempPos) - 1);
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)

	}
	tempPos = sPos;
	while(1) {
		if (x(tempPos)<7 && y(tempPos)<7){
			tempPos = pos(x(tempPos) + 1, y(tempPos) + 1);
			tempPiece = game::allGotti->BW[game::whoIsAt(tempPos)];
			if (tempPiece.color == sPiece.color){
				break;		//Can't go further if same colored piece is found
			}else if (tempPiece.color == 1 - sPiece.color){
				this->addPossibleMove(sPos, tempPos, capture);
				break;		//Can't go further if opponent's piece is found
			}else if (tempPiece.color == whiteWalker){
				this->addPossibleMove(sPos, tempPos, legalMove);	//go further if emptysquare
			}
		}
		else
			break;		//bring out from while(1)
	}
}

void possibleMovesSet::addPossibleMove(int sPos, int dPos, moveType mType){
	possibleMoves[possibleMovesCount].fromWhere = sPos;
	possibleMoves[possibleMovesCount].toWhere = dPos;
	possibleMoves[possibleMovesCount].thisMove = mType;
	possibleMovesCount++;
}


void possibleMovesSet::normalize(){
    for (int i=0; i<possibleMovesCount; i++){
        if (doesThisLeaveCheck(possibleMoves[i].fromWhere, possibleMoves[i].toWhere,*game::allGotti, game::currentTurn)){
            possibleMoves[i].thisMove = illegalMove;       //ahileko lagi yetti matra garau na ta
        }
    }
}


bool possibleMovesSet::doesThisLeaveCheck(int tempS, int tempD, gottiSet tempGotti, pieceColor tempColor){




    return false;
}
