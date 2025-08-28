#include "ai.h"
#include "game.h"
#include "board.h"

std::string ai::get_ai_move()
{
  return "";
}

int ai::minimax(const board& board, int depth, bool is_ai)
{
  if (is_game_over())
    return is_ai ? -10 : 10;

  if (depth == 9)
    return 0;

  int best_score = is_ai ? -9999 : 9999;

  return 0;
}
