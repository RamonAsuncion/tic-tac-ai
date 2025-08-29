#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <utility>

struct position {
  int row;
  int col;

  position() = default;
  position(int r, int c) : row(r), col(c) {}
  position(std::pair<int, int> p) : row(p.first), col(p.second) {}
};

class board
{
public:
  board();
  void init();
  bool make_move(position pos, char symbol);
  bool is_empty(position pos) const;
  bool is_tie() const;
  char check_winner() const;
  void display() const;
  std::vector<position> possible_moves() const;

private:
  std::vector<std::vector<char>> grid;
};

#endif /* _BOARD_H_ */

