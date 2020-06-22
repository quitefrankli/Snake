#include "AI.hpp"
#include "Game.hpp"
#include "General.hpp"

extern Game game;

using namespace std;

SnakeAI::SnakeAI() {
    General::randomise(getPosY(), getPosY());
    setID(game.SNAKE_AI_BODY);
}

SnakeAI::~SnakeAI() {
    body.clear();
}

void SnakeAI::changeDirection() {
    int randomValue = rand()%4;
    switch (randomValue) {
        case 0:
            randomValue = game.LEFT;
            break;
        case 1:
            randomValue = game.RIGHT;
            break;
        case 2:
            randomValue = game.UP;
            break;
        case 3:
            randomValue = game.DOWN;
            break;
    }
    bool left, right, up, down;
    left = right = up = down = false;
    
    //USE OPTION BITMASK METHOD
    if ((*game.grid)[getPosY()][getPosX()-1][0] == game.WALL) setDirection(game.RIGHT);//left = true;// && randomValue != game.RIGHT) randomValue = game.UP;
    else if ((*game.grid)[getPosY()][getPosX()+1][0] == game.WALL) setDirection(game.LEFT); //right = true;// && randomValue != game.LEFT) randomValue = game.DOWN;
    else if ((*game.grid)[getPosY()+1][getPosX()][0] == game.WALL) setDirection(game.UP);//up = true;// && randomValue != game.DOWN) randomValue = game.LEFT;
    else if ((*game.grid)[getPosY()-1][getPosX()][0] == game.WALL) setDirection(game.DOWN);//down = true;// && randomValue != game.UP) randomValue = game.RIGHT;
    
//    if (left * right * up * down) { //near border
//        if (left) setDirection(game.RIGHT);
//        else if
//    }
    else if (getDirection() != randomValue * (-1))
        setDirection(randomValue);
}

void SnakeAI::reset() {
    body.clear();
    setPosX(rand() % (game.getBlocksAcross()-2)+1);//1...getBlocksAcross()-2
    setPosY(rand() % (game.getBlocksAcross()-2)+1);
    grow();
}

void SnakeAI::sequence() {
    vector<unique_ptr<Object>>::iterator itBody = body.end();
    vector<unique_ptr<Object>>::iterator itHead = body.begin();
    for (itBody--; itBody != itHead; itBody--) { //start from tail and work to head
        (*itBody)->setPosX((*(itBody-1))->getPosX());
        (*itBody)->setPosY((*(itBody-1))->getPosY());
    }
    
    if (tickCounter == tickChangeDirection) {
        changeDirection();
        tickCounter = 0;
    } else {
        tickCounter++;
    }
    
    switch (getDirection()) {
        case game.LEFT:
            body[0]->setPosX(body[0]->getPosX()-game.getStandardVelocity());
            break;
        case game.RIGHT:
            body[0]->setPosX(body[0]->getPosX()+game.getStandardVelocity());
            break;
        case game.UP:
            body[0]->setPosY(body[0]->getPosY()-game.getStandardVelocity());
            break;
        case game.DOWN:
            body[0]->setPosY(body[0]->getPosY()+game.getStandardVelocity());
            break;
    }
    
    this->setPos((*itHead)->getPosX(), (*itHead)->getPosY()); //syncing head
    game.updateGrid(this);
}

