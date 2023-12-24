/**
 * @file
 * @brief Listen to the Serial Port for Instructions.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void listen_for_instruction() {
  char instControl;

  if (Serial.available() > 0) {
    Serial.println("Arduino listening...");
    Serial.println("Enter g or s at any time");
    instControl = Serial.read();
    if (instControl == 'g') {
      start = true;
      init_scan_events();
      Serial.println("\n=====================\nLoading experiment...");
    }
    if (instControl == 's') {
      start = false;
      free(se);
      Serial.println("Stopped");
    }
  }
}
