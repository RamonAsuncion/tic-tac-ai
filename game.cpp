#include <cstdlib>
#include <iostream>
#include <string>

#include "constants.h"
#include "game.h"

game::game()
{
  srand(static_cast<unsigned int>(time(0))); // random AI start position
  game_over = false;
  current_player = PLAYER_X;
}

// when I write something like "Xa1" it errors
void game::show_menu()
{
  int choice = 0;

  while (true) {
    std::cout << "Welcome to Tic-Tac-AI!\n";
    std::cout << "1. PvP\n";
    std::cout << "2. PvAI\n";
    std::cout << "3. Quit\n";
    std::cout << "> ";

    std::cin >> choice;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input, please enter a number between 1 and 3.\n";
      continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
      mode = game_mode::PvP;
      break;
    } else if (choice == 2) {
      mode = game_mode::PvAI;
      int diff_choice = 0;
      while (true) {
        std::cout << "Choose difficult of AI:\n";
        std::cout << "1. Dumb AI\n";
        std::cout << "2. Impossible AI\n";
        std::cout << "> ";
        std::cin >> diff_choice;

        if (std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Please enter 1 or 2.\n";
          continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (diff_choice == 1 || diff_choice == 2) {
          break;
        } else {
          std::cout << "Please choose 1 or 2.\n";
        }
      }

      ai_difficulty selected_difficulty =
        (diff_choice == 1) ? ai_difficulty::Dumb : ai_difficulty::Impossible;
      ai_player = ai(selected_difficulty);
      break;
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

    //auto possible_moves = game_board.possible_moves();
    //std::cout << "Possible moves: ";
    //for (const auto& pm : possible_moves) {
    //  std::cout << "{" << pm.row << ", " << pm.col << "} ";
    //}
    //std::cout << "\n";

    if (mode == game_mode::PvP || current_player == PLAYER_X) {
      player_move();
    } else {
      ai_move();
    }

  check_game_over();
  if (!game_over)
    switch_player();
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

    if (!valid_move)
      std::cout << "Invalid move: " << move << "\n";
  }
}

void game::ai_move() {
  position ai_choice = ai_player.get_move(game_board);
  game_board.make_move(ai_choice, current_player);
}

bool game::process_move(const std::string& player_move)
{
  if (player_move.length() != 3) return false;

  // Ob2 Xc2 Ob3 Xa1
  char player = std::toupper(player_move[0]);
  char col = std::tolower(player_move[1]);
  char row = player_move[2];

  if (player != current_player) {
    std::cout << "It's " << current_player << "'s turn!\n";
    return false;
  }

  // if (player != current_player) return false;
  if (col < 'a' || col > 'c') return false;
  if (row < '1' || row > '3') return false;

  position p;
  p.row = row - '1';
  p.col = col - 'a';

  return game_board.make_move(p, player);
}

void game::check_game_over()
{
  char winner = game_board.check_winner();

  if (winner != EMPTY_CELL) {
    game_board.display();
    std::cout << winner << " wins!\n";
    game_over = true;
  } else if (game_board.is_tie()) {  // last move could be a winner
    game_board.display();
    std::cout << "It's a tie!\n";
    game_over = true;
  }
}
