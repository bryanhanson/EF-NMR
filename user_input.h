/**
 * @brief Values the User Should Provide.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 * 
 * */

#ifndef USER_INPUT
#define USER_INPUT

#define EXPT 1  // the experiment to run: 1 = 1H
#define NO_SCANS 2
#define REPORT 1  // 0 = no troubleshooting; > 0 increasing levels of debug reporting
#define TIME_CONV 1000 // value should convert durations below to milliseconds

#define SCAN_EVENT_COUNT 6  // must match no. of entries below
// edit values between {} only!
#define EVENT_NAMES \
  { "pol", "del1", "tx", "del2", "rx", "rd" }
#define EVENT_DURATIONS \
  { 5, 1, 2, 1, 5, 1 }
#define PIN_ASSIGNMENTS \
  { 2, -1, 3, -1, 4, -1 }  // -1 means no pin is hot (delay of some type)


#endif