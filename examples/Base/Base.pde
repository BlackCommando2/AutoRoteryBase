#include <RoteryBase.h>
RoteryBase r1;
UniversalEncoder Enc1(18, 19, -1), Enc2(26, 27, 1), Enc3(21, 22,-1);
Motor m1(32, 15 , 0), m2(23, 33, 0), m4(25, 14, 0), m3( 5, 4, 0);
void setup() {
  Serial.begin(115200);
  r1.setMotors(&m1,&m2,&m3,&m4);
  r1.setEncoders(&Enc1,&Enc2,&Enc3);
  r1.setup();
}

void loop() {
  r1.getFeedbackRef()->displayGraph();
  r1.compute();
}