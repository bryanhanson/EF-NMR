/**
 * @file
 * @brief Reset (Shutdown) All Pins
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void reset_pins() {
  // pins 0 and 1 are reserved for rx, tx, don't use!
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}
