#include <stdio.h>
#include <time.h>
#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);

DigitalOut a[10] = {(p18), (p19), (p30), (p29), (p28), (p27), (p26), (p25), (p24), (p23)};

AnalogIn mysen(p20);
Timer t;


void meter(int lv){
  if(lv < 11){
    for(int i = 0;i < lv;i++){
      a[i] = 1;
    }
  }
  else if (lv > 11){
    for(int i = 0;i < 10;i++){
      a[i] = 0;
    }
  }
}

void wave(int lv){
  if(lv < 11){
    for(int i = 0;i < lv;i++){
      a[i] = 0;
    }
    a[lv] = 1;
  }
  else if (lv > 11){
    for(int i = 0;i < 10;i++){
      a[i] = 0;
    }
  }
}
    


int main(void){

  while(true){
    static int k = 0;
 
    if(k == 0){
      if(mysen >= 3.0/3.3){
        k++;
        t.start();
      }
      else {
        meter(99);
      }
    }
    
    
    else if (k == 1){
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
    else if(k == 2){
        
      for(int i = 0;i < 10;i++){
        wave(i);
        wait(0.02);
        wave(99);
      }
      for(int i = 8;i >= 0;i--){
        wave(i);
        wait(0.02);
      }
      meter(99);
    }
  }
}
