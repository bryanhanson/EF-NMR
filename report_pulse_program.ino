/**
 * @file
 * @brief Print the a `pulse_program` Struct to Console.  Used for troubleshooting.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright GPL-3 license
 *
 * @param pp `pulse_program`; Struct to the pulse program.
 * @param size int; The number of events in the struct.
 * @return void.  A summary of the struct is printed to the console.
 * */

void report_pulse_program(pulse_program *pp, int size) {
  extern pulse_program *pp;
  char buf[80];
  char fbuf1[10];
  char fbuf2[10];

  sprintf(buf, "event \t pin \t on \t\t off");
  Serial.println(buf);
  sprintf(buf, "----- \t --- \t -- \t\t ---");
  Serial.println(buf);

  for (int i = 0; i <= size; i++) {
    dtostrf(pp->on[i], 6, 3, fbuf1);
    dtostrf(pp->off[i], 6, 3, fbuf2);
    sprintf(buf, "%s \t % d \t %s \t %s", pp->event_names[i], pp->pin[i], fbuf1, fbuf2);
    Serial.println(buf);
  }
  Serial.println("");
}
