#include <math.h>
#include <time.h>

void wait(float s)
{
    struct timespec sleeper, dummy ;
    
    sleeper.tv_sec  = (time_t)(floor(s)) ;
    sleeper.tv_nsec = (long)(ceil(s)*1000000);
    
    nanosleep (&sleeper, &dummy) ;    
}

/*
void wait_us(int us)
{
    struct timespec sleeper, dummy ;
    
    sleeper.tv_sec  = (time_t)(us / 1000000) ;
    sleeper.tv_nsec = (long)(us % 1000000);

    nanosleep (&sleeper, &dummy) ;
}
*/
void wait_us(unsigned int us)
{
	volatile unsigned int i;
	unsigned int n = us * 100;
	for (i = 0; i < n; i++);
}

void wait_ms(int ms)
{
    struct timespec sleeper, dummy ;
    
    sleeper.tv_sec  = (time_t)(ms / 1000) ;
    sleeper.tv_nsec = (long)(ms % 1000) * 1000000 ;
    
    nanosleep (&sleeper, &dummy) ;
}
