#include "BMX055.h"
#include "mbed.h"

BMX055 bmx(PB_15,PB_14,PB_13,PA_10,PA_12,PA_11);//(mosi,miso,sck,CSB1,CSB2,CSB3) conntect 4-wire spi mode
Serial pc(USBTX,USBRX); //USBê⁄ë±

int main() {

    pc.printf("aa");
    
    while(1) {
      short mag[4];
      while(bmx.read_mag(mag)==false);
      pc.printf("mag,%d,%d,%d,%d\r\n",(int)mag[0],(int)mag[1],(int)mag[2],(int)mag[3]);
    
      short gyr[3];
      while(bmx.read_gyr(gyr)==false);
      pc.printf("gyr,%d,%d,%d\r\n",(int)gyr[0],(int)gyr[1],(int)gyr[2]);
    
      short acc[3];
      while(bmx.read_acc(acc)==false);
      pc.printf("acc,%d,%d,%d\r\n",(int)acc[0],(int)acc[1],(int)acc[2]);
    }
    
}