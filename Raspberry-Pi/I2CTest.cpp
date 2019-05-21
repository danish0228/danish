// Toggle a LED
#include <mbed.h>

#include <stdio.h>

#include "LM73.h"

LM73 lm73(p2, p3);


int main()
{
	while(1) {
		printf("%.2f\n", lm73.read());
		wait_ms(1000);
	}
}
