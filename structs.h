/**
 * @brief Struct to Hold Scan Event Parameters.
 * 
 * Struct to hold scan event parameters, basically the info needed to trigger operations on the Arduino.
 * 
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

#include "user_input.h"

#ifndef STRUCTS
#define STRUCTS

struct scan_events
{
  /// pointers to event names (derived from `EVENT_NAMES` in `user_input.h`)
  char *event_names[SCAN_EVENT_COUNT];
  /// Arduino output pin (copied from `PIN_ASSIGNMENTS` in `user_input.h`)
  int pin[SCAN_EVENT_COUNT];
  /// event on times (computed from off times)
  float on[SCAN_EVENT_COUNT];
  /// event off times (cumulative sum of the event durations, computed from `EVENT_DURATIONS` in `user_input.h`)
  float off[SCAN_EVENT_COUNT];
};

#endif