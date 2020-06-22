#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

#include "Game.hpp"
#include "Objects.hpp"
#include "Graphics.hpp"
#include "AI.hpp"

using namespace std;
using namespace this_thread;
using namespace chrono;

Game::Game() {
    assert(blocksAcross % 2 == 0); //required for some implementations
    assert(blocksAcross == blocksDown);
    assert(Graphics::gameWidth % blocksAcross == 0); //makes sure it's divisible

    int i, x, y;
    grid = make_unique<vector<vector<vector<int>>>>
    (blocksDown, vector<vector<int>>(blocksAcross, vector<int>(maxEntitiesPerSector, UNDEFINED)));
    
    for (y = 0; y != blocksDown; y++) {
        for (x = 0; x != blocksAcross; x++) {
            if (y == 0 || x == 0 || y == blocksDown-1 || x == blocksAcross-1) {
                (*grid)[y][x][0] = WALL;
                unique_ptr<Wall> newWall(new Wall(x, y, 0, 0, 0));
                border.push_back(move(newWall));
            }
        }
    }
    
    //Human snake
    for (i = 0; i < numberOfSnake; i++) {
        unique_ptr<Snake> newSnake(new Snake);
        snake.push_back(move(newSnake));
    }
    
    //Computer snake
    for (i = 0; i < numberOfSnakeAI; i++) {
        unique_ptr<SnakeAI> newSnakeAI(new SnakeAI);
        snakeAI.push_back(move(newSnakeAI));
    }
    
    //Food
    for (i = 0; i < numberOfFood; i++) {
        unique_ptr<Food> newFood(new Food);
        food.push_back(move(newFood));
    }
}

Game::~Game() {
    border.clear();
    snake.clear();
    snakeAI.clear();
    food.clear();
}

void Game::updatePositions() {
    //General
    vector<unique_ptr<Object>>::iterator itBody, itHead;
    
    //Border
    for (auto &wallPtr : border)
        wallPtr->sequence();
    
    //Human Snake
    for (auto &snakeHumanPtr : snake)
        snakeHumanPtr->sequence();

    //AI Snake
    for (auto &snakeAIPtr : snakeAI)
        snakeAIPtr->sequence();
}

void Game::checkCollisions() {
    for (auto &snakeHumanPtr : snake)
        if (snakeHumanPtr->checkCollisions(NULL, NULL, NULL)) snakeHumanPtr->reset();
    
    for (auto itSnakeAI = snakeAI.begin(); itSnakeAI < snakeAI.end(); itSnakeAI++)
        if ((*itSnakeAI)->checkCollisions(NULL, NULL, NULL)) snakeAI.erase(itSnakeAI);
}

void Game::resetGrid() {
for (auto &y : *grid)
    for (auto &x : y) x[0] = EMPTY;
}

void Game::updateGrid() {
    resetGrid();
    
    for (auto &ptr : border)
        (*grid)[ptr->getPosY()][ptr->getPosX()][0] = WALL;
    for (auto &ptr : food)
        (*grid)[ptr->getPosY()][ptr->getPosX()][0] = FOOD;
    
    for (auto &snakeHead : snake)
        for (auto &snakeBody : snakeHead->body)
            (*grid)[snakeBody->getPosY()][snakeBody->getPosX()][0] = SNAKE_HUMAN_BODY;
    
    for (auto &snakeHead : snakeAI)
        for (auto &snakeBody : snakeHead->body)
            (*grid)[snakeBody->getPosY()][snakeBody->getPosX()][0] = SNAKE_AI_BODY;
}

void Game::updateGrid(Object *basePointer) {
    if (dynamic_cast<Wall *>(basePointer) != nullptr) {
        Wall *wallPtr = dynamic_cast<Wall *>(basePointer);
        (*grid)[wallPtr->getPosY()][wallPtr->getPosX()][0] = WALL;
    } else if (dynamic_cast<Food *>(basePointer) != nullptr) {
        
    } else if (dynamic_cast<SnakeAI *>(basePointer) != nullptr) {
        SnakeAI *snakeAIPtr = dynamic_cast<SnakeAI *>(basePointer);
        for (auto &ptr : snakeAIPtr->body)
            (*grid)[ptr->getPosY()][ptr->getPosX()][0] = SNAKE_AI_BODY;
    } else if (dynamic_cast<Snake *>(basePointer) != nullptr) {
        Snake *snakePtr = dynamic_cast<Snake *>(basePointer);
        for (auto &ptr : snakePtr->body)
            (*grid)[ptr->getPosY()][ptr->getPosX()][0] = SNAKE_HUMAN_BODY;
    } else {
        cerr << "Error in updateGrid!" << endl;
    }
}

void Game::gameOver() {
//    //gameOverBool = true;
//    //exit(0);
}

void Game::quit() {
    cout << "Exiting..." << endl;
    exit(0);
}

bool Game::sequence() {
    if (!gameOverBool) {
        if (!pause) {
            if (getTickCounter() >= 0) { //Game update after every nth tick
                resetGrid();
                updatePositions();
                checkCollisions();
                clearTickCounter();
                Graphics::display();
            } else {
                incrementTickCounter(); // for fps
            }
        }
    } else {
        cout << "Game Over!" << endl;
    }
    
    return true;
}

void Game::drawAll() {
    for (auto &borderPtr : border)
        borderPtr->draw();
    for (auto &foodPtr : food)
        foodPtr->draw();
    for (auto &snakeHumanPtr : snake)
        snakeHumanPtr->draw();
    for (auto &snakeAIPtr : snakeAI)
        snakeAIPtr->draw();
}

void Game::drawTransparent() {
    for (auto &snakeHumanPtr : snake)
        snakeHumanPtr->drawTransparent();
    for (auto &snakeAIPtr : snakeAI)
        snakeAIPtr->drawTransparent();
}
