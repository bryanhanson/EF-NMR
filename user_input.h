/**
 * @brief Values the User Should Provide.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 * 
 * */

#ifndef USER_INPUT
#define USER_INPUT

#define EXPT "1H"
#define NO_SCANS 1
#define REPORT 1  // 0 = no troubleshooting; > 0 increasing levels of debug reporting
#define TIME_CONV 1 // value should convert durations below to milliseconds

#define TX_PIN 3 // transmit pin
#define POL_PIN 2 // polarization coil control pin

#define SCAN_EVENT_COUNT 6  // must match no. of entries below
// edit values between {} only!
#define EVENT_NAMES { "pol", "del1", "tx", "del2", "rx", "rd" }
#define EVENT_DURATIONS { 2000, 500, 1000, 500, 500, 1000 }
#define PIN_ASSIGNMENTS { POL_PIN, -1, TX_PIN, -1, RX_PIN, -1 }  // -1 means no pin is hot -- use for delays

#endif