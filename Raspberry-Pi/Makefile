DEBUG   = -g -O0
INCLUDE = -I/usr/local/include -I libmbed

GCCPREFIX=/usr/bin

CC=$(GCCPREFIX)/gcc
CXX=$(GCCPREFIX)/g++
AS=$(GCCPREFIX)/as
LD=$(GCCPREFIX)/ld
AR=$(GCCPREFIX)/ar
OBJCOPY=$(GCCPREFIX)/objcopy

CFLAGS = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

CXXFLAGS= $(CFLAGS)
LDFLAGS = -L/usr/local/lib -L.
LIBS    = libmbed/libmbed.a -lwiringPi -lm -lc

TARGETS = LEDTest LCDTest I2CTest SPITest

all:
	cd libmbed; make
	make $(TARGETS)

LCDTest: LCDTest.o $(LIBS)
	$(CXX) $(LDFLAGS) $^ -o $@

LEDTest: LEDTest.o $(LIBS)
	$(CXX) $(LDFLAGS) $^ -o $@

I2CTest: I2CTest.o LM73.o $(LIBS) 
	$(CXX) $(LDFLAGS) $^ -o $@

SPITest: SPITest.o $(LIBS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	-rm $(TARGETS)
	-rm *.o
	cd libmbed; make clean


