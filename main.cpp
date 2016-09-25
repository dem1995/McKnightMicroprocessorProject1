/*!
\author David "Dawn" Estes McKnight
\date 12 September 2016
*/

#include "mbed.h"
#include "LEDCycle.h"
#include "BouncelessInput.h"
BouncelessInput grButton(p5, PullUp);
BouncelessInput gbButton(p10, PullUp);
BouncelessInput brButton(p30, PullDown);
bool gr, gb, br;


int main()
{
    LEDCycle blueLEDs(LED1, LED2, LED3, LED4);
    blueLEDs.setActiveValue(ACTIVEHIGH);
    LEDCycle greenLEDs(p20, p19, p18);
    greenLEDs.setActiveValue(ACTIVEHIGH);
    LEDCycle redLEDs(p21, p22, p23);
    redLEDs.setActiveValue(ACTIVELOW);

    while(1) {
        gr=grButton.recentlyPressed();
        gb=gbButton.recentlyPressed();
        br=brButton.recentlyPressed();
        if (br) {
            redLEDs.cycle();
            blueLEDs.cycle();
        }
        if (gb) {
            greenLEDs.cycle();
            blueLEDs.cycle();
        }
        if (gr) {
            greenLEDs.cycle();
            blueLEDs.cycle();
        }

        /*

        if(gr||gb||br)
        {
        if (gr||gb)
            greenLEDs.cycle();
        if (gb||br)
            blueLEDs.cycle();
        if (br||gr)
            redLEDs.cycle();
            }
         */
    }

}
