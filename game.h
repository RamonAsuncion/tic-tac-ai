#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"
#include "player.h"
#include "ai.h"

class game
{
public:
  game();
  void run();
private:
  board game_board;
  char current_player;
  player human_player;
  ai ai_player;
  bool game_over;
  void switch_player();
  void player_move();
  void ai_move();
  bool process_move(const std::string& move);
};

#endif /* _GAME_H_ */
