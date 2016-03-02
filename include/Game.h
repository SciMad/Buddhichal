#include "Gotti.h"

enum gameState {notStarted=0, running, paused, over};
enum situation {sourceNotSelected=0, sourceSelected, destinationSelected, moveRequested};
enum gameMode {vsHuman=0, vsComputer};

enum gameColorsIndex {red=0, yellow, green, brown, purple,lightPurple};

const float gameColor[15][4] = {	{0.7, 0.0, 0.1, 0.5},	//for Red
								{0.9, 0.8, 0.0, 0.5},	//For yellow
								{0.2, 0.5, 0.2, 0.5},	//for green color
								{0.5, 0.0, 0.2, 0.5},	//For brown
								{0.5, 0.0, 0.5, 0.5}, 	//For ....
								{0.5, 0.4, 0.6, 0.5}, 	//lightPurple
								{0.8, 0.0, 0.0, 0.5},
								{0.2, 0.5, 0.2, 0.5}, 	//for green //for legal move color (2)
								{0.8, 0.2, 0.2, 0.5},	//for reddish color //for capture
								{0.6, 0.0, 0.0, 0.5},	//for enPassant color deepPurple
								{0.2, 0.3, 0.6, 0.5},	//for castling	// blue
								{9.0, 0.9, 0.1, 0.5},	//for promotion // yellowish
							};

class possibleMovesSet{
public:
	//void possibleMovesSet();
	void listOut(), getPawnMoves(), getQueenMoves(), getBishopMoves(), getKingMoves();
	void refresh(int);
	void addPossibleMove(int, int, moveType);
	void normalize();
	int possibleMovesCount;				//0 when no moves are possible...(i.e. 1 based count) but the possibleMoves[] starts from '0', i.e. 0 based	count
	int sPos;
	piece sPiece;
	pieceMove possibleMoves[27];

    void getRookMoves(int, gottiSet*, pieceColor);
    void getKnightMoves(int, gottiSet*, pieceColor);


    static bool doesThisLeaveCheck(int, int, gottiSet, pieceColor);

protected:
	moveType tempThisMove;
	piece tempPiece, oneStepForwardPiece, twoStepsForwardPiece, leftDiagonalPiece, rightDiagonalPiece, leftPiece, rightPiece;
	int direction, tempPos, oneStepForward, twoStepsForward, leftDiagonalPos, rightDiagonalPos, leftPos, rightPos;

};


class game{
public:

	game(int, gameMode);

    static gottiSet* allGotti;

    static int gameLevel;															// Search Depth
	static gameMode currentGameMode;															//single player or 2 players
    static int selectedX, selectedY, selectedPos;
	static int sourcedPos,destinedPos;												//To move from where to where??
	static int sourcedPieceIndex, destinedPieceIndex;								//index (0-32) of the piece to be moved or to be captured
	static situation currentSituation;
    static pieceMove lastMove;
    static pieceColor currentTurn;
    static possibleMovesSet currentPossibleSet;

    static int whoIsAt(int), whoIsAt(int, int);		//PrototypeDeclaration for immediate use inside class 'move', 'possibleMovesSet', 'game' & the returned integer is the index of BW[]
	static void start(gameMode);
	static void respondRequestedMove();

	//move possibleMoves[27];													//Max possible moves for any step is 27
	//move lastMove;
protected:
    static moveType whatIsThisMove();
};
