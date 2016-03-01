#include "../header/gotti.h"

float gottiSet::pieceBorderWidth = 1.0;
piece gottiSet::BW[33];

void gottiSet::initPieces(){
    int i;

    BW[0].changeTo(rook,0);
    BW[1].changeTo(knight,1);
    BW[2].changeTo(bishop,2);
    BW[4].changeTo(queen,3);
    BW[3].changeTo(king,4);
    BW[5].changeTo(bishop,5);
    BW[6].changeTo(knight,6);
    BW[7].changeTo(rook,7);
    for(i=8; i<16; i++){
        BW[i].changeTo(i);
    }

    for(i=16; i<24; i++){
        BW[i].changeTo(black, pawn,i+32);
    }
    BW[24].changeTo(black, rook, 56);
    BW[25].changeTo(black, knight, 57);
    BW[26].changeTo(black, bishop, 58);
    BW[27].changeTo(black, queen, 59);
    BW[28].changeTo(black, king, 60);
    BW[29].changeTo(black, bishop, 61);
    BW[30].changeTo(black, knight, 62);
    BW[31].changeTo(black, rook, 63);

    BW[32].state = dead; BW[32].position = 99; BW[32].color = whiteWalker;
}
