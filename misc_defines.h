/**
 * @brief Miscellaneous Defines
 *
 * These values should not be changed by the casual user.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 * 
 * */

#ifndef MISC_DEFINES
#define MISC_DEFINES

#define RX_PIN A0 // receive pin; this is hard-wired in capture_FID, DO NOT CHANGE!  Automatic: #define A0 14;
#define RB_SIZE 6  // ring buffer capacity; only N-1 values can actually be held

#endif