/*!
\author David "Dawn" Estes McKnight
\date 12 September 2016
*/

#ifndef BOUNCELESSINPUT_H
#define BOUNCELESSINPUT_H
#include "BouncelessInput.h"

BouncelessInput::BouncelessInput(PinName name, PinMode mode):DigitalIn(name, mode),
    _bitStream(0x55)    //01010101

{
    _lastSteadyState=false;     //Reads whatever the raw value is as the initial state for this

    _recentlyPressed=false;     //The button was not recently pressed
    _recentlyDepressed=false;   //The button was not recently depressed

    _ticker.attach(this, &BouncelessInput::update, 0.001); // less than .05 seconds (for the total stream to be converted) to stabilize, as recommended by http://www.eng.utah.edu/~cs5780/debouncing.pdf
}

void BouncelessInput::update()
{
    _bitStream=(_bitStream>>1);                        //Shifts bits left
    if (DigitalIn::read()) {
        _bitStream|=0x80;
    }
    _bitStream|=DigitalIn::read();        //Changes last bit to a 1 if raw value of DigitalIn is 1 (on), 0 if it is 0 (off)

    if (_bitStream==0x00) {
        if (_lastSteadyState==true)     //Checks to see if the last steady state was on
            _recentlyPressed=true;       //If so, the button was recently pressed
        _lastSteadyState=false;           //The stable stream of 0s indicates that the new last-read steady state is 0 (off)

    } else if(_bitStream==0xFF) {              //Checks for stable stream of 1s (on)
        if (_lastSteadyState==false)     //Checks to see if the last steady state was off
            _recentlyDepressed=true;       //If so, the button was recently depressed
        _lastSteadyState=true;           //The stable stream of 1s indicates that the new last-read steady state is 1 (on)
    }
}

BouncelessInput::operator int()
{
    return read();
}

int BouncelessInput::read()
{
    return _lastSteadyState;
}

bool BouncelessInput::recentlyPressed()
{
    if (_recentlyPressed) {             //Checks to see if the button was recently pressed (i.e., this function had not been called since the last time the button was pressed)
        _recentlyPressed=false;         //If so, then we reset the value (we've now called this instance function since the last button press)
        return true;                    //Because we hadn't prior to calling this instance of the function, we return that yes, the button was recently pressed
    }
    return false;                       //If not, we return false, that it was not recently pressed
}

bool BouncelessInput::recentlyDepressed()
{
    if (_recentlyDepressed) {             //Checks to see if the button was recently depressed (i.e., this function had not been called since the last time the button was depressed)
        _recentlyDepressed=false;         //If so, then we reset the value (we've now called this instance function since the last button depress)
        return true;                    //Because we hadn't prior to calling this instance of the function, we return that yes, the button was recently depressed
    }
    return false;                       //If not, we return false, that it was not recently depressed
}

#endif