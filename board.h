#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

class board
{
public:
  board();
  void init();
  void make_move(int col, int row, char symbol);
  bool is_empty(int col, int row);
  void display() const;
private:
  static const int SIZE = 3;
  std::vector<std::vector<char>> grid;
};

#endif /* _BOARD_H_ */
