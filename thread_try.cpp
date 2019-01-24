#include "mbed.h"
#include "rtos.h"
#define RESET 99

DigitalOut led[5] = {(p9), (LED1), (LED2), (LED3), (LED4)};
DigitalIn mysw1(p10);
DigitalIn mysw2(p11);
DigitalOut a[10] = {(p18), (p19), (p30), (p29), (p28), (p27), (p26), (p25), (p24), (p23)};
PwmOut mysp(p21);

DigitalOut led1(LED1);
DigitalOut led2(LED2);

void light(int light){
  led[light] = 1;
  wait(1);
  led[light] = 0;
}

void exit(){

  led[1] = 0;
  led[2] = 0;
  led[3] = 0;
  led[4] = 0;
  a[0] = 0;
  a[1] = 0;
  a[2] = 0;
  a[3] = 0;
  a[4] = 0;
  a[5] = 0;
  a[6] = 0;
  a[7] = 0;
  a[8] = 0;
  a[9] = 0;  

}


 
    
void wave(void const *argument){
  const double WAVETIME = 0.02;
  
  for(int lv = 0;lv < 10;lv++){
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

}


int main() {
  while(1){
       
    if(mysw1 == 1){ 
      Thread thread(wave);
      light(1);

    }
    else{
      exit();
    }
    
  }

}
