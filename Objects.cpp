#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#include <GL.H>
#include <GLU.H>
#include <glut.h>
#elif defined(__APPLE__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" //Removes annoying warnings
#include <unistd.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
std::exit(0);
#endif

#include <memory>
#include <vector>
#include <iostream>
#include <utility>

#include "Objects.hpp"
#include "Game.hpp"
#include "Interface.hpp"
#include "General.hpp"

using namespace std;

extern Game game;
extern Interface interfaceObj;

Object::Object() {
    posX = posY = game.getBlocksAcross() / 2;
    setRGB(1, 1, 1);
    id = game.UNDEFINED;
}

Object::Object(double x, double y, double r, double g, double b) {
    posX = x; posY = y;
    colour[0] = r; colour[1] = g; colour[2] = b;
    id = game.UNDEFINED;
}

Object::Object(float x, float y, float r, float g, float b, float alpha) {
    posX = x; posY = y; colour[0] = r; colour[1] = g; colour[2] = b; this->alpha = alpha;
    id = game.UNDEFINED;
}

void Object::setRGB(double r, double g, double b) {
    colour[0] = r; colour[1] = g; colour[2] = b;
}

double Object::getPosXTranslated() {
    double x = -1 + (posX * 2.0/game.getBlocksAcross()) * Graphics::gameWidth/Graphics::windowWidth; //mapping
    return x;
}

double Object::getPosYTranslated() {
    double y = 1 - (posY * 2.0/game.getBlocksAcross()) * Graphics::gameHeight/Graphics::windowHeight;;
    return y;
}

void Object::draw() {
    double x = getPosXTranslated();
    double y = getPosYTranslated();
    double blockLength = game.getBlockLength();
    double blockHeight = game.getBlockHeight();
    double pixelLength = game.getPixelLength();
    double pixelHeight = game.getPixelHeight();

    //perimeter
    glColor3d(0.8, 0.8, 0.8);
    glBegin(GL_LINE_LOOP);
    {
        glVertex2d(x, y);
        glVertex2d(x+blockLength, y);
        glVertex2d(x+blockLength, y-blockHeight);
        glVertex2d(x, y-blockHeight);
    }
    glEnd();
    //interiors
    glColor4f(colour[0], colour[1], colour[2], alpha);
    glRectd(x+pixelLength, y-pixelHeight, x+blockLength-pixelLength, y-blockHeight+pixelHeight);
}

Snake::Snake() {
    setPosX(game.getBlocksAcross()/2);
    setPosY(game.getBlocksAcross()/2);
    newDirection = Game::STOP;
    snakeVision = unique_ptr<Vision>(new Vision(getPosX(), getPosY(), 3));
    setVisibility(false);
    grow();
}

Snake::~Snake() {
    body.clear();
    body.shrink_to_fit();
}

void Snake::sequence() {
    if (newDirection != game.STOP) {
        if (newDirection != direction * -1) direction = newDirection;
        vector<unique_ptr<Object>>::iterator itBody = body.end();
        vector<unique_ptr<Object>>::iterator itHead = body.begin();
        
        for (itBody--; itBody != itHead; itBody--) { //start from tail and work to head
            (*itBody)->setPosX((*(itBody-1))->getPosX());
            (*itBody)->setPosY((*(itBody-1))->getPosY());
        }
        
        switch (direction) {
            case game.LEFT:
                (*itHead)->setPosX((*itHead)->getPosX()-game.getStandardVelocity());
                break;
            case game.RIGHT:
                (*itHead)->setPosX((*itHead)->getPosX()+game.getStandardVelocity());
                break;
            case game.UP:
                (*itHead)->setPosY((*itHead)->getPosY()-game.getStandardVelocity());
                break;
            case game.DOWN:
                (*itHead)->setPosY((*itHead)->getPosY()+game.getStandardVelocity());
                break;
        }
        
        this->setPos((*itHead)->getPosX(), (*itHead)->getPosY()); //syncing head
    }
    game.updateGrid(this);
}

void Snake::reset() {
    body.clear();
    body.shrink_to_fit();

    setPosX(game.getBlocksAcross()/2);
    setPosY(game.getBlocksAcross()/2);
	direction = newDirection = game.STOP;
    grow();
}

bool Snake::checkCollisions(unsigned *num, double *x, double *y) {
    double tmpX = getPosX();
    double tmpY = getPosY();
    
    //check for collision with wall
    if (tmpX == 0 ||
        tmpX == game.getBlocksAcross()-1 ||
        tmpY == 0 ||
        tmpY == game.getBlocksAcross()-1) return true;
    
//    //check for collision with self
//    vector<unique_ptr<Object>>::iterator itBody;
//    for (itBody = body.begin() + 1; itBody < body.end(); itBody++)
//         if (tmpX == (*itBody)->getPosX() && tmpY == (*itBody)->getPosY()) return true;
    
    //check for collision with food
    for (auto &ptr : game.food) {
        if (tmpX == ptr->getPosX() && tmpY == ptr->getPosY()) {
            ptr->randomise();
            this->grow();
        }
    }
    
    return false;
}

void Snake::grow() {
    double r = (rand() % 100 + 1) / 100.0;
    double g = (rand() % 100 + 1) / 100.0;
    double b = (rand() % 100 + 1) / 100.0;
    
    unique_ptr<Object> newBody(new Object(0, 0, r, g, b));
    
    if (body.size() != 0) {
        vector<unique_ptr<Object>>::iterator itBody = body.end() - 1;
        //try this after auto itBody2 = body.end() - 1;
        newBody->setPosX((*itBody)->getPosX());
        newBody->setPosY((*itBody)->getPosY());
    } else {
        newBody->setPosX(this->getPosX());
        newBody->setPosY(this->getPosY());
    }
    newBody->setID(this->getID());
    body.push_back(move(newBody));
}

void Snake::draw() {
    for (auto &ptr : body) ptr->draw();
}

void Snake::drawTransparent() {
    snakeVision->sync(getPosX(), getPosY());
    snakeVision->draw();
    
//    string str("x");
//    interfaceObj.drawString(getPosXTranslated(), getPosYTranslated(), 1, 1, 1, 0, str);
}

Wall::Wall(double x, double y, double r, double g, double b): Object(x, y, r, g, b) {}

void Wall::sequence() {
    game.updateGrid(this);
}

Food::Food() {
    setRGB(1, 0.3, 0);
    randomise();
}

void Food::randomise() {
    General::randomise(getPosX(), getPosY());
}

Vision::Vision(int x, int y, int size) {
    this->size = size;
    for (int tmpY = y - size; tmpY < y + size + 1; tmpY++) {
        for (int tmpX = x - size; tmpX < x + size + 1; tmpX++) {
            if (tmpY != y || tmpX != x) {
                unique_ptr<Object> newBlock(new Object(tmpX, tmpY, 0.8, 0.3, 0, 0.1));
                vision.push_back(move(newBlock));
            }
        }
    }
}

Vision::~Vision() {
    vision.clear();
    vision.shrink_to_fit();
}

void Vision::sync(int x, int y) {
    vector<unique_ptr<Object>>::iterator itVision = vision.begin();
    for (int tmpY = y - size; tmpY < y + size + 1; tmpY++) {
        for (int tmpX = x - size; tmpX < x + size + 1; tmpX++) {
            if (tmpY != y || tmpX != x) {
                (*itVision)->setPos(tmpX, tmpY);
                itVision++;
            }
        }
    }
}

void Vision::draw() {
    for (auto &it : vision) it->draw();
}
