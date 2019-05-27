
#include "BMX055.h"

BMX055::BMX055(PinName mosi,PinName miso,PinName sck,PinName _accss,PinName _gyrss,PinName _magss):bmx(mosi,miso,sck),accss(_accss),gyrss(_gyrss),magss(_magss)
{
    accss=1;
    gyrss=1;
    magss=1;
    wait(0.1);
    bmx.frequency(10000000);
    bmx.format(8,3);
    init_acc(RANGE_2G,BW_250);
    init_gyr(RANGE_250,ODR_BW_2000_230);
    init_mag(0,0);



}

char BMX055::readbyte_acc(char adr){
    accss=0;
    adr=adr|0b10000000;
    bmx.write(adr);
    char val=bmx.write(0xFF);
    accss=1;
    return val;

}

void BMX055::readnbyte_acc(char adr,char *data,char num){//numÇÕîzóÒÇÃêî
    accss=0;
    adr=adr|0b10000000;
    bmx.write(adr);
    for(int i=0;i<num;i++)data[i]=bmx.write(0xFF);
    accss=1;
}
void BMX055::writebyte_acc(char adr,char data){
    accss=0;
    bmx.write(adr);
    bmx.write(data);
    accss=1;
}
bool BMX055::read_acc(short *acc){
    char data[6];
    readnbyte_acc(0x02,data,6);
    unsigned short buf[3];
    for(int i=0;i<3;i++){
    buf[i]=(data[2*i]>>4)|(data[2*i+1]<<4);
    if(buf[i]>0x800)acc[i]=(short)-1*((~buf[i]+1)&0xfff);
    else acc[i]=(short)buf[i];
    }
    return true;
}
char BMX055::read_temp(){
    return readbyte_acc(0x08);
}
void BMX055::calib_acc(){
    //sensor offset
    writebyte_acc(0x37,0b01111110);
    
    wait_ms(10);
    while(((readbyte_acc(0x36)&0b00010000)>>4)!=1);
    writebyte_acc(0x36,0b00100000);
    while(((readbyte_acc(0x36)&0b00010000)>>4)!=1);
    writebyte_acc(0x36,0b01000000);
    while(((readbyte_acc(0x36)&0b00010000)>>4)!=1);
    writebyte_acc(0x36,0b01100000);
    while(((readbyte_acc(0x36)&0b00010000)>>4)!=1);
}
void BMX055::init_acc(char range,char bw){
    accss=1;
    writebyte_acc(0x14,0xb6);//softwarereset
    
    writebyte_acc(0x0f,range);
    writebyte_acc(0x10,bw);
    
    wait(0.5);
    calib_acc();
}


char BMX055::readbyte_gyr(char adr){
    gyrss=0;
    adr=adr|0b10000000;
    bmx.write(adr);
    char val=bmx.write(0xFF);
    gyrss=1;
    return val;
}
void BMX055::readnbyte_gyr(char adr,char *data,char num){//numÇÕîzóÒÇÃêî
    gyrss=0;
    adr=adr|0b10000000;
    bmx.write(adr);
    for(int i=0;i<num;i++)data[i]=bmx.write(0xFF);
    gyrss=1;
}
void BMX055::writebyte_gyr(char adr,char data){
    gyrss=0;
    bmx.write(adr);
    bmx.write(data);
    gyrss=1;
}
bool BMX055::read_gyr(short *gyr){
    char data[6];
    readnbyte_gyr(0x02,data,6);
    short buf[3];
    for(int i=0;i<3;i++){
    buf[i]=data[2*i]|(data[2*i+1]<<8);
    gyr[i]=buf[i];
    }
    
    return true;
}
void BMX055::calib_gyr(){
    writebyte_gyr(0x32,0b00111111);
}
void BMX055::init_gyr(char range,char odr_bw){
    
    gyrss=1;
    writebyte_gyr(0x14,0xb6);//soft reset
    writebyte_gyr(0x0f,range);
    writebyte_gyr(0x10,odr_bw);//bandwidth&ODR
    calib_gyr();
}

char BMX055::readbyte_mag(char adr){
    magss=0;
    adr=adr|0b10000000;
    bmx.write(adr);
    char val=bmx.write(0xFF);
    magss=1;
    return val;
}
void BMX055::writebyte_mag(char adr,char data){
    magss=0;
    bmx.write(adr);
    bmx.write(data);
    magss=1;
}
void BMX055::readnbyte_mag(char adr,char *data,char num){//numÇÕîzóÒÇÃêî
    magss=0;
    adr=adr|0b10000000;
    bmx.write(adr);
    for(int i=0;i<num;i++)data[i]=bmx.write(0xFF);
    magss=1;
}
bool BMX055::read_mag(short *mag){
    if((readbyte_mag(0x48)&0x01)==1){
    char data[8];
    readnbyte_mag(0x42,data,8);
    short buf[4];
    
    buf[0]=(data[0]>>3)|(data[1]<<5);
    if(buf[0]>0x1000)mag[0]=-1*((~buf[0]+1)&0xfff);
    else mag[0]=buf[0];
    
    buf[1]=(data[2]>>3)|(data[3]<<5);
    if(buf[1]>0x1000)mag[1]=-1*((~buf[1]+1)&0xfff);
    else mag[1]=buf[1];
    
    buf[2]=((short)data[4]>>1)|((short)data[5]<<7);
    if(buf[2]>0x4000)mag[2]=-1*((~buf[2]+1)&0x7fff);
    else mag[2]=buf[2];
    
    buf[3]=((short)data[6]>>2)|((short)data[7]<<6);
    if(buf[3]>0x2000)mag[3]=-1*((~buf[3]+1)&0x3fff);
    else mag[3]=buf[3];
    
    writebyte_mag(0x4c,0b00000010);//forced mode trigger
    
    
    return true;
    
    }else return false;
}
void BMX055::init_mag(unsigned char REPXY,unsigned char REPZ){
    magss=1;
    writebyte_mag(0x4b,0b00000001);//go sleep mode
    wait_ms(50);
    writebyte_mag(0x4b,0b10000011);//soft reset&go sleep mode
    wait_ms(50);
    
    writebyte_mag(0x51,REPXY);//set REPXY
    //1+REPXY
    wait_ms(50);
    
    writebyte_mag(0x52,REPZ);//set REPZ
    //1+REPZ 
    wait_ms(50);
    
    writebyte_mag(0x4c,0b00000010);//forced modetrigger
}



void BMX055::offset(){
    calib_acc();
    calib_gyr();
}
    