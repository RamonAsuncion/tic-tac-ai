#include <cstdlib>
#include <iostream>
#include <string>

#include "constants.h"
#include "game.h"

game::game()
{
  srand(time(0)); // random AI start position
  game_over = false;
  current_player = PLAYER_X;
}

void game::show_menu()
{
  int choice = 0;
  while (choice != 1 && choice != 2 && choice != 3) {
    std::cout << "Welcome to Tic-Tac-AI!\n";
    std::cout << "1. PvP\n";
    std::cout << "2. PvAI\n";
    std::cout << "3. Quit\n";
    std::cout << "> ";
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
      // std::cout << "Player 1: " << current_player << " use command 'Xa1'!\n";
      mode = game_mode::PvP;
    } else if (choice == 2) {
      mode = game_mode::PvAI;
    } else if (choice == 3) {
      std::cout << "Exiting...\n";
      exit(0);
    } else {
      std::cout << "Invalid option: " << choice << ", choose a # between 1-3.\n";
    }
  }
}

void game::run()
{
  show_menu();

  while (!game_over) {
    game_board.display();

    auto possible_moves = game_board.possible_moves();
    std::cout << "Possible moves: ";
    for (const auto& pm : possible_moves) {
      std::cout << "{" << pm.first << ", " << pm.second << "} ";
    }
    std::cout << "\n";

    if (mode == game_mode::PvP || current_player == PLAYER_X) {
      player_move();
    } else {
      ai_move();
      continue;
    }
  }
}

void game::switch_player()
{
  current_player = (current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

void game::player_move()
{
  std::string move;
  bool valid_move = false;

  while (!valid_move) {
    int pvp_player = (current_player == PLAYER_X ? 1 : 2);
    std::cout << "P" << pvp_player << ": ";
    std::getline(std::cin, move);

    valid_move = process_move(move);

    if (valid_move) {
      check_game_over();
      if (!game_over)
        switch_player();
    }
    else {
      std::cout << "Invalid move: " << move << "\n";
    }
  }
}

void game::ai_move() {
  std::cout << "Dumb AI:\n";
  bool valid_move = false;

  move m;
  while (!valid_move) {
    m.col = rand() % 3;
    m.row = rand() % 3;

    valid_move = game_board.make_move(m, current_player);
  }

  check_game_over();
  if (!game_over)
    switch_player();
}

bool game::process_move(const std::string& player_move)
{
  if (player_move.length() != 3) return false;

  // Ob2 Xc2 Ob3 Xa1
  char player = std::toupper(player_move[0]);
  char col = std::tolower(player_move[1]);
  char row = player_move[2];


  // fixme size can change (c / 3)
  if (player != current_player) return false;
  if (col < 'a' || col > 'c') return false;
  if (row < '1' || row > '3') return false;

  move m;
  m.row = row - '1';
  m.col = col - 'a';

  return game_board.make_move(m, player);
}

void game::check_game_over()
{
  char winner = game_board.check_winner();
  game_board.display();

  if (winner != EMPTY_CELL) {
    std::cout << winner << " wins!\n";
    game_over = true;
  } else if (game_board.is_draw()) {  // last move could be a winner
    std::cout << "It's a draw!\n";
    game_over = true;
  }
}
