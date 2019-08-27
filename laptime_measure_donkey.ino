#include <LIDARLite.h>
#include <FaBoOLED_EROLED096.h>

const int BUFSIZE = 128;
const float CROSSLINE = 150.0;
float laptimes[BUFSIZE];
int lidx;

LIDARLite lidar;
FaBoOLED_EROLED096 oled;

unsigned long prv;
float calclaptime(){
  unsigned long now = millis();
  unsigned long res = now - prv;
  prv = now;
  return res;
}

void outputToOLED(){
  oled.clear();
  for(int i = 0; i < 6; i++){
    int idx = (lidx + BUFSIZE - i) % BUFSIZE;
    oled.setCursor(0, i);
    oled.print((unsigned long)laptimes[idx]);
  }
}

void setup() {
  // put your setup code here, to run once:
  lidar.begin(0, true);
  lidar.configure(0);
  Serial.begin(115200);
  lidx = 0;

  oled.begin();
  oled.clear();
  prv = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  float dist = lidar.distance(true);
  if(dist < CROSSLINE){
    laptimes[lidx] = calclaptime();
    Serial.println(laptimes[lidx]);
    outputToOLED();
    lidx = (lidx + 1) % BUFSIZE;
    delay(2000);
  }
}
