#include "platform.h"
#include "PinNames.h"
#include "I2C.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

using namespace mbed;

I2C::I2C(PinName sda, PinName scl, const char *name)
{
	_name = (char *)name;
    _fd = -1;
    // ハードI2Cのみをサポート（ピン固定）
    if (sda == SDA && scl == SCL) {
        _fd = open("/dev/i2c-0", O_RDWR);
    }    
}

int I2C::read(int address, char *data, int length, bool repeated) {
    int len;
    if (_fd >= 0) {
        ioctl(_fd, I2C_SLAVE, address>>1);
        if ((len = ::read(_fd, data, length)) > 0) {
            // 今は、戻り値のサイズをチェックしない
            return (0);
        }
        else
            return (-1);
    }
    else
        return (-1);
}

int I2C::read(int ack) {
    int     len;
    char    buf[1];
    if (_fd >= 0) {
        if ((len = ::read(_fd, buf, 1)) > 0) {
            // 今は、戻り値のサイズをチェックしない
            return (buf[0]);
        }
        else
            return (0);
    }
    else
        // 失敗したときに-1だと変な動きをするかも知れないので、ここでは0を返す
        return (0);
}

int I2C::write(int address, const char *data, int length, bool repeated) {
    int len;
    if (_fd >= 0) {
	int addr = address>>1;
        ioctl(_fd, I2C_SLAVE, addr);
        if ((len = ::write(_fd, data, length)) > 0) {
            // 今は、戻り値のサイズをチェックしない
            return (0);
        }
        else
            return (-1);
    }
    else
        return (-1);
}

int I2C::write(int ack) {
    int     len;
    char    buf[1];
    if (_fd >= 0) {
        if ((len = ::write(_fd, buf, 1)) > 0) {
            // 今は、戻り値のサイズをチェックしない
            return (1);
        }
        else
            return (0);
    }
    else
        return (0);
}

