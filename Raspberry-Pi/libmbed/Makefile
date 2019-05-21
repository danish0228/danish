#DEBUG  = -g -O0
INCLUDE = -I/usr/local/include -I.

GCCPREFIX=/usr/bin

CC=$(GCCPREFIX)/gcc
CXX=$(GCCPREFIX)/g++
AS=$(GCCPREFIX)/as
LD=$(GCCPREFIX)/ld
AR=$(GCCPREFIX)/ar
OBJCOPY=$(GCCPREFIX)/objcopy

CFLAGS = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

CXXFLAGS= $(CFLAGS)
LDFLAGS = -L/usr/local/lib
LIBS    = -lwiringPi

OBJS=	DigitalOut.o BusOut.o TextLCD.o wait_api.o I2C.o SPI.o

all: libmbed.a


libmbed.a:  $(OBJS)
	$(AR) r $@ $^

clean:
	-rm libmbed.a
	-rm *.o
