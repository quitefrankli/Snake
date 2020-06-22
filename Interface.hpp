#ifndef Interface_hpp
#define Interface_hpp

#include <string>

struct Specs {
	float x, y;
	float r, g, b;
	float alpha;
	float lineWidth;
};

// responsible for displaying score and other utilities
class Interface {
private:
    bool boolGrid = false;
public:
    Interface() {}
    ~Interface() {}

	Specs specs;
    
    void draw();
    //assumes default settings
    void drawString(std::string str); //might be good idea to use reference as this copies the string which isn't necessary
    //probably is easier usually to just use the simpler one
    void drawString(float x, float y, float r, float g, float b, std::string str);
    void drawGrid();
    void setDrawGrid(bool val) { boolGrid = val; }
};

#endif
