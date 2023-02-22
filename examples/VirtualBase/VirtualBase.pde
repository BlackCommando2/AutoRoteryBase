#include <RoteryBase.h>
RoteryBase r1;
Direction UserIn;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(5); 
  r1.enableVirtualMode();
  r1.setDirection(&UserIn);
}

void loop() {
  if(Serial.available())
  {
    UserIn.input();
  }
  r1.getFeedbackRef()->displayGraph();
  r1.compute();
}