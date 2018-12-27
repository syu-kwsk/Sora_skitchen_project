#include<stdio.h>
#include "mbed.h"
DigitalOut a(p18);
DigitalOut b(p19);
DigitalOut c(p30);
DigitalOut d(p29);
DigitalOut e(p28);
DigitalOut f(p27);
DigitalOut g(p26);
DigitalOut h(p25);
DigitalOut i(p24);
DigitalOut j(p23);


AnalogIn mysen(p20);
DigitalOut myled(LED1);
PwmOut mysp(p22);

void meter(int lv){
  /*アレイの表示*/
  int pow = 0; 
  while(pow < lv){
    j = 1;
    pow++;
    if(pow == lv){
      break;
    }
    i = 1;
    pow++;
    if(pow == lv){
      break;
    }
    h = 1;
    pow++;
    if(pow == lv){
      break;
    }
    g = 1;
    pow++;
    if(pow == lv){
      break;
    }
    f = 1;
    pow++;
    if(pow == lv){
      break;
    }
    e = 1;
    pow++;
    if(pow == lv){
      break;
    }
    d = 1;
    pow++;
    if(pow == lv){
      break;
    }
    c = 1;
    pow++;
    if(pow == lv){
      break;
    }
    b = 1;
    pow++;
    if(pow == lv){
      break;
    }
    a = 1;
    pow++;
    if(pow == lv){
      break;
    }
  }
  /*検出音*/
  mysp.period(1.0/260);
  mysp.write(0.5);
  wait(0.2);
  mysp.write(0.0);
}


int  main(){
  int dan = 0;
  while(dan <= 10){
    /*検出時*/
    if(mysen >= 3.0/3.3){
      while(mysen >= 3.0/3.3){
        myled = 1;
      }
      myled = 0;
      dan++;
    }
    /*非検出時*/
    else if(mysen < 3.0/3.3){
      meter(0);
      
      if(dan == 1){
        meter(1);
      }
      else if(dan == 2){
        meter(2);
      }
      else if(dan == 3){
        meter(3);
      }
      else if(dan == 4){
        meter(4);
      }
      else if(dan == 5){
        meter(5);
      }
      else if(dan == 6){
        meter(6);
      }
      else if(dan == 7){
        meter(7);
      }
      else if(dan == 8){
        meter(8);
      }
      else if(dan == 9){
        meter(9);
      }
      else if(dan == 10){
        meter(10);
      }
        
    }
  }
  

  

  
}
