/**
 * @file
 * @brief Listen to the Serial Port for Instructions.
 *
 * Simply sets a flag (`start`) that is monitored in the main loop/
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void listen_for_instruction() {
  char instControl;

  if (Serial.available() > 0) {
    instControl = Serial.read();
    if (instControl == 'g') {
      start = true;
      Serial.println("\n=====================\nLoading experiment...");
    }
    if (instControl == 's') {
      start = false;
      Serial.println("\nStopped");
    }
  }
}
