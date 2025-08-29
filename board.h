#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

struct move {
  int col, row;
};

class board
{
public:
  board();
  void init();
  bool make_move(move move, char symbol);
  bool is_empty(move move) const;
  bool is_draw() const;
  char check_winner() const;
  void display() const;
  std::vector<std::pair<int, int>> possible_moves();
private:
  std::vector<std::vector<char>> grid;
};

#endif /* _BOARD_H_ */
