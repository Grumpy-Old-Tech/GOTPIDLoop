#include <GOTPIDLoop.h>

//-------------PID---------------- 
GOTPIDLoop pid(1000); // every 1000 milliseconds

void setup() {

  Serial.begin(9600);

  pid.setTuningParameters(2, 0, 0, false); 
  pid.setDeadband(0);
  pid.setOutputLimited(0, 100);  
  pid.reset();  
  
  pid.setpoint = 50;
  pid.processVariable = 50;

}

void loop() {

  byte character;
  if (Serial.available()) {
    character = Serial.read();
    if (character == 'q') {
      pid.processVariable += 1;
    }
    if (character == 'a') {
      pid.processVariable -= 1;
    }
  }

  Serial.print("SP:");
  Serial.print(pid.setpoint);
  Serial.print("\tPV:");
  Serial.print(pid.processVariable);

  pid.execute();

  Serial.print("\tOP:");
  Serial.println(pid.output);
}
