#include <stdio.h>
#include <time.h>
#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalIn mysw1(p10);
DigitalIn mysw2(p11);
DigitalOut a[10] = {(p18), (p19), (p30), (p29), (p28), (p27), (p26), (p25), (p24), (p23)};
PwmOut mysp(p21);
AnalogIn mysen(p20);
Timer t;



void pi_sound(){
#define PI 1.0/960.000 
#define WRITE 0.5
#define WAIT_SIREN 0.65    

  mysp.period(PI);
  mysp.write(WRITE);
  wait(WAIT_SIREN);
}
void po_sound(){
#define PO 1.0/770.000
#define WRITE 0.5
#define WAIT_SIREN 0.65    
   
  mysp.period(PO);
  mysp.write(WRITE);
  wait(WAIT_SIREN);
}

void famima_sound(){
#define WRITE 0.5  
#define WAIT 5.0/14.0
  
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
  wait(2*WAIT);
  
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

void meter(int lv){
#define RESET 99
  if(lv < 11){
    for(int i = 0;i < lv;i++){
      a[i] = 1;
    }
  }
  else if (lv == RESET){
    for(int i = 0;i < 10;i++){
      a[i] = 0;
    }
  }
}

void wave(int lv){
#define WAVETIME 0.02
#define RESET 99
  if(lv < 11){
    for(int i = 0;i < lv;i++){
      a[i] = 0;
    }
    a[lv] = 1;
    wait(WAVETIME);
  }
  else if (lv == RESET){
    for(int i = 0;i < 10;i++){
      a[i] = 0;
    }
  }  
}


int main(void){
  while(true){
    static int k = 0;
    int pow;
    if (mysw1 == 1){
      if (pow == 0){
        pow = 1;
        k++;
      }
      else if (pow == 1){
        pow = 0;
        k = 0;               
      }
    }
 
 
    if(k == 1){
      if(mysen >=3.0/3.3){
        k++;
        t.start();
      }
      else {
        meter(99);
      }
    }
    
    
    else if (k == 2){
      if(mysen >= 3.0/3.3){
        led1 = 1;
      }
      if(mysen < 3.0/3.3){
        led1 = 0;
        t.reset();
        k--;
      }  

      for(int i = 0; i < 10; i++){
        if (t > i && t <= i + 1){
          meter(i);
        }
      }
      if(t > 10 && t <= 11){
        t.reset();
        meter(99);
        k++;
      }
    }
    else if(k == 3){
        
      for(int i = 0;i < 10;i++){
        wave(i);
      }
      pi_sound();
      for(int i = 8;i >= 0;i--){
        wave(i);
        meter(99);
      }   
      po_sound();
    }

    
  
  }
}
