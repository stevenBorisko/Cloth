#ifndef DISPLAYABLE_HPP
#define DISPLAYABLE_HPP

#include <stdio.h>
#include <vector>

class Displayable {
public:
    virtual void setup();
    virtual void update();
    
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void mouseEntered(int x, int y);
    virtual void mouseExited(int x, int y);
    virtual void windowResized(int w, int h);
    
private:
    
};

#endif
