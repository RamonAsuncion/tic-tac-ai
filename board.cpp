#include <iostream>
#include <cstdlib>

#include "board.h"
#include "constants.h"

board::board()
{
  init();
}

void board::init()
{
  grid = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, EMPTY_CELL));
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
      if (grid[row][col] == EMPTY_CELL) {
        moves.push_back(std::make_pair(row, col));
      }
    }
  }
  return moves;
}

bool board::is_empty(move move) const
{
  return grid[move.row][move.col] == EMPTY_CELL;
}

bool board::is_draw() const
{
  if (check_winner() != EMPTY_CELL) {
    return false;
  }

  // any empty cell remain
  for (int row = 0; row < SIZE; ++row) {
    for (int col = 0; col < SIZE; ++col) {
      if (grid[row][col] == EMPTY_CELL) {
        return false;
      }
    }
  }

  return true;
}

char board::check_winner() const
{
  // check rows
  for (int row = 0; row < SIZE; ++row) {
    if (grid[row][0] != EMPTY_CELL) {
      bool row_win = true;
      for (int col = 0; col < SIZE; ++col) {
        if (grid[row][col] != grid[row][0]) {
          row_win = false;
          break;
        }
      }
      if (row_win) return grid[row][0];
    }
  }

  // check cols
  for (int col = 0; col < SIZE; ++col) {
    if (grid[0][col] != EMPTY_CELL) {
      bool col_win = true;
      for (int row = 1; row < SIZE; ++row) {
        if (grid[row][col] != grid[0][col]) {
          col_win = false;
          break;
        }
      }
      if (col_win) return grid[0][col];
    }
  }

  // check diag
  if (grid[0][0] != EMPTY_CELL) {
    bool diag_win = true;
    for (int i = 1; i < SIZE; ++i) {
      if (grid[i][i] != grid[0][0]) {
        diag_win = false;
        break;
      }
    }
    if (diag_win) return grid[0][0];
  }

  // check anti diag
  if (grid[0][SIZE - 1] != EMPTY_CELL) {
    bool anti_diag_win = true;
    for (int i = 1; i < SIZE; ++i) {
      if (grid[i][SIZE - 1 - i] != grid[0][SIZE - 1]) {
        anti_diag_win = false;
        break;
      }
    }
    if (anti_diag_win) return grid[0][SIZE - 1];
  }

  // no winner
  return EMPTY_CELL;
}

inline void clear_screen()
{
  std::cout << "\033[2J\033[1;1H";
}

void board::display() const
{
  clear_screen(); // TODO: I need to let user know how to use command.
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

