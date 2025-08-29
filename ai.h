#ifndef _AI_H_
#define _AI_H_

#include <string>
#include <vector>

#include "board.h"

class board;

enum class ai_difficulty {
  Dumb,
  Impossible
};

class ai
{
public:
  ai(ai_difficulty level = ai_difficulty::Impossible);
  position get_move(const board& current_board);
private:
  ai_difficulty difficulty;
  static int minimax(board& current_board, int depth, bool is_maximizing);
  static position find_best_move(const board& current_board);
};

#endif /* _AI_H_ */
