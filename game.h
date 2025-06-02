#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"
#include "player.h"
#include "ai.h"

enum class game_mode
{
  PvP,
  PvAI
};

class game
{
public:
  game();
  void run();
  bool is_draw() const;
  bool check_winner() const;
private:
  game_mode mode;
  board game_board;
  char current_player;
  player human_player;
  ai ai_player;
  bool game_over;
  void switch_player();
  void player_move();
  void ai_move();
  bool process_move(const std::string& move);
  void show_menu();
  void check_game_over();
};

#endif /* _GAME_H_ */
