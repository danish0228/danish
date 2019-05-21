#include <mbed.h>

#include <stdio.h>


SPI spi(p10, p11, p12);


int main()
{
	char*   buf = "Hello world\n";
    int     value;
    
    spi.frequency(500000);
	while((value = *buf++)) {
		spi.write(value);
	}
}
