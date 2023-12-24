## Bnmr = Bryan's NMR software.

This repository contains Arduino files that support my implementation of an Earth Field NMR instrument.  It is a WIP.

### Git Tagged Versions
* M1: A working version that creates a `scan_events` struct which contains all the information needed for simple pulse program.  It listens to the serial port for instructions to go or stop.  All user input is in a single file.  The 1H acquisition function is empty in this version.
* M2: This version "works" if you don't look too close: access to the global `scan_events` struct from `acquire_1H()` is corrupted (contains assorted garbage values).
* M3: Much improved working version in which the key struct is a global variable and is actually seen everywhere, due to proper use of `extern` tag.  Corrected some inconsistent variable names which were probably contributing to the corruption seen earlier.  Renamed a lot of things to be more NMR-like.

## Things to Test
* Start up message is emitted.
* Invalid `EXPT` is captured and reported.
* Different values of `REPORT` are handled appropriately.
*