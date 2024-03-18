/**
 * @brief Compute on/off times for a `pulse_program` struct.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param pp `pulse_program`; Struct to hold the pulse program.  Initially empty.
 * @param size int; The number of events in the pulse program.
 * 
* */

void compute_on_off(pulse_program *pp, int size) {
  extern pulse_program *pp;
  
  // on starts at zero and then the other values come from off,
  // except for the last value which is not used
  pp->on[0] = 0.0;
  for (int i = 1; i <= size - 1; i++) {
    pp->on[i] = pp->off[i - 1];
  }
}
