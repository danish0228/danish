// Toggle a LED
#include <mbed.h>

#include <stdio.h>

#define	LM73_ADDR	(0x4c <<1)

I2C lm73(p2, p3);


int main()
{
	// init LM73
	char	buf[2];
	buf[0] = 0x04; buf[1] = 0x60;
	lm73.write(LM73_ADDR, buf, 2);
	buf[0] = 0x00;
	lm73.write(LM73_ADDR, buf, 1);
	
	while(1) {
		lm73.read(LM73_ADDR, buf, 2);
printf("%02x", buf[0]);
printf("%02x\n", buf[1]);
		printf("%d", buf[0] <<1 | buf[1]>>7);
		printf(".");
		printf("%2d\n", ((buf[1] & 0x7f) *200) >> 8);

		wait_ms(1000);
	}
}
