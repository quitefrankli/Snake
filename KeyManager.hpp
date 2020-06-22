#ifndef KeyManager_hpp
#define KeyManager_hpp

// responsible for player input
namespace KeyManager {
    static int key[256];
    
    void keyDown(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
    void specialKeyDown(int key, int x, int y);
    void specialKeyUp(int key, int x, int y);
}

#endif
