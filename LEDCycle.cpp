/*!
\author David "Dawn" Estes McKnight
\date 12 September 2016
*/

#include "LEDCycle.h"

LEDCycle::LEDCycle()
{
    state=0;
    leds=std::vector<DigitalOut*>();
    setActiveValue(ACTIVEHIGH);
}

LEDCycle::LEDCycle(PinName pin1, PinName pin2, PinName pin3)
{
    state=0;

    leds=std::vector<DigitalOut*>();
    leds.push_back(new DigitalOut(pin1));
    leds.push_back(new DigitalOut(pin2));
    leds.push_back(new DigitalOut(pin3));
    setActiveValue(ACTIVEHIGH);
}
LEDCycle::LEDCycle(PinName pin1, PinName pin2, PinName pin3, PinName pin4)
{
    state=0;
    leds=std::vector<DigitalOut*>();
    leds.push_back(new DigitalOut(pin1));
    leds.push_back(new DigitalOut(pin2));
    leds.push_back(new DigitalOut(pin3));
    leds.push_back(new DigitalOut(pin4));
    setActiveValue(ACTIVEHIGH);
}

LEDCycle::~LEDCycle()
{
    for (int i=0; i<leds.size(); i++)
        delete leds[i];
    leds.clear();
}

void LEDCycle::cycle()
{
    if (state==leds.size()) {                      //Increment state and see if we've turned on all the LEDs
        while(state>0) {                           //Decrements state until it reaches 0
            (*leds[--state]).write(!activeValue);  //turns the LEDs off
        }
    } else {
        state++;
        leds[state-1]->write(activeValue);         //Turns LEDs on
    }
}

void LEDCycle::setActiveValue(int activeVal)
{
    activeValue=activeVal;
    for (int i=0; i<leds.size(); i++)
        leds[i]->write(!activeValue);
}

void LEDCycle::setAllTo(bool b)
{
    for (int i=0; i<leds.size(); i++)
        leds[i]->write(b);
}

mbed::DigitalOut LEDCycle::operator[](int index)
{
    return *leds[index];
}
