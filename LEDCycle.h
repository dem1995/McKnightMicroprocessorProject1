/*!
\author David "Dawn" Estes McKnight
\date 12 September 2016
*/

#ifndef LEDCYCLE_H
#define LEDCYCLE_H
#include "mbed.h"
#include <vector>
static const int ACTIVEHIGH=1;
static const int ACTIVELOW=0;

//Class for cycling through mbed LED lights

class LEDCycle
{
    public:
    LEDCycle();                                                         //!<The Default Constructor
    LEDCycle(PinName pin1, PinName pin2, PinName pin3);                 //!<Constructor given three PinNames
    LEDCycle(PinName pin1, PinName pin2, PinName pin3, PinName pin4);   //!<Constructor given four PinNames
    ~LEDCycle();                                                        //!<Destructor
    
    void cycle();                                                       //!<Adds one to LEDCycle::state, which determines how many of LEDCycle::leds to light up.
    
    void setActiveValue(int i);                                         //!<Tells the LEDCycle that the lights should be on when they have a value of i and off when they have a value of ~i.
    void setAllTo(bool b);                                              //!<Sets all the lights to b=1 or b=0.
    
    DigitalOut operator[](int index);                                   //!<The indexing operation. Returns the indexth element of LEDCycle::leds.
    
    private:
    int state;                                                          //!<The state that the LEDCycle is in. At any given state value, there will be state leds of LEDCycle::leds lit up.
    int activeValue;                                                    //!<Whether the lights should be turned on with a value of 1, or with a value of 0.
    std::vector<DigitalOut*> leds;                                      //!<A vector (dynamic array) of pointers to DigitalOut objects that control the voltage provided the LEDs connected to the pins contained by those DigitalOut objects.
};
#endif