/**
 * @file
 * @brief Acquire a Standard 1H NMR Spectrum.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void acquire_1H(scan_events *se, int size, int report) {
  Serial.println("\tHello from acquire_1H!");
  report_scan_events(se, size);
}
