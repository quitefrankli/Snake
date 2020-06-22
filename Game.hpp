#ifndef Game_hpp
#define Game_hpp

#include <memory>
#include <vector>

#include "Graphics.hpp"
#include "AI.hpp"

// main game logic
class Game {
private:
    int blocksAcross = 50; //how many blocks should fill row-wise
    int blocksDown = blocksAcross;
    int pixelsPerBlock = Graphics::gameWidth/blocksAcross;
    int maxEntitiesPerSector = 50;
    double blockLength = 2.0 * Graphics::gameWidth / Graphics::windowWidth / blocksAcross;
    double blockHeight = 2.0 * Graphics::gameHeight / Graphics::windowHeight / blocksAcross;
    double pixelLength = 2.0 / Graphics::windowWidth;
    double pixelHeight = 2.0 / Graphics::windowHeight;
    double standardVelocity = 1; //must be 1 atm

    const int numberOfSnakeAI = 0; // at the moment the AI snake does nothing but moves randomly and competes with player for food
    const int numberOfSnake = 1; // player
    const int numberOfFood = 1; // at any one time
    
    double scorePosX = 0.5;
    double scorePosY = 0.5;
    double characterWidth = 10;
    double maxCharacters = 3;
    
    unsigned tickCounter = 0;
    unsigned ticksPerFrame = 20;
    
    unsigned score = 0;
    
    bool pause = false;
    bool gameOverBool = false;
    
public:
    Game();
    ~Game();

    bool sequence();
    unsigned getTickCounter() { return tickCounter; }
    void clearTickCounter() { tickCounter = 0; }
    void incrementTickCounter() { tickCounter++; }
    void incrementScore() { score++; }
    
    int getBlocksAcross() { return blocksAcross; }
    int getBlocksDown() { return blocksDown; }
    int getPixelsPerBlock() { return pixelsPerBlock; }
    double getBlockLength() { return blockLength; }
    double getBlockHeight() { return blockHeight; }
    double getPixelLength() { return pixelLength; }
    double getPixelHeight() { return pixelHeight; }
    double getStandardVelocity() { return standardVelocity; }
    
    double getScorePosX() { return scorePosX; }
    double getScorePosY() { return scorePosY; }
    double getCharacterWidth() { return characterWidth; }
    double getMaxCharacters() { return maxCharacters; }
    
    void togglePause() { pause = 1 - pause; }
    void setGameOverBool(bool val) { gameOverBool = val; }
    
    std::vector<std::unique_ptr<Wall>> border;
    std::vector<std::unique_ptr<Food>> food;
    std::vector<std::unique_ptr<Snake>> snake;
    std::vector<std::unique_ptr<SnakeAI>> snakeAI;
    
    std::unique_ptr<std::vector<std::vector<std::vector<int>>>> grid;
    void resetGrid();
    void updateGrid();
    void updateGrid(Object *basePointer);

    void updatePositions(); //every positional change should be reflected here otherwise it could break the grid
    void checkCollisions();
    void gameOver();
    void drawAll();
    void drawTransparent();
    void quit();
    
    enum { //handy for reverse directions
        STOP = 0,
        LEFT = -1,
        RIGHT = 1,
        UP = 2,
        DOWN = -2,
    };
    
    enum entityTypeID : uint32_t { //allows space for 32 different entities on the same coordinate (which should be enough)
        EMPTY               = 0x00,
        
        UNDEFINED           = 0x01,
        WALL                = 0x02,
        FOOD                = 0x04,
        SNAKE_HUMAN_HEAD    = 0x08,
        
        SNAKE_HUMAN_BODY    = 0x10,
        SNAKE_AI_HEAD       = 0x20,
        SNAKE_AI_BODY       = 0x40,
    };
};

#endif
