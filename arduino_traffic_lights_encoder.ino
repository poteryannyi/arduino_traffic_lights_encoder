// traffic lights
#define s_red 13           //pin red
#define s_yellow 12        //pin yellow
#define s_green 11         //pin green

#include <EncButton.h>     //used an example from https://github.com/GyverLibs/EncButton/tree/main/examples/tickISR
EncButton<EB_TICK, 2, 3, 4> enc;   // encoder with key <A, B, KEY>

void setup() 
{ 
  pinMode(s_red,OUTPUT);     //R
  pinMode(s_yellow,OUTPUT);  //Y
  pinMode(s_green,OUTPUT);   //G
  void f_turn_off_traffic_light();  //all off
  Serial.begin(9600);
  // we connect both encoder pins to external interrupts by CHANGE
  attachInterrupt(0, isr, CHANGE);  // D2
  attachInterrupt(1, isr, CHANGE);  // D3
}

void isr() {
  enc.tickISR();  // calling the ISR tick at the interrupt
}

void f_turn_off_traffic_light(){
  // function turn off the traffic light
 digitalWrite(s_red,0);
 digitalWrite(s_yellow,0);
 digitalWrite(s_green,0);
}

void loop() 
{
  // тут тоже вызываем тик, нужен для 
  // корректной работы дебаунсов и прочих таймеров!!!
//we call the stick, it is necessary for the correct operation of de balances and other timers

  
  enc.tick();

  if (enc.turn()) {// любой поворот
    if (enc.counter > 3) {enc.counter = 3;}
    if (enc.counter < 1) {enc.counter = 1;}
    Serial.print("turn ");
    Serial.println(enc.counter);    // вывод счётчика
  }
  f_turn_off_traffic_light();   //all off
  switch (enc.counter) {
  case 1:
    digitalWrite(s_red,1);        //red on
    break;
  case 2:
    digitalWrite(s_yellow,1);     //yellow on
    break;
  case 3:
    digitalWrite(s_green,1);      //green on
    break;
  default:
      f_turn_off_traffic_light();   //all off
    break;
  }
}
