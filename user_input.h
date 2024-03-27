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
#define NO_SCANS 1
/// Number of data points collected in a single scan
#define NO_POINTS 16000

/// Troubleshooting; 0 = no troubleshooting; > 0 increasing levels of debug reporting
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

/// Ring buffer capacity.
#define RB_SIZE 20
/// Baud rate; must be high to empty the ring buffer fast enough
#define BAUD_RATE 2000000
/// ADC skip rate; ADC can collect data much faster than serial port can send it.  A value of x means collect every xth point.
#define ADC_SKIP 3

#endif