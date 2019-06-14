#ifndef BMX055_H
#define BMX055_H

/*
//example
BMX055 bmx(D11,D12,D13,D10,D9,D8);//(mosi,miso,sck,CSB1,CSB2,CSB3) conntect 4-wire spi mode

int main() {

    
    while(1) {
      float mag[4];
      while(bmx.read_mag(mag)==false);
      printf("%d,%d,%d,%d\r\n",(int)mag[0],(int)mag[1],(int)mag[2],(int)mag[3]);
    }
    
    while(1) {
      float gyr[3];
      while(bmx.read_gyr(gyr)==false);
      printf("%d,%d,%d\r\n",(int)gyr[0],(int)gyr[1],(int)gyr[2]);
    }
    
    while(1) {
      float acc[3];
      while(bmx.read_acc(acc)==false);
      printf("%d,%d,%d\r\n",(int)acc[0],(int)acc[1],(int)acc[2]);
    }
}
*/


#define RANGE_2G 0b0011 //acc range
#define RANGE_4G 0b0101
#define RANGE_8G 0b1000
#define RANGE_16G 0b1100

#define BW_7_81 0b01000 //acc bandwidth
#define BW_15_63 0b01001
#define BW_31_25 0b01010
#define BW_62_5 0b01011
#define BW_125 0b01100
#define BW_250 0b01101
#define BW_500 0b01110
#define BW_1000 0b01111

#define RANGE_2000 0b000 //gyro range
#define RANGE_1000 0b001
#define RANGE_500 0b010
#define RANGE_250 0b011
#define RANGE_125 0b100


#define ODR_BW_100_32 0b0111 //gyro output data rate and bandwidth
#define ODR_BW_200_64 0b0110
#define ODR_BW_100_12 0b0101
#define ODR_BW_200_23 0b0100
#define ODR_BW_400_47 0b0111
#define ODR_BW_1000_116 0b0110
#define ODR_BW_2000_230 0b0101
#define ODR_BW_2000_523 0b0100




#include "mbed.h"

class BMX055 {
public:
    BMX055(PinName mosi,PinName miso,PinName sck,PinName _accss,PinName _gyrss,PinName _magss);
    
    char readbyte_acc(char adr);
    void readnbyte_acc(char adr,char *data,char num);//numÇÕîzóÒÇÃêî
    void writebyte_acc(char adr,char data);
    bool read_acc(short *acc);
    char read_temp();
    void calib_acc();
    void init_acc(char range,char bw);
    
    
    char readbyte_gyr(char adr);
    void readnbyte_gyr(char adr,char *data,char num);//numÇÕîzóÒÇÃêî
    void writebyte_gyr(char adr,char data);
    bool read_gyr(short *gyr);
    void calib_gyr();
    void init_gyr(char range,char odr_bw);
    
    char readbyte_mag(char adr);
    void writebyte_mag(char adr,char data);
    void readnbyte_mag(char adr,char *data,char num);//numÇÕîzóÒÇÃêî
    bool read_mag(short *mag);
    void init_mag(unsigned char REPXY,unsigned char REPZ);
    
    

    void offset();
  
 private:
    SPI bmx;
    
    DigitalOut accss;
    DigitalOut gyrss;
    DigitalOut magss;
    
};

#endif