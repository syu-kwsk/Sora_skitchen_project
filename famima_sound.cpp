#include "mbed.h"

PwmOut mysp(p22);

void famima_sound(){
#define WRITE 0.5  //
#define WAIT 5.0/14.0 //
  mysp.period(1.0/739.989); //ファ＃
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/587.330); //レ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/440.000); //ラ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/587.330); //レ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/659.255); //ミ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/880.000); //ラ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/880.000); //ラ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/659.255); //ミ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/739.989); //ファ＃
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/659.255); //ミ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/440.000); //ラ
  mysp.write(WRITE);
  wait(WAIT);
  
  mysp.period(1.0/587.330); //レ
  mysp.write(WRITE);
  wait(2*WAIT);

  mysp.write(0.0);
  
  
}



void main(){
  while(1){
    famima_sound();
  }

}
