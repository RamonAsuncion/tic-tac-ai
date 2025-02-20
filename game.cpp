#include <string>
#include <vector>
#include <iostream>

#include "game.h"

// for now it's going to be terminal input
// https://codegolf.stackexchange.com/questions/95629/print-this-tic-tac-toe-board

//   a     b     c
//      |     |
//1  -  |  -  |  -
// _____|_____|_____
//      |     |
//2  -  |  -  |  -
// _____|_____|_____
//      |     |
//3  -  |  -  |  -
//      |     |
// Ob2 Xc2 Ob3 Xa1
//First, the token that's going
//Next, the letter of the column it is moving on
//Last, the number of the row it is moving on
// I'll offer clicking later when I do the actual UI with SDL2.


void game::init() { }

void game::switch_player() { }

void game::player_move() { }

void game::ai_move() { }

int main(void)
{
  // Ob2 Xc2 Ob3 Xa1
  // but i don't think this is what the input is taking probably X or O
  return 0;
}

