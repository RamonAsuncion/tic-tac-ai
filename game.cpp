#include <string>
#include <iostream>

#include "game.h"

game::game()
{
  game_over = false;
}

void game::run()
{
  // todo: menu to do pvp or pvai
  std::string move;
  while (!game_over) {
    game_board.display();
    std::cout << "Move: ";
    std::getline(std::cin, move);
    if (process_move(move))
      switch_player();
    else
      std::cout << "Invalid move!";
  }
}

void game::switch_player()
{
  current_player = (current_player == 'X') ? 'O' : 'X';
}

void game::player_move() { }

void game::ai_move() { }

bool game::process_move(const std::string& move)
{
  if (move.length() != 3) return false;

  // Ob2 Xc2 Ob3 Xa1
  char player = move[0];
  char col = move[1];
  char row = move[2];

  printf("%c%c%c\n", move[0], move[1], move[2]);

  // if (player != current_player) return false;
  if (col < 'a' || col > 'c') return false;
  if (row < '1' || row > '3') return false;

  int row_idx = row - '1';
  int col_idx = col - 'a';

  game_board.make_move(col_idx, row_idx, player);

  return true;
}

