/**
 * @file
 * @brief Bryan's EF-NMR Software
 *
 * Inspired by the more complex version by Carl Michal, but built from scratch, with all its own warts.
 * Trying for Arduino-only control of the NMR.
 *
 * There are two global variables that are important to understand:
 *   * `start` A boolean which is monitored and modifed by `listen_for_instruction` and passed to `loop`.
 *   * `pulse_program` The *address* of a struct holding the pulse program events. This is passed around and accessed by many functions. 
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

// global variables
boolean start = false;
pulse_program *pp = malloc(sizeof(pulse_program));


void init();
void setup() {
  // set up code runs once at startup
  Serial.begin(9600);
  if (Serial) {
    Serial.println("Arduino listening...");
    Serial.println("Enter g or s at any time");
  }
  // turn off all pins to start
  // pins 0 and 1 are reserved for rx, tx
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  if (pp == NULL) {
    Serial.println("Allocation failed");
  }
}

void loop() {

  // Listen continuously for the command to go or stop (g or s)
  listen_for_instruction();

  // while loop runs one experiment with NO_SCANS scans, then stops, leaving the main loop simply listening for g or s
  while (start) {
    init_pulse_program();  // get a fresh pulse program each time we "go"
    Serial.println("Starting scans...");
    for (int i = 1; i <= NO_SCANS; i++) {
      switch (EXPT) {
        case 1:
          Serial.print("\tScan no: ");
          Serial.println(i);
          acquire_1H(pp, SCAN_EVENT_COUNT, REPORT);
          break;
        default:
          Serial.println("No experiment found");
          i = NO_SCANS + 1;  // interrupt if valid EXPT not found
          break;
      }
      if (i == NO_SCANS) {
        start = false;
        free(pp);
        Serial.println("Scans complete!");
        Serial.println("Experiment complete, stopping...\n================================");
        Serial.println("");
      }
      if (i > NO_SCANS) {
        start = false;
        free(pp);
        Serial.println("Scans aborted!");
        Serial.println("");
      }
    }
  }
}
