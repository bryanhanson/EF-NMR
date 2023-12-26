/**
 * @file
 * @brief Acquire a Standard 1H NMR Spectrum.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void acquire_1H(pulse_program *pp, int size, int report) {
  extern pulse_program *pp;
  // Serial.println("\tHello from acquire_1H!");
  if (REPORT > 1) {
    report_pulse_program(pp, size);
  }
  // this next part ignores the receive process reality until later
  for (int i = 0; i < size; i++) {
    float time = (pp->off[i] - pp->on[i]) / TIME_CONV;  // CRITICAL: units here should be milliseconds
    if (pp->pin[i] == -1) {
      delay(time); // no pin hot, just wait
    }
    if (pp->pin[i] != -1) {
      digitalWrite(pp->pin[i], HIGH);
      delay(time);
      digitalWrite(pp->pin[i], LOW);
    }
  }
}
