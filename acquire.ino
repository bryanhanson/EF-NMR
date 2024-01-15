/**
 * @file
 * @brief Acquire NMR data
 *
 * Supervises the overall acquisition process.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void acquire(pulse_program *pp, int size, ring_buffer *rb, int report) {
  extern pulse_program *pp;
  extern ring_buffer *rb;
  if (REPORT > 1) {
    report_pulse_program(pp, size);
  }

  for (int i = 0; i < size; i++) {
    float time = (pp->off[i] - pp->on[i]) / TIME_CONV;  // CRITICAL: units here should be milliseconds
    if (pp->pin[i] == -1) { // no pin hot, simple delay
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
      // capture_FID(pp, size, rb, REPORT);
    }
  }
}
