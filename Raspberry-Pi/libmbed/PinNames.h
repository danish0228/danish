//
//  PinNames.h
//  
//
//  Created by Hiroshi TAKEMOTO on 12/10/21.
//
//

#ifndef _PinNames_h
#define _PinNames_h

#ifdef __cplusplus
extern "C" {
#endif

    //typedef enum PinName PinName;
    typedef int PinName;
    enum e_PinName {
        
        // Raspberry Pi Pin Names
        GPIO2 = 2,
        GPIO3,
        GPIO4,
        GPIO17 = 6,
        GPIO21,
	GPIO27,
	GPIO22,
        GPIO10 = 9,
        GPIO9,
        GPIO11,
        GPIO7 = 14,
        GPIO8,
        GPIO25,
        GPIO24 = 18,
        GPIO23,
        GPIO18 = 21,
        GPIO15,
        GPIO14,
        SDA = GPIO2,
        SCL = GPIO3,
        GPCLK0 = GPIO4,
        PCM_DOUT = GPIO21,
        MOSI = GPIO10,
        MISO = GPIO9,
        SCKL = GPIO11,
        CE1 = GPIO7,
        CE0 = GPIO8,
        PCM_CLK = GPIO18,
        RXD = GPIO15,
        TXD = GPIO14,

        // Raspberry Connector Pin Names
        p2 = GPIO2,
        p3 = GPIO3,
        p4 = GPIO4,
        p6 = GPIO17,
        p7 = GPIO21,
        p8 = GPIO22,
        p10 = GPIO10,
        p11 = GPIO9,
        p12 = GPIO11,
        p14 = GPIO7,
        p15 = GPIO8,
        p16 = GPIO25,
        p18 = GPIO24,
        p19 = GPIO23,
        p21 = GPIO18,
        p22 = GPIO15,
        p23 = GPIO14,
	p27 = GPIO27,

        // Not connected
        NC = (int)0xFFFFFFFF
        
    };
    
    //typedef enum PinMode PinMode;
    typedef int PinMode;
    enum e_PinMode {
        PullUp = 0
        , PullDown = 3
        , PullNone = 2
        , OpenDrain = 4
    };
    
#ifdef __cplusplus
}
#endif

#endif 
