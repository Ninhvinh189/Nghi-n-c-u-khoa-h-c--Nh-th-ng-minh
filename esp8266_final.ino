#include <ESP8266WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>


const char* ssid = "Vinh";
const char* password = "11111111";

// Biến Check các chế độ đèn
unsigned long previousMillis = 0;
unsigned long timerDelay = 5000; // will store last time LED was updated

// constants won't change :
int x = 0;
int t = 0;
String string;
String string1;
int LED = 16; // GPIO16 (D0)
int yellowLED1 = 13; // D7
int yellowLED2 = 12; // GPIO12(D6)
int yellowLED3 = 14; // D5


WiFiServer server(80);


void setup(){
  Serial.begin(115200);

  // 1 den
  pinMode(LED, OUTPUT);

  // 3 den
  pinMode(yellowLED1, OUTPUT);
  pinMode(yellowLED2, OUTPUT);;
  pinMode(yellowLED3, OUTPUT);

  // setup bus i2c
  Wire.begin(5,4);
  
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  server.begin();
  Serial.println("Server started");
  Serial.print("IP Address of network: "); // will IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop(){

  WiFiClient client = server.available();
 
  if (!client){
    return;
  }

  // Chờ cho đến khi người dùng gửi dữ liệu
  Serial.println("Waiting for new client");
  while(!client.available())
  {
    delay(1);
  }

  // Đọc request của người dùng
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
   Wire.beginTransmission(8); /* Bắt đầu với Slave có địa chỉ 8 */
   Wire.write(x);  /* gửi value của các chế độ đèn */
   Wire.endTransmission(); 

   delay(1000);

  // I2c led request
  if(request.indexOf("/chedo_on") != -1){
    x = 2;
  }
  if (request.indexOf("/chedo_off") != -1 ){
    x = 1;
  }
  if (request.indexOf("/chedo1") != -1 ){
    x = 3;
  }
  if (request.indexOf("/chedo2") != -1 ){
    x = 4;
  }
  if (request.indexOf("/chedo3") != -1 ){
    x = 5;
  }
  if (request.indexOf("/chedo4") != -1 ){
    x = 6;
  }
  if (request.indexOf("/chedo5") != -1 ){
    x = 7;
  }
  
  // Led request
  int value = LOW;
  int valueY= LOW;
  if(request.indexOf("/LED=WHITE_ON") != -1){
    
    digitalWrite(LED, HIGH); // Turn LED ON
    value = HIGH;
 
  }

  if(request.indexOf("/LED=WHITE_OFF") != -1){

    digitalWrite(LED, LOW); // Turn LED OFF
    value = LOW;
  } 

  if(request.indexOf("/LED=YELLOW_LED_ON") != -1){
    
    digitalWrite(yellowLED1, HIGH); // Turn LED ON
    digitalWrite(yellowLED2, HIGH);
    digitalWrite(yellowLED3, HIGH);
    valueY = HIGH;

  }

  if(request.indexOf("/LED=YELLOW_LED_OFF") != -1){

    digitalWrite(yellowLED1, LOW);
    digitalWrite(yellowLED2, LOW);
    digitalWrite(yellowLED3, LOW);// Turn LED OFF
    valueY = LOW;
  } 
  
//*------------------HTML Page Code---------------------*//

  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println();
  client.print(" Control 1 bulb(white bulb): ");
  if(value == LOW){
    client.print("OFF");
  }
  else
  {
    client.print("ON");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=WHITE_ON\"\"><button>ON</button></a>");
  client.println("<a href=\"/LED=WHITE_OFF\"\"><button>OFF</button></a><br />");

//  Điều khiển 3 bóng vàng.
  client.print(" Control 3 bulb(yellow bulb): ");
  if(valueY == LOW){
    client.print("OFF");
  }
  else
  {
    client.print("ON");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=YELLOW_LED_ON\"\"><button>ON</button></a><br />");
  client.println("<a href=\"/LED=YELLOW_LED_OFF\"\"><button>OFF</button></a><br />");

  // Dieu khien led i2c
  client.print("Cac che do den led nhap nhay: ");
  switch(x)
  {
    case 1:{
      client.print("OFF");
      break;
    }
    case 2:{
      client.print("ON");
      break;
    }
    case 3:{
      client.print("Che do 1");
      break;
    }
    case 4:{
      client.print("Che do 2");
      break;
    }
    case 5:{
      client.print("Che do 3");
      break;
    }
    case 6:{
      client.print("Che do 4");
      break;
    }
    case 7:{
      client.print("Che do 5");
      break;
    }
  }
  client.println("<br><br>");
  client.println("<a href=\"/chedo_on\"\"><button>ON</button></a><br />");
  client.println("<a href=\"/chedo_off\"\"><button>OFF</button></a><br />");
  client.println("<a href=\"/chedo1\"\"><button>Che do 1</button></a><br />");
  client.println("<a href=\"/chedo2\"\"><button>Che do 2</button></a><br />");
  client.println("<a href=\"/chedo3\"\"><button>Che do 3</button></a><br />");
  client.println("<a href=\"/chedo4\"\"><button>Che do 4</button></a><br />");
  client.println("<a href=\"/chedo5\"\"><button>Che do 5</button></a><br />");

  client.println("</html>");

  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
