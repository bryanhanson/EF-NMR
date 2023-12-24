/**
 * @file
 * @brief Acquire a Standard 1H NMR Spectrum.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void acquire_1H(pulse_program *pp, int size, int report) {
  extern pulse_program *pp;
  Serial.println("\tHello from acquire_1H!");
  if (REPORT > 1) {
    report_pulse_program(pp, size);
  }
}
