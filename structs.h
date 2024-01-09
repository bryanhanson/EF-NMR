/**
 * @brief Structs to Hold Various Parameters.
 * 
 * 
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

#include "user_input.h"
#include "misc_defines.h"

#ifndef STRUCTS
#define STRUCTS

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

typedef struct ring_buffer {
  /// buffer to hold ADC output
  uint16_t rbuf[RB_SIZE];
  /// write index
  int writeIndx;
  /// read index
  int readIndx;
  /// no of points to be collected
  int np;
  /// no of points actually collected
  int npc;
  /// no of points transmitted via the serial port
  int nps;
};

#endif