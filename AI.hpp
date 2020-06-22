#ifndef AI_hpp
#define AI_hpp

#include "Objects.hpp"

// This class adds other AI snakes that competes with the player
class SnakeAI: public Snake {
private:
    const int tickChangeDirection = 0;
    int tickCounter = 0;
public:
    SnakeAI();
    ~SnakeAI();
    
    void resetTickCounter() { tickCounter = 0; }
    void incrementTickCountet() { tickCounter++; }
    int getTickCOunter() { return tickCounter; }
    
    void changeDirection();
    void reset();
    
    void sequence();
};

#endif
