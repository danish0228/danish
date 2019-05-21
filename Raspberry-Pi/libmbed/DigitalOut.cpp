
#include "platform.h"
#include "PinNames.h"
#include "DigitalOut.h"

#include <wiringPi.h>

#ifdef __cplusplus
extern "C" {
#endif
    static bool calledWiringPiSetup = false;
#ifdef __cplusplus
}
#endif

using namespace mbed;

DigitalOut::DigitalOut()
	: _pin(-1)
	, _wiring(-1)
{
}

DigitalOut::DigitalOut(PinName pin, const char* name)
    : _pin(-1)
    , _wiring(-1)
{
	setup(pin, name);
}

void DigitalOut::setup(PinName pin, const char* name)
{
	_pin = pin;
    if (!calledWiringPiSetup) {
        if (wiringPiSetup () == -1)
            return;
        calledWiringPiSetup = true;
    }
    switch (pin) {
        case p2:
            _wiring = 8;
            break;
        case p3:
            _wiring = 9;
            break;
        case p4:
            _wiring = 7;
            break;
        case p6:
            _wiring = 0;
            break;
        case p7:
            _wiring = 2;
            break;
        case p8:
            _wiring = 3;
            break;
        case p10:
            _wiring = 12;
            break;
        case p11:
            _wiring = 13;
            break;
        case p12:
            _wiring = 14;
            break;
        case p14:
            _wiring = 11;
            break;
        case p15:
            _wiring = 10;
            break;
        case p16:
            _wiring = 6;
            break;
        case p18:
            _wiring = 5;
            break;
        case p19:
            _wiring = 4;
            break;
        case p21:
            _wiring = 1;
            break;
        case p22:
            _wiring = 16;
            break;
        case p23:
            _wiring = 15;
            break;            
        default:
            break;
    }
	if (_wiring > 0) {
		pinMode (_wiring, OUTPUT) ;
	}
}

/* Function: write
 *  Set the output, specified as 0 or 1 (int)
 *
 * Variables:
 *  value - An integer specifying the pin output value,
 *      0 for logical 0 and 1 (or any other non-zero value) for logical 1
 */
void DigitalOut::write(int value)
{
    if (_wiring > 0) {
        if (value) {
            digitalWrite (_wiring, 1);
        }
        else {
            digitalWrite (_wiring, 0);
        }
    }
}

int DigitalOut::read()
{
    if (_wiring > 0) {
        return (digitalRead(_wiring));
    }
    else {
        return (0);
    }
}