#ifndef Graphics_hpp
#define Graphics_hpp

namespace Graphics {
    static bool fullScreen = false;
    static bool transparent = true;
	const static bool antiAliasing = false;
    
    const int windowWidth = 1200;
    const int windowHeight = 800;
    const int gameWidth = 800;
    const int gameHeight = gameWidth; //for now they have to be equal
    const int interfaceWidth = windowWidth-gameWidth;
    const int interfaceHeight = windowHeight;
    const float interfaceXPos = -1 + (float)gameWidth/(float)windowWidth * 2.0;
    const float interfaceYPos = 0;
    
    const double windowsPosX = 0;
    const double windowsPosY = 0;
    const unsigned sleepTimeMilli = 35;
    
    void display();
    void idle();
    void toggleFullScreen();
    
    int getGLKey(int key);
}

#endif


