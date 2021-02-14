// A simple thermostat
// © Copyright Maxim Bortnikov 2021
//For more information please visit https://github.com/Northstrix/A_simple_thermostat
#include <OneWire.h> // Include OneWire library
#include <DallasTemperature.h> // Include DallasTemperature library
#define ONE_WIRE_BUS 4 // Connect the DS18B20's DQ to pin 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int clk = 5; // connect display's clk to pin 5
int data = 6; // connect display's data to pin 6
bool a[14][4]={ //Symbols
  {1,0,1,0}, //0
  {0,0,0,1}, //1
  {0,0,1,0}, //2
  {0,0,1,1}, //3
  {0,1,0,0}, //4
  {0,1,0,1}, //5
  {0,1,1,0}, //6
  {0,1,1,1}, //7
  {1,0,0,0}, //8
  {1,0,0,1}, //9
  {1,1,1,1}, //-
  {1,0,1,1}, //F
  {1,1,1,0}, //P
  {0,0,0,0} // space
  };
void clr(){ // clear the display
  digitalWrite(data,LOW);
for(int i=0;i<40;i++){
  digitalWrite(clk,HIGH);
  delayMicroseconds(1);
  digitalWrite(clk,LOW);
  delayMicroseconds(1);
}
}
void out(int n){ // Output a symbol
  for(int j=0;j<4;j++){
  if(a[n][j]==1){
  digitalWrite(data,HIGH);}
  else{
  digitalWrite(data,LOW);}
  digitalWrite(clk,HIGH);
  delayMicroseconds(1);
  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  }
}
void setup() {
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(3, OUTPUT);
  sensors.begin();
  clr();
}

void loop() {
  sensors.requestTemperatures(); 
  clr(); // clear the display
  int n = (sensors.getTempFByIndex(0));
  int dt = (analogRead(A0)/4);
  if (dt-1 < n-1) digitalWrite(3,HIGH); // turn the heater off
  if (dt+1 > n+1) digitalWrite(3,LOW); // turn the heater on
  int n3= n%10;
  int n21 = n/10;
  int n2 = n21%10;
  int n11 = n21/10;
  int n1 = n11%10;
  if (n1 !=0) out(n1);
  if(n1 == 0 && n2 == 0){}
  else out(n2);
  out(n3);
  out(11); // Symbol "F"
  out(13);
  out(13);
  int dt3= dt%10;
  int dt21 = dt/10;
  int dt2 = dt21%10;
  int dt11 = dt21/10;
  int dt1 = dt11%10;
  if (dt1 !=0) out(dt1);
  if(dt1 == 0 && dt2 == 0){}
  else out(dt2);
  out(dt3);
  out(11); // Symbol "F"
  delay(750);
}
