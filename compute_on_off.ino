/**
 * @file
 * @brief Compute on/off times for a `scan_event` struct.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param se `scan_events`; Struct to hold event info.  Initially empty.
 * @param size int; The number of events in the struct.
 * @param report int; Should the struct be printed to console?
 * 
 * @return A completed `scan_events` struct.
* */

void compute_on_off(scan_events *se, int size, int report)
{
  // on starts at zero and then the other values come from off,
  // except for the last value which is not used
  se->on[0] = 0.0;
  for (int i = 1; i <= size - 1; i++)
  {
    se->on[i] = se->off[i - 1];
  }

  if (report > 1)
  {
    Serial.println("\ncompute_on_off reports:");
    report_scan_events(se, SCAN_EVENT_COUNT);
  }
}
