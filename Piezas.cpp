#include "Piezas.h"
#include <vector>
const int MAXROW = 3;
const int MAXCOL = 4;
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas(){
	board.resize(3);
	for(int row = 0; row < MAXROW; row++)
		board[row].resize(4);	
	turn = X;
	reset();
};
/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset(){
	for(int row = 0; row < MAXROW; row++){
		for(int col = 0; col < MAXCOL; col++){
			board[row][col] = Blank;
		}//forCol
	}//forRow
};
/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column){
	Piece place = turn;
	if(turn == X)
		turn = O;
	else
		turn = X;
	if(column > 3 || column < 0)
		return Invalid;
	if(board[2][column] != Blank)
		return Blank;
	for(int row = 0; row < MAXROW; row++){
		if(pieceAt(row, column) == Blank){
			board[row][column] = place;
			return place;
		}//if
	}//for
	return Invalid;
};
/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column){
	if(row > 2 || column > 3 || row < 0 || column < 0)
		return Invalid;
	else
		return board[row][column];
};
/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState(){
	int countX = 0;
	int countO = 0;
	int tempX = 0;
	int tempO = 0;
	Piece last = Blank;
	for(int rowR = 0; rowR < MAXROW; rowR++){//Checks Rows for Maximum
		tempX = 0;
		tempO = 0;
		for(int colR = 0; colR < MAXCOL; colR++){
			Piece test = pieceAt(rowR, colR);
			if(test == Blank)
				return Invalid;
			else if(test == X){
				if(last == X || last == Blank)
					tempX++;
				else if(last == O && tempX == 0)
					tempX++;
			}else if(test == O){
				if(last == O || last == Blank)
					tempO++;
				else if(last == X && tempO == 0)
					tempO++;
			}//else if
			if(tempX > countX)
				countX = tempX;
			if(tempO > countO)
				countO = tempO;
		}//forCol
	}//forRow	
	last = Blank;
	for(int colC = 0; colC < MAXCOL; colC++){//Checks Columns for Maximum
		tempX = 0;
		tempO = 0;
		for(int rowC = 0; rowC < MAXROW; rowC++){
			Piece test = pieceAt(rowC, colC);
			if(test == Blank)
				return Invalid;
			else if(test == X){
				if(last == X || last == Blank)
					tempX++;
				else if(last == O && tempX == 0)
					tempX++;
			}else if(test == O){
				if(last == O || last == Blank)
					tempO++;
				else if(last == X && tempO == 0)
					tempO++;
			}//else if
			if(tempX > countX)
				countX = tempX;
			if(tempO > countO)
				countO = tempO;
		}//forCol
	}//forRow
	if(countX > countO)
		return X;
	if(countO > countX)
		return O;
	if(countO == countX)
		return Blank;
	return Invalid;
};
