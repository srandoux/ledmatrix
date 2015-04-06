#ifndef __SIMPLEPLASMA_H__
#define __SIMPLEPLASMA_H__


#include "threaded-canvas-manipulator.h"
#include "led-matrix.h"
using namespace rgb_matrix;



class SimplePlasma : public ThreadedCanvasManipulator
{
public:
    SimplePlasma(Canvas *m);
    void Run();
    
 private:
    const float radius1, radius2, radius3, radius4, centerx1, centerx2, centerx3, centerx4, centery1, centery2, centery3, centery4;
    float angle1, angle2, angle3, angle4;
    long hueShift;
    
    static const unsigned char localgamma[];
    static signed char sinetab[];
    
    unsigned short ColorHSV(long hue, unsigned char sat, unsigned char val, int gflag);
 };


#endif /*__SIMPLEPLASMA_H__*/
