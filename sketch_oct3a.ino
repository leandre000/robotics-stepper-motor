#include <Stepper.h>

const int stepsPerRevolution = 2048;  // 28BYJ-48 with gearbox
const int in1Pin = 8;
const int in2Pin = 9;
const int in3Pin = 10;
const int in4Pin = 11;

Stepper myStepper(stepsPerRevolution, in1Pin, in3Pin, in2Pin, in4Pin);

String inputCommand = "";

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(15);  // RPM
  Serial.println("Stepper Motor Ready!");
  Serial.println("Type: rotate <angle>");
  Serial.println("Example: rotate 90  or  rotate -180");
}

void loop() {
  // Check if data is available
  if (Serial.available() > 0) {
    inputCommand = Serial.readStringUntil('\n');
    inputCommand.trim(); // remove spaces/newlines

    if (inputCommand.startsWith("rotate")) {
      int spaceIndex = inputCommand.indexOf(' ');
      if (spaceIndex > 0) {
        String angleStr = inputCommand.substring(spaceIndex + 1);
        float angle = angleStr.toFloat();

        // Convert angle to steps
        int steps = (int)(angle / 360.0 * stepsPerRevolution);

        Serial.print("Rotating ");
        Serial.print(angle);
        Serial.println(" degrees...");
        
        myStepper.step(steps);

        Serial.println("Done.");
      } else {
        Serial.println("Error: use format 'rotate <angle>'");
      }
    } else {
      Serial.println("Unknown command. Use: rotate <angle>");
    }
  }
}


//stepper motor