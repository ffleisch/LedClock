

#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN  12

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 114

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "credentials.h"

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const int segments[]={1,1,1,0,1,1,1,               
                      0,0,1,0,0,0,1,               
                      0,1,1,1,1,1,0,               
                      0,1,1,1,0,1,1,               
                      1,0,1,1,0,0,1,               
                      1,1,0,1,0,1,1,               
                      1,1,0,1,1,1,1,               
                      0,1,1,0,0,0,1,               
                      1,1,1,1,1,1,1,               
                      1,1,1,1,0,1,1,               
                      1,1,1,1,1,0,1,               
                      1,0,0,1,1,1,1,               
                      1,1,0,0,1,1,0,               
                      0,0,1,1,1,1,1,               
                      1,1,0,1,1,1,0,               
                      1,1,0,1,1,0,0,               
};

const int segmentMap[]={0,
0,0,0,1,1,1,1,
2,2,2,2,3,3,3,
3,4,4,4,4,5,5,
5,5,6,6,6,6,0,
0,0,0,1,1,1,1,
2,2,2,2,3,3,3,
3,4,4,4,4,5,5,
5,5,6,6,6,6,7,
7,0,0,0,0,1,1,
1,1,2,2,2,2,3,
3,3,3,4,4,4,4,
5,5,5,5,6,6,6,
6,0,0,0,0,1,1,
1,1,2,2,2,2,3,
3,3,3,4,4,4,4,
5,5,5,5,6,6,6,
6,};
const int digitMap[]={0,
0,0,0,0,0,0,0,
0,0,0,0,0,0,0,
0,0,0,0,0,0,0,
0,0,0,0,0,0,1,
1,1,1,1,1,1,1,
1,1,1,1,1,1,1,
1,1,1,1,1,1,1,
1,1,1,1,1,1,5,
5,2,2,2,2,2,2,
2,2,2,2,2,2,2,
2,2,2,2,2,2,2,
2,2,2,2,2,2,2,
2,3,3,3,3,3,3,
3,3,3,3,3,3,3,
3,3,3,3,3,3,3,
3,3,3,3,3,3,3,
3,};



void setSingleDigit(int digit, int val){
  
}


void setDigits(uint8_t data[],int dots,uint32_t color){
     strip.clear();
     for(int i=0;i<LED_COUNT;i++){
        int digitIndex=digitMap[i];
        int segmentIndex=segmentMap[i];
        if(digitIndex==5){
               if(dots){
                  strip.setPixelColor(i, color);  
               }
        }else{
            if(segments[data[digitIndex]*7+segmentIndex]!=0){
                strip.setPixelColor(i, color);
            }
        }

     }
     strip.show();                // Update strip with new contents
}

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);


  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600);

}



void loop() {
  timeClient.update();

  //time_t epochTime = timeClient.getEpochTime();
  //Serial.print("Epoch Time: ");
  //Serial.println(epochTime);
  
  //String formattedTime = timeClient.getFormattedTime();
  //Serial.print("Formatted Time: ");
  //Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
  
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond); 

  int dot=currentSecond%2==0?0:1;
  
  uint8_t digitData[4];
  digitData[0]=uint8_t(currentHour/10);
  digitData[1]=uint8_t(currentHour%10);
  digitData[2]=uint8_t(currentMinute/10);
  digitData[3]=uint8_t(currentMinute%10);

  int hue = (currentHour*60+currentMinute) * 65536L /(60);
  uint32_t col=strip.gamma32(strip.ColorHSV(hue));
  //uint32_t col=strip.Color(50,255,0);
  setDigits(digitData,1,col);
  
 

  //String weekDay = weekDays[timeClient.getDay()];
  //Serial.print("Week Day: ");
  //Serial.println(weekDay);    

  /*//Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

  //Print complete date:
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);

  Serial.println("");*/

  delay(1000);
}
