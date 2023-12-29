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

  for (int i = 0; i < size; i++) {
    float time = (pp->off[i] - pp->on[i]) / TIME_CONV;  // CRITICAL: units here should be milliseconds
    // delay (no pin hot)
    if (pp->pin[i] == -1) {
      delay(time);
    }
    // transmit
    if (pp->pin[i] == TX_PIN) {
      digitalWrite(pp->pin[i], HIGH);
      delay(time);
      digitalWrite(pp->pin[i], LOW);
    }
    // receive
    if (pp->pin[i] == RX_PIN) {
      capture_FID(pulse_program *pp, int size, int report);
    }
  }
}
