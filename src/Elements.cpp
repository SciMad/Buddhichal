#include "Elements.h"

float piece::pieceBorderWidth = 1.0;
piece::piece(){				        //Constructor Declaration
    this->state = alive;
    this->whoAmI = pawn;            //pawn, rook, and so on also represent the index in the array in gotti.h
    this->position = 99;
    this->color = white;	        //whiteWalker??
    this->hasMovedYet = false;
};

int piece::x(){
    return ::x(this->position);					//returns the x(position) of outermost scope
}

int piece::y(){
    return ::y(this->position);					//returns the y(position) of outermost scope
}
void piece::capture(){
    this->state = dead; this->position = 99; this->color = whiteWalker;
}
void piece::changeTo(int newPosition){
    this->position = newPosition;
}
void piece::changeTo(pieceName newPost, int newPosition){
    this->whoAmI = newPost;
    this->position = newPosition;
}
void piece::changeTo(pieceColor newColor, pieceName newPost, int newPosition){
    this->whoAmI = newPost;
    this->position = newPosition;
    this->color = newColor;
}



pieceMove::pieceMove(int sPos, int dPos, moveType mType){
    this->fromWhere = sPos;
    this->toWhere = dPos;
    this->thisMove = mType;
    //this->thisMove = find From Function what type of move this is.
}

pieceMove::pieceMove(){
}

