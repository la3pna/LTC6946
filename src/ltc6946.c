#include "arduino.h"
#include LTC6946.h

#include "Arduino.h"
#include "LTC6946.h"

LTC6946::LTC6946(void)
{
  _R = 11; // initial condition of R =11 for 900KHz ish PFD
  }

LTC6946::init(int csPin, uint64_t reference)
{
  _cs = csPin;
  _Fpfd = reference / _R
 SPI.begin();
  pinMode(_cs, OUTPUT);
  
}

void LTC6946::setFreq(uint64_t _frequency)
{
    _divisor = (int)_lowF/_frequency; // simple floor() routine...
    _Fpfd = 
    _N = (frequency*_divisor)/_Fpfd;

       disable();
       
       setRdiv(_R);
       setNdiv(_N);
       writeReg(Reg7, 0x63); // Set ALCMON, ALCCAL, CAL, LKEN
       delay (100); //need to wait for the PLL to do frequency cal.

       writeReg(Reg8, );
       enable();
}

void LTC6946::setRdiv(uint32_t R)
{
   writeReg(Reg3,0x00); // set Bdiv and Rdiv_high to 0
   writeReg(Reg4, _R); //R register
  }
void LTC6946::setNdiv(uint64_t N)
{
       writeReg(Reg5,(_N>>8)&&0xFF); Get the high part of _N
       writeReg(Reg6, N&0xFF); //Need to & 0xFF to get 8 bits...
  }

bool LTC6946::isLocked()
{
  if(readReg(0x00)&0x04)
  {
    return true;
    }
    else
    {
      return false;
      }
}

int LTC6946::readReg(int addr)
{
  digitalWrite(_cs, LOW);
  SPI.transfer(addr<<1|0x1); 
  int answer = SPI.transfer(0x0);
  digitalWrite(_cs, HIGH);
  return answer;
}

void LTC6946::writeReg(int addr, int val)
{
    digitalWrite(_cs, LOW);
  SPI.transfer(addr<<1|0x0); 
  SPI.transfer(value);
    digitalWrite(_cs, HIGH);
}

void LTC6946::enable()
{
    writeReg(Reg2, 0x08);
}

void LTC6946::disable()
{
     writeReg(Reg2, 0x0A);
}
