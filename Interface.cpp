#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#elif defined(__APPLE__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" //Removes annoying warnings
#include <unistd.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
std::exit(0);
#endif

#include <iostream>

#include "Graphics.hpp"
#include "Interface.hpp"
#include "Game.hpp"
#include "Objects.hpp"

extern Game game;

using namespace std;

void Interface::draw() {
    string str("SNAKE");
    string str2("SCORE");

    // writes "SNAKE"
    glPushMatrix();
    glTranslatef(((float)Graphics::gameWidth)/((float)Graphics::windowWidth) * 0.5 + 0.02, 0.75, 0);
    glScalef(0.0015, 0.001, 0);
    glColor3f(0, 1, 0);
    glLineWidth(6);
    for (char &c : str)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    glPopMatrix();
    
    // writes "SCORE"
    glPushMatrix();
    glTranslatef(((float)Graphics::gameWidth)/((float)Graphics::windowWidth) * 0.5 + 0.02, 0.5, 0);
    glScalef(0.0005, 0.0005, 0);
    glColor3f(0.8, 0.1, 0.1);
    glLineWidth(3);
    for (char &c : str2) 
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    glPopMatrix();
    
    int score = game.snake[0]->getLength();
    drawString(0.8, 0.5, 0, 1, 0, to_string(score));
    glLineWidth(1);
    
    if (boolGrid) 
        drawGrid();
}

void Interface::drawString(float x, float y, float r, float g, float b, std::string str) {
    glColor3f(0, 1, 0);
    glRasterPos2f(x, y);
    for (char &c : str) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
}

void Interface::drawGrid() {
    float yPos = Graphics::interfaceYPos;
    float xPos = Graphics::interfaceXPos;
    float xInc = 2*(float)Graphics::interfaceWidth/(float)Graphics::windowWidth/(float)game.getBlocksAcross();
    float yInc = (float)Graphics::interfaceHeight/(float)Graphics::windowHeight/(float)game.getBlocksDown();
    bool skip = false;
    
    glColor3f(0, 0, 1);
    for (unsigned y = 0; y < game.grid->size(); y++) {
        xPos = Graphics::interfaceXPos;
        for (unsigned x = 0; x < (*game.grid)[y].size(); x++) {
            switch ((*game.grid)[y][x][0]) {
                case game.EMPTY:
                    skip = true;
                    break;
                case game.SNAKE_HUMAN_BODY:
                    glColor3f(0.8, 0.2, 0);
                    break;
                case game.SNAKE_AI_BODY:
                    glColor3f(0, 0.2, 0.8);
                    break;
                case game.WALL:
                    glColor3f(0, 0, 0);
                    break;
            }
            if (!skip) glRectf(xPos, yPos, xPos+xInc, yPos-yInc);
            else skip = false;
            xPos += xInc;
        }
        yPos -= yInc;
    }
}
