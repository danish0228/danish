#include "platform.h"
#include "PinNames.h"
#include "SPI.h"


#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

using namespace mbed;

SPI::SPI(PinName mosi, PinName miso, PinName sclk, const char *name)
    : _mosi(-1)
    , _miso(-1)
    , _sclk(-1)
    , _fd(-1)
    , _bits(8)
    , _hz(1000000)
    , _mode(0)
    , _delay(0)
{
    _name = (char *)name;
    // ハードSPIのみをサポート（ピン固定）
    if (mosi == MOSI && miso == MISO && sclk == SCKL) {
        _fd = open("/dev/spidev0.0", O_RDWR);
        if (ioctl(_fd, SPI_IOC_WR_BITS_PER_WORD, &_bits) < 0)
            return;
        if (ioctl(_fd, SPI_IOC_WR_MODE, &_mode) < 0)
            return;
        if (ioctl(_fd, SPI_IOC_WR_MAX_SPEED_HZ, &_hz) < 0)
            return;
    }
}

void SPI::format(int bits, int mode) {
    if (_fd >= 0) {
        _bits = bits;
        _mode = mode;
        if (ioctl(_fd, SPI_IOC_WR_BITS_PER_WORD, &_bits) < 0)
            return;
        if (ioctl(_fd, SPI_IOC_WR_MODE, &_mode) < 0)
            return;
    }
}

void SPI::frequency(int hz) {
    if (_fd >= 0) {
        _hz = hz;
        if (ioctl(_fd, SPI_IOC_WR_MAX_SPEED_HZ, &_hz) < 0)
            return;
    }
}

int SPI::write(int value) {
    int ret;
    _tx[0] = value;
    _rx[0] = 0;

    struct spi_ioc_transfer tr;
	tr.tx_buf = (unsigned long)_tx;
	tr.rx_buf = (unsigned long)_rx;
	tr.len = 1;
	tr.delay_usecs = _delay;
	tr.speed_hz = _hz;
	tr.bits_per_word = _bits;
    
    if ((ret = ioctl(_fd, SPI_IOC_MESSAGE(1), &tr)) < 0)
        return ret;
    return _rx[0];
}

