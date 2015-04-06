#include "simpleanalogclock.h"

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include "graphics.h"

SimpleAnalogClock::SimpleAnalogClock(Canvas *m) : ThreadedCanvasManipulator(m),hour(0),min(0),sec(0)
{
}

void SimpleAnalogClock::draw()
{
  Color c(0,0,0xff); 
  
  DrawCircle(canvas(), canvas()->width()/2,  canvas()->height()/2,  canvas()->width()/2-1, c);
}


void SimpleAnalogClock::draw_handles(int h, int m, int s, int r, int g, int b)
{
    float radians;
    unsigned int secx2, secy2, minx2, miny2, hourx2, houry2;
    const int width =canvas()->width();
    const int height = canvas()->height();
    const int sechandle = canvas()->width()/2 -2;
    const int minhandle = canvas()->width()/2 -2;
    const int hourhandle = canvas()->width()/2 - 4; 
    Color c(r,g,b);

    // Pre calculate the hand end coordinates to minimize the time between
    // clearing the old hands and drawing the new ones.
    radians = s * (M_PI/30);
    secx2 = width/2-sinf(radians)*sechandle;
    secy2 = height/2+cosf(radians)*sechandle;
    
    radians = m * (M_PI/30);
    minx2 = width/2-sinf(radians)*minhandle;
    miny2 = height/2+cosf(radians)*minhandle;
    radians = ((float)h + (float)m/60.) * (M_PI/6);
    
    hourx2 = width/2-sinf(radians)*hourhandle;
    houry2 = height/2+cosf(radians)*hourhandle;
    
    // Draw the hands
    // Center = 16,16, minute & second hands = 15 pixels, hour hand = 11 pixels
    DrawLine(canvas(), width/2-1, height/2-1, secx2, secy2, c);
    DrawLine(canvas(), width/2-1, height/2-1, minx2, miny2, c);
    DrawLine(canvas(), width/2-1, height/2-1, hourx2, houry2, c);
}

void SimpleAnalogClock::clock()
{
    
    struct tm result;
    time_t tm;
    
    tm=time(NULL);
    localtime_r(&tm, &result);
    
    /* erase previous handles*/
    draw_handles(hour, min, sec, 0, 0, 0);
    
    sec=result.tm_sec;
    min=result.tm_min;
    hour=result.tm_hour;
    
    /* draw the handles*/
    draw_handles(hour, min, sec, 255, 255, 0);
    
}

void SimpleAnalogClock::Run()
{
    /*draw the circle*/
    draw();
    
    while (running())
    {
        usleep(500000);
        clock();
    }
}
