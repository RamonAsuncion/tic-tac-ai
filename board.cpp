#include <iostream>

#include "board.h"

board::board()
{
  init();
}

void board::init()
{
  grid = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, '-'));
}

bool board::make_move(move move, char symbol)
{
  if (is_empty(move)) {
    grid[move.row][move.col] = symbol;
    return true;
  }
  return false;
}

std::vector<std::pair<int, int>> board::possible_moves()
{
  std::vector<std::pair<int, int>> moves;
  for (int row = 0; row < SIZE; ++row) {
    for (int col = 0; col < SIZE; ++col) {
      // return cell that is empty e.g. {{0, 1}, {1,0}...}
      if (grid[row][col] == '-') {
        moves.push_back(std::make_pair(row, col));
      }
    }
  }
  return moves;
}

bool board::is_empty(move move) const
{
  return grid[move.row][move.col] == '-';
}

bool board::is_draw() const
{
  for (int row = 0; row < SIZE; ++row) {
    for (int col = 0; col < SIZE; ++col) {
      if (grid[row][col] == '-') {
        return false;
      }
    }
  }
  return true; // assumes check_winner is false.
}

bool board::check_winner(char player) const
{
  // check cols
  for (int row = 0; row < SIZE; ++row) {
    bool row_win = true;
    for (int col = 0; col < SIZE; ++col) {
      if (grid[row][col] != player) {
        row_win = false;
        break;
      }
    }
    if (row_win) return true;
  }

  // check rows
  for (int col = 0; col < SIZE; ++col) {
    bool col_win = true;
    for (int row = 0; row < SIZE; ++row) {
      if (grid[row][col] != player) {
        col_win = false;
        break;
      }
    }
    if (col_win) return true;
  }

  // check diag
  bool diag_win = true;
  for (int i = 0; i < SIZE; ++i) {
    if (grid[i][i] != player) {
      diag_win = false;
      break;
    }
  }
  if (diag_win) return true;

  // check anti diag
  diag_win = true;
  for (int i = 0; i < SIZE; ++i) {
    if (grid[i][SIZE - 1 - i] != player) {
      diag_win = false;
      break;
    }
  }
  if (diag_win) return true;

  return false;
}

void board::display() const
{
  //   a     b     c
  //      |     |
  //1  -  |  -  |  -
  // _____|_____|_____
  //      |     |
  //2  -  |  -  |  -
  // _____|_____|_____
  //      |     |
  //3  -  |  -  |  -
  //      |     |
  std::cout << "\n    a     b     c\n";
  for (int i = 0; i < SIZE; ++i) {
    std::cout << "       |     |      \n";
    std::cout << (i + 1) << "   " << grid[i][0] << "  |  " << grid[i][1] << "  |  " << grid[i][2] << "\n";
    if (i != SIZE - 1)
      std::cout << "  _____|_____|_____\n";
  }
  std::cout << "       |     |     \n\n";
}

