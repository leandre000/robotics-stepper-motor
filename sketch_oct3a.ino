#include <Stepper.h>

// Define steps per revolution of your stepper motor (adjust this!)
const int stepsPerRevolution = 200;  

// Create stepper object (pins depend on your driver wiring)
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

String inputString = "";   // Store incoming serial command

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper Motor Control Ready!");
  Serial.println("Type commands like: rotate 180 degrees or rotate -270 degrees");
}

void loop() {
  // Check if serial data is available
  if (Serial.available()) {
    inputString = Serial.readStringUntil('\n'); // Read the whole line
    inputString.trim(); // Remove extra spaces

    if (inputString.startsWith("rotate")) {
      // Extract number part (angle)
      int firstSpace = inputString.indexOf(' ');
      int secondSpace = inputString.indexOf(' ', firstSpace + 1);

      String angleStr = inputString.substring(firstSpace + 1, secondSpace);
      int angle = angleStr.toInt();

      // Convert angle to steps
      long stepsToMove = (long)angle * stepsPerRevolution / 360;

      Serial.print("Rotating ");
      Serial.print(angle);
      Serial.println(" degrees...");

      // Rotate motor
      myStepper.step(stepsToMove);

      Serial.println("Done.");
    }
    else {
      Serial.println("Invalid command. Use format: rotate <angle> degrees");
    }
  }
}
