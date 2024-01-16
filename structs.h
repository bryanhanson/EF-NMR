
#include "user_input.h"
#include "misc_defines.h"

#ifndef STRUCTS
#define STRUCTS

/**
* @file
**/

/**
 * @brief Struct to Hold the Pulse Program
 * 
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

typedef struct pulse_program {
  /// pointers to event names (derived from `EVENT_NAMES` in `user_input.h`)
  char *event_names[SCAN_EVENT_COUNT];
  /// Arduino output pin (copied from `PIN_ASSIGNMENTS` in `user_input.h`)
  int pin[SCAN_EVENT_COUNT];
  /// event on times (computed from off times)
  float on[SCAN_EVENT_COUNT];
  /// event off times (cumulative sum of the event durations, computed from `EVENT_DURATIONS` in `user_input.h`)
  float off[SCAN_EVENT_COUNT];
};

/**
 * @brief Struct to Hold Ring Buffer Related Items
 * 
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

typedef struct ring_buffer {
  /// `rbuf`: buffer to hold ADC output
  volatile uint16_t rbuf[RB_SIZE];
  /// `writeIndx`: write index
  volatile int writeIndx;
  /// `readIndx`: read index
  volatile int readIndx;
  /// `np`: no of points to be collected. Taken from `NO_POINTS` defined in `misc_defines.h`
  volatile int np;
  /// `npc`: no of points actually collected
  volatile int npc;
  /// `nps`: no of points transmitted via the serial port
  volatile int nps;
  /// `adc_running`: is the ADC active?
  volatile boolean adc_running;
  /// `adc_done`: is the ADC collecting data?
  volatile boolean adc_done;
};

#endif