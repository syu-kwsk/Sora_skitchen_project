#include <stdio.h>
#include <time.h>
#include "mbed.h"

#define RESET 99


DigitalOut led[5] = {(p9), (LED1), (LED2), (LED3), (LED4)};
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
DigitalIn mysw1(p10);
DigitalIn mysw2(p11);
DigitalOut a[10] = {(p18), (p19), (p30), (p29), (p28), (p27), (p26), (p25), (p24), (p23)};
PwmOut mysp(p21);
AnalogIn mysen(p20);
Timer t;

void light(int light){
  led[light] = 1;
  wait(1);
  led[light] = 0;
}


void pi_sound(){
  const double PI = 1.0/960.000; 
  const double WRITE = 0.5;
  const double WAIT_SIREN = 0.65;    

  mysp.period(PI);
  mysp.write(WRITE);
  wait(WAIT_SIREN);
}
void po_sound(){
  const double PO = 1.0/770.000;
  const double WRITE = 0.5;
  const double WAIT_SIREN = 0.65;    
   
  mysp.period(PO);
  mysp.write(WRITE);
  wait(WAIT_SIREN);
}

void famima_sound(){
  const double WRITE = 0.5;  
  const double WAIT = 5.0/14.0;
  
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

  if(lv < 10){
    for(int i = 0;i <= lv;i++){
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
  const double WAVETIME = 0.02;
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

void exit(){
  t.reset();
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
  mysp.write(0);
}



int main(void){
  enum Mode{Init, Alert, Famima}; /*Init   = 初期モード
                                    Alert  = 防犯モード  
                                    Famima = コンビニモード*/
   
  enum Mode mode;//モードの種類
  
  while(true){
    static int power = 0;//電源の状態
    static int k = 0;//各モードの段階
    
    if (mysw1 == 1){
      light(1); //スイッチ１を押されて、LED1点灯
      if (power == 0){
        power++;//電源をいれて
        k++;//段階を開始して
        light(2);//LED２点灯
      }
      
      else if (power != 0){
        k = 0;//段階をリセットして
        power = 0;//電源をリセットして
        mode = Init;//モードを初期モードにして
        exit();//すべての出力を切り
        light(3);//LED3点灯             
      }
    }
    
    
    /*電源ONのとき*/
    if(power == 1){ 
    
      /*モード選択*/
      if(mysw2 == 1){
        k = 1;//段階を開始し直して
        exit();//すべての出力を切ってから
        mode = mode == Alert ? Famima : Alert;//モードを決定
        light(4);//LED４点灯
      } 
    }
 
 
 
    /*防犯モードが選択中のとき*/
    if(mode == Alert){
      
      /*センサー検出段階*/
      if(k == 1){
        if(mysen >=3.0/3.3){
          t.reset();//警戒時間をリセットして
          t.start();//警戒時間を計測して
          k++;//次の段階へ
          light(1);//LED１点灯
        }
        else {
          meter(RESET);//検出していないなら、メーターの出力をリセット
        }
      }

      /*危険度計測段階*/
      else if (k == 2){
        if(mysen >= 3.0/3.3){
          led[1] = 1;//検出中はLED１点灯
        }
        if(mysen < 3.0/3.3){
          led[1] = 0;//検出外はLED１消灯して
          t.reset();//警戒時間をリセットして
          k--;//検出段階に戻る
        }  

        for(int i = 0; i < 10; i++){
          if (t > i && t <= i + 1){
            meter(i);//１秒間ごとにメーターを上昇
          }
        }
        if(t > 10 && t <= 11){
          t.reset();//１０秒間を超えたら、警戒時間をリセットして
          meter(RESET);//メーターもリセットして
          k++;//次の段階へ
        }
      }
      
      /*警戒態勢段階*/
      else if(k == 3){
        
        for(int i = 0;i < 10;i++){
          wave(i);
        }
        pi_sound();
        for(int i = 8;i >= 0;i--){
          wave(i);
          meter(RESET);
        }   
        po_sound();
      }
      
    }//警戒モード終わり
    
    
    /*コンビニモード選択中のとき*/
    if(mode == Famima){
      
      /*検出段階*/
      if(k == 1){
        if(mysen >= 3.0/3.3){
          k++;//客が来たら、次の段階へ
          light(1);//LED１点灯
        }    
      }
          
      /*来店段階*/    
      else if(k == 2){
      
        if(mysen >= 3.0/3.3){
          famima_sound();//来店BGMを流す
        }
      
        if(mysen < 3.0/3.3){
          k--;//いなくなったら、検出段階に戻る
        }
      }
      
    }//コンビニモード終わり
 
  }//while終わり
}//main終わり
