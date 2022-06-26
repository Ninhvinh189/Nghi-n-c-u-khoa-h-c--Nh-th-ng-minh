#include <Wire.h>
#include <SoftwareSerial.h>

int obstacleLed = 12; /* led output cho cảm biến vật cản */
int obstaclePin = 11; /* chân output cho cảm biến vật cản */


SoftwareSerial BTSerial(3, 2); // TX, RX
int x=1;
int led = 13;

void setup() {

  Wire.begin(8);                /* Tham gia vao i2c với địa chỉ 8 */
  Wire.onReceive(receiveEvent); /* Nghe sự kiện */
  Serial.begin(9600);           
  pinMode(led,OUTPUT);
  BTSerial.begin(9600);

  //Cảm biến va chạm
  pinMode(obstacleLed, OUTPUT);
  pinMode(obstaclePin, INPUT);
}

void loop() {
  
  translateObstacle();
              
  // Truyền tín hiệu từ master sang slave qua bluetooth
  BTSerial.write(x);
  Serial.println(x);

    
}

// function nhận data từ master i2c
void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    x = Wire.read();      /* đọc data từ master */
  }         
}


// Function cảm biến vật cản
void translateObstacle(){
  int hasObstacle = digitalRead(obstaclePin);
  Serial.println(hasObstacle);
  if (hasObstacle == 0)
  {
    digitalWrite(obstacleLed, HIGH);
  }
  else
  {
    digitalWrite(obstacleLed, LOW);
  }
  delay(200);
}
