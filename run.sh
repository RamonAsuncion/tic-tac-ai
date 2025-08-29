rm main 2> /dev/null
g++ -std=c++17 -Wall -Wextra -g -Og main.cpp board.cpp game.cpp ai.cpp -o main
./main
