#include <iostream>

#include "Graphics.hpp"
#include "Game.hpp"
#include "Objects.hpp"
#include "KeyManager.hpp"
#include "Interface.hpp"

extern Game game;
extern Interface interfaceObj;

using namespace std;

void KeyManager::keyDown(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            game.quit();
            break;
        case 'f':
            //Graphics::toggleFullScreen();
            break;
        case 'p':
            game.togglePause();
            break;
        case 'g':
            game.snake[0]->grow();
            break;
        case 'i':
            interfaceObj.setDrawGrid(true);
            break;
        case 's':
            game.snake[0]->setDirection(0);
            break;
        case 'v':
            if (Graphics::transparent) Graphics::transparent = false;
            else Graphics::transparent = true;
            break;
        case '=':
            int i;
            cout << "Please enter amount of growth: ";
            cin >> i;
            for (int counter = 0; counter < i; counter++) (*(game.snake.begin()))->grow();
            game.togglePause();
            cout << "Game paused, unpause to continue." << endl;
            break;
    }
}

void KeyManager::keyUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'i':
            interfaceObj.setDrawGrid(false);
            break;
    }
}

void KeyManager::specialKeyDown(int key, int x, int y) {
    Snake *snake = game.snake[0].get();
    int val = Graphics::getGLKey(key);
    snake->setNewDirection(val);
}

void KeyManager::specialKeyUp(int key, int x, int y) {
    
}
