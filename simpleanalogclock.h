#ifndef __SIMPLEANALOGCLOCK_H__
#define __SIMPLEANALOGCLOCK_H__

#include "threaded-canvas-manipulator.h"
#include "led-matrix.h"
using namespace rgb_matrix;

class SimpleAnalogClock : public ThreadedCanvasManipulator {
   
public:
    SimpleAnalogClock(Canvas *m) ;
    void Run();

private:
    int hour;
    int min;
    int sec;
   
    void draw();

    void draw_handles(int h, int m, int s, int r, int g, int b);
    
    void clock();
    
};

#endif /*__SIMPLEANALOGCLOCK_H__*/
