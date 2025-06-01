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

void board::make_move(int col, int row, char symbol)
{
  grid[row][col] = symbol;
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

