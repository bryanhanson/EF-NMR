/**
 * @file
 * @brief Build a Struct Containing Scan Event Details.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @return A `scan_event` struct.
 * */

void init_scan_events()
{
  // declare and define user provided values from user_input.h
  int size = SCAN_EVENT_COUNT;
  int report = REPORT;
  int pin[] = PIN_ASSIGNMENTS;
  float durations[] = EVENT_DURATIONS;
  char *en[] = EVENT_NAMES;

  // declare and malloc the struct
  scan_events *ev = malloc(sizeof( scan_events));
  if (ev == NULL)
  {
    Serial.println("Allocation failed");
  }

  // copy user provided inputs
  memcpy(ev->event_names, en, sizeof en);
  memcpy(ev->pin, pin, sizeof pin);
  memcpy(ev->off, durations, sizeof durations);

  if (report > 1)
  {
    Serial.println("durations reports:");
    report_scan_events(ev, size);
  }

  // take the cumsum of end_time
  cumsum(ev, SCAN_EVENT_COUNT, REPORT);

  // compute on/off times
  compute_on_off(ev, SCAN_EVENT_COUNT, REPORT);

  if (report >= 1)
  {
    Serial.println("\nPulse program:");
    report_scan_events(ev, size);
  }

  // free(ev); // don't free here!  somewhere else!
}