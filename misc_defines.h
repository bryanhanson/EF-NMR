/**
 * @file
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

/// Receive pin; this is hard-wired in `capture_FID()`, **DO NOT CHANGE!**  Elsewhere: #define A0 14
#define RX_PIN A0 // other pins defined in user_input.h -- be consistent
/// Ring buffer capacity
#define RB_SIZE 20
/// Number of data points collected in a single scan
#define NO_POINTS 50

#endif