#include <string>
#include <iostream>

#include "game.h"

game::game()
{
  game_over = false;
  current_player = 'X';
}

void game::show_menu()
{
  int choice = 0;
  while (choice != 1 && choice != 2 && choice != 3) {
    std::cout << "Welcome to Tic-Tac-AI!\n";
    std::cout << "1. PvP\n";
    std::cout << "2. PvAI\n";
    std::cout << "3. Quit\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
      mode = game_mode::PvP;
    } else if (choice == 2) {
      mode = game_mode::PvAI;
    } else if (choice == 3) {
      std::cout << "Exiting...\n";
      exit(0);
    } else {
      std::cout << "Invalid option!\n";
    }
  }
}

void game::run()
{
  show_menu();
  std::string move;
  int pvp_player = 1;
  while (!game_over) {
    game_board.display();

    if (mode == game_mode::PvP || current_player == 'X') {
      // todo: move this (?)
      std::cout << "P" << pvp_player << ": ";
      std::getline(std::cin, move);
      pvp_player = (pvp_player == 1) ? 2 : 1;
    } else {
      ai_move();
      continue;
    }

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

// void game::player_move() { }

// ai.cpp will be used to make a easy / medium / hard difficulty one or maybe one that is just hard
void game::ai_move() {
  // todo: random empty spot (create is_empty function)
}

bool game::process_move(const std::string& move)
{
  if (move.length() != 3) return false;

  // Ob2 Xc2 Ob3 Xa1
  char player = move[0];
  char col = move[1];
  char row = move[2];

  if (player != current_player) return false;
  if (col < 'a' || col > 'c') return false;
  if (row < '1' || row > '3') return false;

  int row_idx = row - '1';
  int col_idx = col - 'a';

  game_board.make_move(col_idx, row_idx, player);

  return true;
}

