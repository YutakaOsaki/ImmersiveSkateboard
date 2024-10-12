#include <Wire.h>
#include <Servo.h>
Servo servo;
#define LDaddrs1 (0x70) 
byte LedDot_ok[8] = {B11111001,B10011010,B10011010,B10011100,B10011100,B10011010,B10011010,B11111001};
byte LedDot_o[8] = {B00111100,B01000010,B10000001,B10000001,B10000001,B10000001,B01000010,B00111100};
byte LedDot_left[8] = {B00001111,B00001111,B00001111,B00001111,B00001111,B00001111,B00001111,B00001111};
byte LedDot_right[8] = {B11110000,B11110000,B11110000,B11110000,B11110000,B11110000,B11110000,B11110000,};
byte LedDot_[8], LedDot[8];
//Setup led matrix and Accelerometer
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000L);
  LED_Setup( LDaddrs1, 1);
  servo.attach(10, 500, 2400);
  pinMode(10, OUTPUT);
  display_ok();
  delay(500);
}
//Detect acceleration and reflect led matrix and servo motor a time per 600ms
void loop() {
  //initialize
  servo.write(90);
  //set threshold
  float thre = -1.5;
  float ms2 = 9.80665;
  float offset_voltage = 2500.0;
  float x_0, x_1, z_0;
  float list_x[20], list_y[20];
  //create accelerations list, appending per 30ms
  for (int t = 0; t < 20; t++){
    //convert analogread into acceleration
    x_1 =  ((analogRead(A1) / 1024.0) * 5.0 * 1000 - offset_voltage) / 1000.0 * ms2;
    //subtract threshold from raw data
    list_x[t] = x_1 - thre;
    delay(30);
    //check acceleration through serial plotter
    Serial.println(x_1 - thre);
  }
  //define move forward(positive: pos) or backward(negative: neg)
  int pos = 0, neg = 0;
  for (int i = 0; i < 20; i++){
    if (abs(list_x[i]) > 1.){
    if (list_x[i] > 0){
      pos = pos + 1;
    }else if(list_x[i] < 0){
      neg = neg + 1;}
    }else{
      pos = pos + 1;
      neg = neg + 1;
    }
  }
  //reflect acceleration in led matrix and servo motor
  if (pos - neg > 7){
    display(2);
    servo_pos();
  }else if(pos - neg < -7){
    display(1);
    servo_neg();
  }else{
    display(0);
  }
}
//Setup LED
void LED_Setup(byte LD_addrs, byte on_off){
  Wire.beginTransmission(LD_addrs);
  Wire.write(0x20 | on_off);  //システムオシレータをONにする
  Wire.endTransmission();
}
//move servo motor forward
void servo_pos(){
  int d_angle = 3;
  servo.write(0);
  delay(200);
  for (int i = 1; i < 31; i++){
    servo.write(d_angle * i);
    delay(50);
  }
}
//move servo motor backward
void servo_neg(){
  int d_angle = 3;
  servo.write(180);
  delay(200);
  for (int i = 1; i < 31; i++){
    servo.write(180 - d_angle * i);
    delay(50);
  }
}
//setup display (we can see ok in the matrix)
void display_ok(){
  select_Dot(LedDot_, LedDot_ok);
  //Display
  Wire.beginTransmission(LDaddrs1);
  Wire.write(B00000000);
  for(int i = 0; i<8; i++){
    Wire.write(LedDot_[i]);
    Wire.write(0);
  }
  Wire.endTransmission();
}
//display forward or backward
void display(int dir) {
  int i,j;
  if (dir == 0){
    select_Dot(LedDot_, LedDot_o);
  }else if (dir == 1){
    select_Dot(LedDot_, LedDot_left);
  }else if (dir == 2){
    select_Dot(LedDot_, LedDot_right);
  }
  //Display
  Wire.beginTransmission(LDaddrs1);
  Wire.write(B00000000);
  for(i = 0; i<8; i++){
    Wire.write(LedDot_[i]);
    Wire.write(0);
  }
  Wire.endTransmission();
}
//convert input data into output data
void select_Dot(byte* Dot, byte* Dot_1){
  for(byte i=0; i<8; i++){
    for(byte j=0; j<7; j++){
     bitWrite(Dot[i],6-j,bitRead(Dot_1[i],j));
    }
    bitWrite(Dot[i],7,bitRead(Dot_1[i],7));  
  }
}