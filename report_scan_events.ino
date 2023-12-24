/**
 * @file
 * @brief Print the Entries in a `scan_events` Struct to Console.  Used for troubleshooting.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright GPL-3 license
 *
 * @param se `scan_events`; Struct to hold event info.
 * @param size int; The number of events in the struct.
 * @return void.  A summary of the struct is printed to the console.
 * */

void report_scan_events(struct scan_events *se, int size) {
  char buf[80];
  char fbuf1[10];
  char fbuf2[10];

  sprintf(buf, "event \t pin \t on \t\t off");
  Serial.println(buf);
  sprintf(buf, "----- \t --- \t -- \t\t ---");
  Serial.println(buf);

  for (int i = 0; i <= size; i++) {
    dtostrf(se->on[i], 6, 3, fbuf1);
    dtostrf(se->off[i], 6, 3, fbuf2);
    sprintf(buf, "%s \t % d \t %s \t %s", se->event_names[i], se->pin[i], fbuf1, fbuf2);
    Serial.println(buf);
  }
  Serial.println("");
}
