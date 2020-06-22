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
#include <random>

#include "Game.hpp"
#include "Graphics.hpp"
#include "KeyManager.hpp"
#include "Interface.hpp"

using namespace std;

random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 randGen(rd()); //Standard mersenne_twister_engine seeded with rd()

Game game;
Interface interfaceObj;

void randomise(double& x, double& y) {
    static uniform_int_distribution<> disX(1, game.getBlocksAcross() - 2);
    static uniform_int_distribution<> disY(1, game.getBlocksDown() - 2);
    x = disX(randGen);
    y = disY(randGen);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(Graphics::windowsPosX, Graphics::windowsPosY);
    glutInitWindowSize(Graphics::windowWidth, Graphics::windowHeight);
    glutCreateWindow("Snake");
    glEnable(GL_BLEND); //allows for translucency and blends colour already computer with those in buffer
    if (Graphics::antiAliasing) 
        glEnable(GL_LINE_SMOOTH); //anti-aliasing (NOTE VERY COMPUTATIONALLY INTENSIVE)
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(Graphics::display);
    glutIdleFunc(Graphics::idle);
    glutKeyboardFunc(KeyManager::keyDown);
    glutKeyboardUpFunc(KeyManager::keyUp);
    glutSpecialFunc(KeyManager::specialKeyDown);
    glutSpecialUpFunc(KeyManager::specialKeyUp);
    glutMainLoop();
}

