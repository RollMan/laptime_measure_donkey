#include <LIDARLite.h>

const int BUFSIZE = 128;
const float CROSSLINE = 150.0;
float laptimes[BUFSIZE];
int lidx;
LIDARLite lidar;
unsigned long prv;
float calclaptime(){
  unsigned long now = millis();
  unsigned long res = now - prv;
  prv = now;
  return res;
}

void setup() {
  // put your setup code here, to run once:
  lidar.begin(0, true);
  lidar.configure(0);
  Serial.begin(115200);
  lidx = 0;
  prv = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  float dist = lidar.distance(true);
  if(dist < CROSSLINE){
    laptimes[lidx] = calclaptime();
    Serial.println(laptimes[lidx]);
    lidx = (lidx + 1) % BUFSIZE;
    delay(2000);
  }
}
