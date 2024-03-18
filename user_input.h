/**
 * @file
 * @brief Values the User Should Provide.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 * 
 * */

#ifndef USER_INPUT
#define USER_INPUT

/// The experiment to be carried out
#define EXPT "1H"
/// The number of scans to be collected
#define NO_SCANS 2
/// 0 = no troubleshooting; > 0 increasing levels of debug reporting
#define REPORT 1
/// Factor to convert durations given here to milliseconds
#define TIME_CONV 1

/// The polarization coil control pin
#define POL_PIN 2
/// The transmit pin
#define TX_PIN 3
/// The receive pin
#define RX_PIN A0

/// The number of events in the pulse program.  Must be consistent with the next entries.
#define SCAN_EVENT_COUNT 6
/// The names of the pulse program events.  Edit values between {} only!
#define EVENT_NAMES { "pol", "del1", "tx", "del2", "rx", "rd" }
/// The duration of events in the pulse program.  Should be in milliseconds, but mind the value of `TIME_CONV`.
#define EVENT_DURATIONS { 2000, 500, 1000, 500, 500, 1000 }
/// The pins associated with each event. A value of -1 means no pin is hot -- use for delays
#define PIN_ASSIGNMENTS { POL_PIN, -1, TX_PIN, -1, RX_PIN, -1 }

/// Ring buffer capacity.  A value of 10 doesn't work, 20 seems to be fine.
#define RB_SIZE 20
/// Number of data points collected in a single scan
#define NO_POINTS 100

#endif