#include <random>

#include "General.hpp"
#include "Game.hpp"

using namespace std;

extern Game game;
extern mt19937 randGen;

void General::randomise(double &x, double &y) {
    static uniform_int_distribution<> disX(1, game.getBlocksAcross() - 2);
    static uniform_int_distribution<> disY(1, game.getBlocksDown() - 2);
    x = disX(randGen);
    y = disY(randGen);
}
