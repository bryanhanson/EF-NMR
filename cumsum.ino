/**
 * @brief Compute the Cumulative Sum of the `end_time` member in a `pulse_program` Struct.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param pp `pulse_program`; Struct to hold the pulse program. `end_time` is updated to the cumulative sums.
 * @param size int; The number of events in the struct.
 * @param report int; Should the struct be printed to console?
 * 
 * */

void cumsum(pulse_program *pp, int size, int report) {
  extern pulse_program *pp;

  // leaving pp.end_time[0] unchanged, hence i starts at 1
  for (int i = 1; i < size; i++) {
    pp->off[i] = pp->off[i] + pp->off[i - 1];
  }

  if (report > 1) {
    Serial.println("\ncumsum reports:");
    report_pulse_program(pp, SCAN_EVENT_COUNT);
  }
}
