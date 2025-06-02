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

bool board::make_move(int col, int row, char symbol)
{
  if (is_empty(col, row)) {
    grid[row][col] = symbol;
    return true;
  }
  return false;
}

bool board::is_empty(int col, int row)
{
  return grid[row][col] == '-';
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

bool board::check_winner(char player)
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

