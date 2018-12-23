/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.c
 * Author:			P. Bauer
 * Due Date:		November 03, 2010
 * ----------------------------------------------------------
 * Description:
 * Implementation of basic chess functions.
 * ----------------------------------------------------------
 */

#include <stdio.h>
#include "chess.h"
#include "general.h"

bool is_square_ok(File file, Rank rank)
{
  return (file <= 'h') && (file >= 'a') && (rank <= 8) && (rank > 0);
}

int nr(Rank rank)
{
  return rank;
}

int nf(File file)
{
  return file;
}

bool is_move_from_base_line(enum PieceColor color, Rank rank)
{
  if (color == White)
  {
    if (rank == 1)
    {
      return false;
    }
    return true;
  }
  else
  {
    if (rank == 8)
    {
      return false;
    }
    return true;
  }
}

bool is_piece(struct ChessPiece pc, enum PieceColor color, enum PieceType type)
{
  return (pc.color == color) && (pc.type == type);
}

void init_chess_board(ChessBoard chess_board)
{

  for (int n = 1; n <= 8; n++)
  {
    for (int b = 1; b <= 8; b++)
    {
      chess_board[n][b].is_occupied = false;
      chess_board[n][b].piece.type = NoPiece;
    }
  }
}

struct ChessSquare *get_square(ChessBoard chess_board, File file, Rank rank)
{
  int r = rank;
  char f = file;

  if (is_square_ok(file, rank))
  {
    return &chess_board[r - 1][f - 'a'];
  }

  return 0;
}

bool is_square_occupied(ChessBoard chess_board, File file, Rank rank)
{
  return chess_board[rank - 1][file - 'a'].is_occupied;
}

bool add_piece(ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece)
{
  if (chess_board[rank - 1][file - 'a'].is_occupied == false && is_square_ok(file, rank) == true)
  {
    chess_board[rank - 1][file - 'a'].is_occupied = true;
    chess_board[rank - 1][file - 'a'].piece = piece;
    return true;
  }
  return false;
}

struct ChessPiece get_piece(ChessBoard chess_board, File file, Rank rank)
{
  if (!is_square_ok(file, rank))
  {
    chess_board[rank - 1][file - 'a'].piece.type = NoPiece;
    return chess_board[rank - 1][file - 'a'].piece;
  }
  return chess_board[rank - 1][file - 'a'].piece;
}

void setup_chess_board(ChessBoard chess_board)
{
  init_chess_board(chess_board);
  
  for (char x = 'a'; x <= 'h'; x++)
  {
    add_piece(chess_board, x, 2, {White, Pawn});
    add_piece(chess_board, x, 7, {Black, Pawn});
  }

  add_piece(chess_board, 'a', 1, {White, Rook});
  add_piece(chess_board, 'h', 1, {White, Rook});
  add_piece(chess_board, 'b', 1, {White, Knight});
  add_piece(chess_board, 'g', 1, {White, Knight});
  add_piece(chess_board, 'c', 1, {White, Bishop});
  add_piece(chess_board, 'f', 1, {White, Bishop});
  add_piece(chess_board, 'd', 1, {White, Queen});
  add_piece(chess_board, 'e', 1, {White, King});
  add_piece(chess_board, 'a', 8, {Black, Rook});
  add_piece(chess_board, 'h', 8, {Black, Rook});
  add_piece(chess_board, 'b', 8, {Black, Knight});
  add_piece(chess_board, 'g', 8, {Black, Knight});
  add_piece(chess_board, 'c', 8, {Black, Bishop});
  add_piece(chess_board, 'f', 8, {Black, Bishop});
  add_piece(chess_board, 'd', 8, {Black, Queen});
  add_piece(chess_board, 'e', 8, {Black, King});
}

bool remove_piece(ChessBoard chess_board, File file, Rank rank)
{
  if (is_square_occupied(chess_board, file, rank) == true)
  {
    chess_board[file - 'a'][rank - 1] = {0};
    return true;
  }

  return false;
}

bool squares_share_file(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  if (is_square_ok(s1_f, s1_r) && is_square_ok(s2_f, s2_r))
  {
    return s1_f == s2_f;
  }

  return false;
}

bool squares_share_rank(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  if (is_square_ok(s1_f, s1_r) && is_square_ok(s2_f, s2_r))
  {
    return s1_r == s2_r;
  }

  return false;
}

bool squares_share_diagonal(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  if (is_square_ok(s1_f, s1_r) && is_square_ok(s2_f, s2_r))
  {
    int r = s1_r - s2_r;
    int f = s1_f - s2_f;

    return r != 0 && (f / r == 1 || f / r == -1);
  }
  return false;
}

bool squares_share_knights_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  int file = s1_f - s2_f;
  int rank = s1_r - s2_r;

  if (is_square_ok(s1_f, s1_r) && is_square_ok(s2_f, s2_r))
  {
    file = s1_f - s2_f;
    rank = s1_r - s2_r;

    if (rank != 0)
    {
      return (file / rank == 1 / 2) || (file / rank == -1 / 2) || (file / rank == 2) || (file / rank == -2);
    }
  }
  return false;
}

bool squares_share_pawns_move(enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  if (is_square_ok(s1_f, s1_r) && is_square_ok(s2_f, s2_r))
  {
    if (s1_r == s2_r - 1 || s2_r == s1_r - 1 || s2_r == s1_r)
    {
      return true;
    }
  }

  return false;
}

bool squares_share_queens_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  return squares_share_diagonal(s1_f, s1_r, s2_f, s2_r) || squares_share_file(s1_f, s1_r, s2_f, s2_r) || squares_share_rank(s1_f, s1_r, s2_f, s2_r);
}

bool squares_share_kings_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  int rank;
  int file;

  rank = s1_r - s2_r;
  file = s1_f - s2_f;

  return (file <= 1) && (file >= -1) && (rank >= -1) && (rank <= 1) && (rank != 0 || file != 0);
}
