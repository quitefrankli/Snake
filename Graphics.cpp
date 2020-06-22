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

#include <chrono>
#include <thread>

#include "Graphics.hpp"
#include "Game.hpp"
#include "Interface.hpp"

extern Game game;
extern Interface interfaceObj;

using namespace std;
using namespace this_thread;
using namespace chrono;

void Graphics::display() {
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game.drawAll();
    //transparent stuff must be drawn after
    if (transparent) game.drawTransparent();
    interfaceObj.draw();
    
    glutSwapBuffers();
}

void Graphics::idle() {
    game.sequence(); //has internal setting for setting frame rates
    sleep_for(milliseconds(sleepTimeMilli)); //setting game speed = 1/1000th of a second
}

void Graphics::toggleFullScreen() {
    glutFullScreen();
}

int Graphics::getGLKey(int key) {
    if (key >= GLUT_KEY_LEFT && key <= GLUT_KEY_DOWN) {
        switch (key) {
            case GLUT_KEY_LEFT:
                return game.LEFT;
            case GLUT_KEY_RIGHT:
                return game.RIGHT;
            case GLUT_KEY_UP:
                return game.UP;
            case GLUT_KEY_DOWN:
                return game.DOWN;
            default:
                break;
        }
    }
    
    return 0;
}

//60fps => 1 sec has 60 frames... total sleep time must fit into 1 sec so that there are 60 sleep cycles in 1 sec
//so sleeptime = 1/60 = 0.0166
