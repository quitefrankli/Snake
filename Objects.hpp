#ifndef Objects_hpp
#define Objects_hpp

#include <memory>
#include <vector>

// base game object class think actor
class Object {
public:
    Object();
    Object(double x, double y, double r, double g, double b);
    Object(float x, float y, float r, float g, float b, float alpha);
	virtual ~Object() = default;

    double &getPosX() { return posX; }
    double &getPosY() { return posY; }
    bool getVisibility() { return isVisible; }
    
    void setVisibility(bool value) { isVisible = value; }
    void setPosX(double value) { posX = value; }
    void setPosY(double value) { posY = value; }
    void setPos(double x, double y) { posX = x; posY = y; }
    void setRGB(double r, double g, double b);
    void setAlpha(float alpha) { this->alpha = alpha; }
    
    uint32_t getID() { return id; }
    void setID(uint32_t id) { this->id = id; }
    
    double getPosXTranslated();
    double getPosYTranslated();
    
    void draw();

private: //Data
	bool isVisible = true;
	double colour[3];
	double posX, posY;
	float alpha = 1;
	uint32_t id;
};

// for more advanced AIs that use vision to move
class Vision { //coded under the assumption that vision size does not change
private:
    int size = 1; //default meaning 1 block in each direction
public:
    Vision(int x, int y, int size);
    ~Vision();
    std::vector<std::unique_ptr<Object>> vision;
    void draw();
    void sync(int x, int y);
};

// main snake player
class Snake: public Object {
private:
    int direction;
    int newDirection; //request made from key manager
    double speed;
    std::unique_ptr<Vision> snakeVision;
public:
    Snake();
    ~Snake();
    std::vector<std::unique_ptr<Object>> body;
    void setDirection(int direction) { this->direction = direction; }
    int getDirection() { return direction; }
    void setSpeed(double speed) { this->speed = speed; }
    int getSpeed() { return speed; }
    void setNewDirection(int newDirection) { this->newDirection = newDirection; }
    
    unsigned getLength() { return body.size(); }
    bool checkCollisions(unsigned *num, double *x, double *y); //bool returns true for collision, num gives number of collisions and their coordinates
    void sequence();
    void reset();
    void grow();
    void draw();
    void drawTransparent();
};

// snakes need food to grow
class Food: public Object {
public:
    Food();
	~Food() {};

    void reset();
};

// boundaries of the game should a snake touch it, it dies
class Wall: public Object {
public:
    Wall(double x, double y, double r, double g, double b);
	~Wall() {}
    
    void sequence();
};

#endif /* Objects_hpp */
