// Toggle a LED
#include <mbed.h>

#include <stdlib.h>
#include <unistd.h>

DigitalOut led(p21);

int main()
{
    while(1) {
        led = !led;
        //delay(1000);
        //wait_ms(1000);
        wait_us(1000000);
    }
}

