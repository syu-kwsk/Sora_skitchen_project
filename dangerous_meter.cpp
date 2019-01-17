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
}

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


void siren_sound(){
#define PI 1.0/960.000 
#define PO 1.0/770.000
#define WRITE 0.5
#define WAIT 0.65    

    mysp.period(PI);
    mysp.write(WRITE);
    wait(WAIT);
    
    mysp.period(PO);
    mysp.write(WRITE);
    wait(WAIT);
    
}


int  main(){
int dan = 0;
DigitalIn mysw(p10);
  /*スイッチ入力*/
  
  
  
  
  
  
  
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
    while(dan > 10){
        if (mysw == 1){
            famima_sound();
            }
        else if(mysw == 0){
            siren_sound();
            }
        
        }
    
  }
  

  

  
}
