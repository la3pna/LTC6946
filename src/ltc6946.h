#include "arduino.h"

#ifndef LTC6946_h
#define LTC6946_h

    // includes
#include <SPI.h>


    // defines
#define statusReg     0x00
#define typeReg     0x0B

#define Reg1     0x01
#define Reg2     0x02
#define Reg3     0x03
#define Reg4     0x04
#define Reg5     0x05
#define Reg6     0x06
#define Reg7     0x07
#define Reg8     0x08
#define Reg9     0x09
#define RegA     0x0A

#define lowF    2240000000 //-1 version


class LTC6946
{
  public:
    LTC6946(void);
    init(int csPin);
    void setFreq(uint64_t frequency);
    void setRdiv(uint32_t R); //64 bits may be excessive...
    bool isLocked();
    void enable();
    void disable();
    void setNdiv(uint64_t N);
    void setOdiv(uint32_t _div);
    void writeReg(int addr, int val);
    int readReg(int addr);

    
  private:
    int _cs;
    uint32_t _R;
    int _Fpfd;
    uint64_t _N;
    int _divisor;
    uint32_t _div;
    
};

#endif
