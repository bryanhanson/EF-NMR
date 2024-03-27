/**
 * @brief Bryan's EF-NMR Software
 *
 * Inspired by the more complex version by Carl Michal, but built from scratch, with all its own warts.
 * Trying for Arduino-only control of the NMR.
 *
 * Overall Flow of the Program
 *   * Coming later...
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "user_input.h"

/// `start` A boolean which is monitored and modifed by `listen_for_instruction` and passed to `loop`
boolean start = false;
/// `pulse_program` The *address* of a struct holding the pulse program events. This is passed around and accessed by many functions.
pulse_program *pp = malloc(sizeof(pulse_program));
/// `ring_buffer` The *address* of a struct holding the ring buffer and related parameters. Used by `capture_FID()`.
ring_buffer *rb = malloc(sizeof(ring_buffer));

void setup() {
  // set up code runs once at startup
  extern pulse_program *pp;
  extern ring_buffer *rb;

  // setup comms
  Serial.begin(BAUD_RATE);
  if (Serial) {
    Serial.println("Arduino listening...");
    Serial.println("Enter g or s at any time");
  }

  // verify memory is available
  if ((pp == NULL) | (rb == NULL)) {
    Serial.println("Allocation failed");
  }

  // turn off all pins to start
  reset_pins();

  // check for a valid experiment
  if (strcmp(EXPT, "1H") != 0) {
    start = false;
    free(pp);
    free(rb);
    reset_pins();
    Serial.println("Invalid experiment, scans aborted!\n==================================");
    Serial.println("");
  }
}

void loop() {
  extern boolean start;
  extern pulse_program *pp;
  extern ring_buffer *rb;

  // Listen continuously for the command to go or stop (g or s)
  listen_for_instruction();

  // if loop runs one experiment with NO_SCANS scans, then stops, leaving the main loop simply listening for g or s
  if (start) {

    init_pulse_program(REPORT);  // get a fresh pulse program each time we "go"
    Serial.println("Starting scans...");
    for (int i = 1; i <= NO_SCANS; i++) {
      if (strcmp(EXPT, "1H") == 0) {
        Serial.print("\n\tScan no: ");
        Serial.println(i);
        acquire(pp, SCAN_EVENT_COUNT, rb, REPORT);
        listen_for_instruction();
        if (!start) {
          break;
        }
      }
      if (i == NO_SCANS) {
        Serial.println("\nScans complete!");
        Serial.println("Experiment complete, stopping...\n================================");
        Serial.println("");
        start = false;
        free(pp);
        free(rb);
        reset_pins();
      }
    }
  }
}
