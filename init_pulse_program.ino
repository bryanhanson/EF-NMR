/**
 * @file
 * @brief Build a Struct Containing the Pulse Program.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

void init_pulse_program() {

  extern pulse_program *pp;

  // declare and define user provided values from user_input.h
  int size = SCAN_EVENT_COUNT;
  int report = REPORT;
  int pin[] = PIN_ASSIGNMENTS;
  float durations[] = EVENT_DURATIONS;
  char *en[] = EVENT_NAMES;

  // copy user provided inputs
  memcpy(pp->event_names, en, sizeof en);
  memcpy(pp->pin, pin, sizeof pin);
  memcpy(pp->off, durations, sizeof durations);

  if (report > 1) {
    Serial.println("durations reports:");
    report_pulse_program(pp, size);
  }

  // take the cumsum of end_time
  cumsum(pp, SCAN_EVENT_COUNT, REPORT);

  // compute on/off times
  compute_on_off(pp, SCAN_EVENT_COUNT, REPORT);

  if (report >= 1) {
    Serial.println("\nPulse program:");
    report_pulse_program(pp, size);
  }
}