#ifndef GAMEELEMENTS_H_INCLUDED
#define GAMEELEMENTS_H_INCLUDED

#include "Utility/Maths.h"

enum moveType {illegalMove=6, legalMove, capture, enPassant, castling, promotion};

enum pieceName {rook=0, pawn, knight, bishop, king, queen, nothing};
enum pieceState {dead = false, alive = true};
enum pieceColor {white=0, black, whiteWalker};

class piece {
public:
    piece();
    pieceName whoAmI;
    int position;
    pieceColor color;
    pieceState state;
    bool hasMovedYet;

    int x();
    int y();



    void capture();
    void changeTo(int);
    void changeTo(pieceName, int);
    void changeTo(pieceColor, pieceName, int);

    static float pieceBorderWidth;
};


class pieceMove {
public:
    pieceMove();
    pieceMove(int, int, moveType);
    int fromWhere;
    int toWhere;
    moveType thisMove;
};


#endif // GAMEELEMENTS_H_INCLUDED
