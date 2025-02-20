#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"
#include "player.h"
#include "ai.h"

class game {
public:
  game();
  void init();
private:
  player human_player;
  ai ai_player;
  void switch_player();
  void player_move();
  void ai_move();
};

#endif /* _GAME_H_ */
