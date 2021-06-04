#include <WiFi.h>
#include <PubSubClient.h>
#define INA1 2
#define INA2 4
#define INB1 5
#define INB2 15
#define INC1 18
#define INC2 19
#define IND1 22
#define IND2 23
// trang 1
// den 0

const int freq = 30000;
const int pwmChanneA2 = 0;
const int pwmChanneB2 = 1;
const int pwmChanneC2 = 2;
const int pwmChanneD2 = 3;

const int resolution = 8;

  const int R_S =12;  // cb dò line trái
  const int S_S =13;  // cb dò line giữa
  const int L_S =14;

  int left_sensor_state = digitalRead(L_S);
  int s_sensor_state = digitalRead(S_S);
  int right_sensor_state = digitalRead(R_S);
  int left_sensor = digitalRead(34);
  int right_sensor = digitalRead(35);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(2, OUTPUT);   //DC1
  pinMode(4, OUTPUT);  
  
  pinMode(5, OUTPUT);   //DC2
  pinMode(15,OUTPUT);   
  
  pinMode(18, OUTPUT);   //DC3
  pinMode(19,OUTPUT);
  
  pinMode(22, OUTPUT);  //DC4
  pinMode(23,OUTPUT);
  
  pinMode(21,OUTPUT); // so 1
  pinMode(25,OUTPUT); 
  pinMode(26,OUTPUT); // so 3
  pinMode(27,OUTPUT); // so 4
  pinMode(33,OUTPUT); // so 5

  pinMode(R_S, INPUT);  
  pinMode(S_S, INPUT);
  pinMode(L_S, INPUT);
  pinMode(34, INPUT);
  pinMode(35,INPUT);
  Serial.begin(9600);

    digitalWrite(21,HIGH);
    digitalWrite(26,HIGH);
    digitalWrite(27,HIGH);
    digitalWrite(33,HIGH);

  ledcSetup(pwmChanneA2, freq, resolution);
  ledcAttachPin(INA2, pwmChanneA2);

  ledcSetup(pwmChanneB2, freq, resolution);
  ledcAttachPin(INB2, pwmChanneB2);

  ledcSetup(pwmChanneC2, freq, resolution);
  ledcAttachPin(INC2, pwmChanneC2);

  ledcSetup(pwmChanneD2, freq, resolution);
  ledcAttachPin(IND2, pwmChanneD2);

    WiFi.begin("SUPERMAN", "15040301");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  client.setServer("io.adafruit.com", 1883);
  client.setCallback(callback);
  client.connect("Ngoi Nha IoT", "quanghoang27", "045c4823117e4cc291e24b4fd70dad60");
  client.subscribe("quanghoang27/feeds/myhome");
}
void callback(char* topic, byte* payload, unsigned int length) {
  if ((char)payload[0] == '1') // so 1 //trai
  {
    
    digitalWrite(21,LOW);
    digitalWrite(26,HIGH);
    digitalWrite(27,HIGH);
    digitalWrite(33,HIGH);
  }
  else if ((char)payload[0] == '0') // so 2
  {
    digitalWrite(21,HIGH);
    digitalWrite(26,HIGH);
    digitalWrite(27,HIGH);
    digitalWrite(33,HIGH);
  }
  else if ((char)payload[0] == '2') // so 3 //mid
  {
    digitalWrite(21,HIGH);
    digitalWrite(26,LOW);
    digitalWrite(27,HIGH);
    digitalWrite(33,HIGH);
  }
   else if ((char)payload[0] == '3') // so 5 //phai
  {
    digitalWrite(21,HIGH);
    digitalWrite(26,HIGH);
    digitalWrite(27,LOW);
    digitalWrite(33,HIGH);
  }
   else if ((char)payload[0] == '4') // dung yen
  {
    digitalWrite(21,HIGH);
    digitalWrite(26,HIGH);
    digitalWrite(27,HIGH);
    digitalWrite(33,LOW);
  }
  }

 
void loop() {
    
    
    client.loop();
    if((digitalRead(21)==0)&&(digitalRead(L_S) == 1)&&(digitalRead(S_S) == 0)&&(digitalRead(R_S) == 1))
    {
 
    Serial.println("Hello");
     tien();
    }
    if((digitalRead(21)==0)&&(digitalRead(L_S) == 0)&&(digitalRead(S_S) == 1)&&(digitalRead(R_S) == 1)) 
    {

      trai();
      }
      
      if((digitalRead(21)==0)&&(digitalRead(L_S) == 1)&&(digitalRead(S_S) == 1)&&(digitalRead(R_S) == 0)) 
    {

      phai();
      }

   
      

        if((digitalRead(26)==0)&&(digitalRead(L_S) == 1)&&(digitalRead(S_S) == 0)&&(digitalRead(R_S) == 1))
    {

     tien();
    }// so 1
    if((digitalRead(26)==0)&&(digitalRead(L_S) == 0)&&(digitalRead(S_S) == 1)&&(digitalRead(R_S) == 1)) 
    {

      trai();
      }
      if((digitalRead(26)==0)&&(digitalRead(L_S) == 1)&&(digitalRead(S_S) == 1)&&(digitalRead(R_S) == 0)) 
    {

      phai();
      }

        if((digitalRead(27)==0)&&(digitalRead(L_S) == 1)&&(digitalRead(S_S) == 0)&&(digitalRead(R_S) == 1))
    {

     tien();
    }// so 1
    if((digitalRead(27)==0)&&(digitalRead(L_S) == 0)&&(digitalRead(S_S) == 1)&&(digitalRead(R_S) == 1)) 
    {

      trai();
      }
      if((digitalRead(27)==0)&&(digitalRead(L_S) == 1)&&(digitalRead(S_S) == 1)&&(digitalRead(R_S) == 0)) 
    {

      phai();
      }
   
     // do line chung
     if((digitalRead(21)==0)&&(digitalRead(S_S) == 0)&&(digitalRead(L_S) == 0)&&(digitalRead(R_S) == 0)) 
    {
      dung();
      delay(1000);
      trai();
      delay(1000);
      }
         if((digitalRead(21)==0)&&(digitalRead(34) == 0)&&(digitalRead(35) == 0)&&(digitalRead(S_S) == 0)&&(digitalRead(L_S) == 1)&&(digitalRead(R_S) == 1)) 
    {
      dung();
      delay(100);
      digitalWrite(25,HIGH);
      delay(2000);
      digitalWrite(25,LOW);
      delay(2000);
      tien();
      delay(500);
      } //so 1
   if((digitalRead(27)==0)&&(digitalRead(S_S) == 0)&&(digitalRead(L_S) == 1)&&(digitalRead(R_S) == 0)) 
    {
      dung();
      delay(1000);
      phai();
      delay(500);
      }

         if((digitalRead(27)==0)&&(digitalRead(34) == 0)&&(digitalRead(35) == 0)&&(digitalRead(S_S) == 0)&&(digitalRead(L_S) == 1)&&(digitalRead(R_S) == 1)) 
    {
       dung();
      delay(100);
      digitalWrite(25,HIGH);
      delay(2000);
      digitalWrite(25,LOW);
      delay(2000);
      tien();
      delay(500);
      }
      if((digitalRead(27)==0)&&(digitalRead(34) == 0)&&(digitalRead(35) == 1)&&(digitalRead(S_S) == 1)&&(digitalRead(L_S) == 1)&&(digitalRead(R_S) == 1))
      {
        trai();
        delay(500);
        }
     // so 5
      if((digitalRead(26)==0)&&(digitalRead(S_S) == 0)&&(digitalRead(L_S) == 1)&&(digitalRead(R_S) == 0)) 
    {
    
      phai();
      delay(300);
      }
            if((digitalRead(26)==0)&&(digitalRead(34) == 0)&&(digitalRead(35) == 0)&&(digitalRead(S_S) == 0)&&(digitalRead(L_S) == 1)&&(digitalRead(R_S) == 1)) 
    {
      dung();
      delay(100);
      digitalWrite(25,HIGH);
      delay(2000);
      digitalWrite(25,LOW);
      delay(2000);
      tien();
      delay(500);
      }// so 3
    
    }// void loop
    void tien()
    {
          digitalWrite(INA1, HIGH);
    ledcWrite(pwmChanneA2, 70);
    digitalWrite(INB1, HIGH);
    ledcWrite(pwmChanneB2, 70);
    digitalWrite(INC1, HIGH);
    ledcWrite(pwmChanneC2, 70);
    digitalWrite(IND1, HIGH);
    ledcWrite(pwmChanneD2, 70);
      }
      void lui()
    {
    digitalWrite(INA1, LOW);
    ledcWrite(pwmChanneA2, 125);
    digitalWrite(INB1, LOW);
    ledcWrite(pwmChanneB2, 125);
    digitalWrite(INC1, LOW);
    ledcWrite(pwmChanneC2, 125);
    digitalWrite(IND1, LOW);
    ledcWrite(pwmChanneD2, 125);
        }
        void phai()
        {
    digitalWrite(INA1, HIGH);
    ledcWrite(pwmChanneA2,70);
    digitalWrite(INB1,LOW);
    ledcWrite(pwmChanneB2, 0);
    digitalWrite(INC1, HIGH);
    ledcWrite(pwmChanneC2, 70);
    digitalWrite(IND1, LOW);
    ledcWrite(pwmChanneD2, 0);
          }
          void trai()
          {
    digitalWrite(INA1, LOW);
    ledcWrite(pwmChanneA2, 0);
    digitalWrite(INB1, HIGH);
    ledcWrite(pwmChanneB2, 100);
    digitalWrite(INC1, LOW);
    ledcWrite(pwmChanneC2, 0);
    digitalWrite(IND1, HIGH);
    ledcWrite(pwmChanneD2, 100);
          }
          void dung()
          {
    digitalWrite(INA1, LOW);
    ledcWrite(pwmChanneA2,0);
    digitalWrite(INB1,LOW);
    ledcWrite(pwmChanneB2, 0);
    digitalWrite(INC1, LOW);
    ledcWrite(pwmChanneC2, 0);
    digitalWrite(IND1, LOW);
    ledcWrite(pwmChanneD2, 0);
            }
