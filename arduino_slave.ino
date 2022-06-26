#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 2); // TX, RX

int pinLed[] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
int check = 1;
void setup()
{
  Serial.begin(9600);
  BTSerial.begin(9600);  
  Serial.println("Enter AT commands:");
 
  for(int i=0;i<=15;i++){
    pinMode(pinLed[i],OUTPUT);
  }
  Serial.println(check);
}

// tat ca den deu tat
void chedo1()
{
   for(int i=0;i<15;i++){
    digitalWrite(pinLed[i],LOW);
  }
  delay(100);
}

// Tat ca den deu bat
void chedo2()
{
   for(int i=0;i<15;i++){
    digitalWrite(pinLed[i],HIGH);
  }
  delay(100);
}


void chedo3()
{
  for(int i=0;i<15;i++){
    digitalWrite(pinLed[i],LOW);
  }
  delay(200);
  for(int i=0;i<15;i++){
    digitalWrite(pinLed[i],HIGH);
  }
  delay(400);
}

void chedo4()
{
  digitalWrite(pinLed[7],HIGH);
//  for(int i=0;i<15;i++){
//    if (i != 7 )
//      digitalWrite(pinLed[i],LOW);
//  }
  for(int i = 14; i > 7;i--)
  {
    digitalWrite(pinLed[14-i],HIGH);
    digitalWrite(pinLed[i],HIGH);
    delay(100);
  }
  for(int i=0;i<7;i++)
  {
    digitalWrite(pinLed[14-i],LOW);
    digitalWrite(pinLed[i],LOW);
    delay(100);
  }
  for(int i = 8; i < 15;i++)
  {
    digitalWrite(pinLed[14-i],HIGH);
    digitalWrite(pinLed[i],HIGH);
    delay(100);
  }
//  for(int i = 8; i < 15;i++)
//  {
//    digitalWrite(pinLed[14-i],LOW);
//    digitalWrite(pinLed[i],LOW);
//    delay(100);
//  }
  for(int i=0;i<7;i++)
  {
    digitalWrite(pinLed[14-i],LOW);
    digitalWrite(pinLed[i],LOW);
    delay(100);
  }
  
}

void chedo5()
{
  for (int i=0 ; i < 15;i+=2)
  {
    digitalWrite(pinLed[i],HIGH);
  }
  delay(200);
  for (int i=0 ; i < 15;i+=2)
  {
    digitalWrite(pinLed[i],LOW);
  }
  delay(200);
  for (int i=1;i < 15;i+=2)
  {
    digitalWrite(pinLed[i],HIGH);
  }
  delay(200);
  for (int i=1 ; i < 15;i+=2)
  {
    digitalWrite(pinLed[i],LOW);
  } 
}

void chedo6()
{
  for(int i=0;i<=14;i++)
  {
    digitalWrite(pinLed[i],LOW);
    delay(100);
  }
  for(int i=0;i<=14;i++){
    digitalWrite(pinLed[i],HIGH);
    delay(100);
  }
   for(int i=0;i<=14;i++){
    digitalWrite(pinLed[i],LOW);
    delay(100);
  }
  for(int i=14;i>=0;i--){
    digitalWrite(pinLed[i],HIGH);
    delay(100);
  }
  for(int i=14;i>=0;i--){
    digitalWrite(pinLed[i],LOW);
    delay(100);
  }
}

void chedo7()
{
  digitalWrite(pinLed[7],HIGH);
  for(int i = 8; i < 15;i++)
  {
    digitalWrite(pinLed[14-i],HIGH);
    digitalWrite(pinLed[i],HIGH);
    delay(150);
  }
  for(int i=0;i<7;i++)
  {
    digitalWrite(pinLed[14-i],LOW);
    digitalWrite(pinLed[i],LOW);
    delay(150);
  }
}

void loop()
{
  if (BTSerial.available()>0){
    Serial.println(BTSerial.read());
  }
  
  check = BTSerial.read();
  if ( check == 1 ){
    chedo1();
  }
  else if ( check==2)
  {
    chedo2();
  }
  else if ( check==3)
  {
    chedo3();
  } else if(check==4)
  {
    chedo4();
  }else if (check==5)
  {
    chedo5();
  }else if (check==6)
  {
    chedo6();
  } else if (check==7) 
  {
    chedo7();
  }

//  // Keep reading from HC-05 and send to Arduino Serial Monitor
//  if (BTSerial.available()){
//    Serial.write(BTSerial.read());
//  }
//
//  // Keep reading from Arduino Serial Monitor and send to HC-05
//  if (Serial.available()){
//    BTSerial.write(Serial.read());
//  }
}
