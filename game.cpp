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
      std::cout << "Start: " << current_player << ", use command \"Xa1\"!\n";
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

  while (!game_over) {
    game_board.display();

    if (mode == game_mode::PvP || current_player == 'X') {
      player_move();
    } else {
      ai_move();
      continue;
    }
  }
}

void game::switch_player()
{
  current_player = (current_player == 'X') ? 'O' : 'X';
}

void game::player_move()
{
  std::string move;
  bool valid_move = false;

  while (!valid_move) {
    int pvp_player = (current_player == 'X' ? 1 : 2);
    std::cout << "P" << pvp_player << ": ";
    std::getline(std::cin, move);

    valid_move = process_move(move);

    if (valid_move)
      switch_player();
    else
      std::cout << "Invalid move!";
  }
}

// ai.cpp will be used to make a easy / medium / hard difficulty one or maybe one that is just hard
void game::ai_move() {
  // todo: random empty spot (create is_empty function)
}

bool game::process_move(const std::string& move)
{
  if (move.length() != 3) return false;

  // Ob2 Xc2 Ob3 Xa1
  char player = std::toupper(move[0]);
  char col = std::tolower(move[1]);
  char row = move[2];

  if (player != current_player) return false;
  if (col < 'a' || col > 'c') return false;
  if (row < '1' || row > '3') return false;

  int row_idx = row - '1';
  int col_idx = col - 'a';

  if (game_board.is_empty(col_idx, row_idx)) {
    game_board.make_move(col_idx, row_idx, player);
    return true;
  }

  return false;
}

