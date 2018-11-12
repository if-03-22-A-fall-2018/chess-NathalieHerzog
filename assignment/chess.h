/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.h
 * Author:			P. Bauer
 * Due Date:		October 15, 2014
 * ----------------------------------------------------------
 * Description:
 * Basic chess functions.
 * ----------------------------------------------------------
 */
 #ifndef ___CHESS_H
 #define ___CHESS_H

typedef struct ChessSquare ChessBoard[8][8];

static struct ChessPiece white_pawn = {struct PieceColor, struct PieceType};
static struct ChessPiece white_king = {struct PieceColor, struct PieceType};
static struct ChessPiece white_pawn = {struct PieceColor, struct PieceType};
static struct ChessPiece white_rook = {struct PieceColor, struct PieceType};
static struct ChessPiece white_knight = {struct PieceColor, struct PieceType};
static struct ChessPiece white_bishop = {struct PieceColor, struct PieceType};
static struct ChessPiece white_queen = {struct PieceColor, struct PieceType};

static struct ChessPiece black_pawn = {struct PieceColor, struct PieceType};
static struct ChessPiece black_rook = {struct PieceColor, struct PieceType};
static struct ChessPiece black_knight = {struct PieceColor, struct PieceType};
static struct ChessPiece black_bishop = {struct PieceColor, struct PieceType};
static struct ChessPiece black_queen = {struct PieceColor, struct PieceType};
static struct ChessPiece black_king = {struct PieceColor, struct PieceType};


#endif
