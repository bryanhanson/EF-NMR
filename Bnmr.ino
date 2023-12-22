/**
 * @file
 * @brief Bryan's EF-NMR Software
 *
 * Inspired by the more complex version by Carl Michal.
 * Trying for Arduino-only control of the NMR.
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
extern struct scan_events *se;

void init();
void setup() {
  // set up code runs once at startup
  Serial.begin(9600);
  Serial.println("Arduino listening...");
  Serial.println("Enter g or s at any time");

  // turn off all pins to start
  // pins 0 and 1 are reserved for rx, tx
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  struct scan_events *se;
  // Listen for the command to go or stop (g or s)
  listen_for_instruction();

  while (start) {
    init_scan_events();
    Serial.println("Starting scans...");
    for (int i = 1; i <= NO_SCANS; i++) {
      switch (EXPT) {
        case 1:
          Serial.print("\tScan no: ");
          Serial.println(i);
          acquire_1H(se, SCAN_EVENT_COUNT, REPORT);
          break;
        default:
          Serial.println("No experiment found");
          i = NO_SCANS + 1; // interrupt if valid EXPT not found
          break;
      }
      if (i == NO_SCANS) {
        start = false;
        Serial.println("Scans complete!");
        Serial.println("Experiment complete\n====================");
        Serial.println("");
      }
      if (i > NO_SCANS) {
        start = false;
        Serial.println("Scans aborted!");
        Serial.println("");
      }
    }
  }
}
