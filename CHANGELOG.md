# Change Log for Bnmr

## Version 0.1.1
### Misc
* Added `pacakge.json` to provide information in a more formal manner.
* Improved and expanded `README.md`.
* Added `reset_pins()` function.

## Version 0.1.0 26 Dec 2023
* First release to Github.

## Early Tagged Versions
First release to GitHub was in late December 2023.  Prior to this, important ~working local versions were tagged with "M*" with "M" representing a milestone as follows:
* M4: Slightly cleaned up version of M3.  First version to go to GitHub.
* M3: Much improved working version in which the key struct is a global variable and is actually seen everywhere, due to proper use of `extern` tag.  Corrected some inconsistent variable names which were probably contributing to the corruption seen earlier.  Renamed a lot of things to be more NMR-like.
* M2: This version "works" if you don't look too close: access to the global `scan_events` struct from `acquire_1H()` is corrupted (contains assorted garbage values).
* M1: A working version that creates a `scan_events` struct which contains all the information needed for simple pulse program.  It listens to the serial port for instructions to go or stop.  All user input is in a single file. The 1H acquisition function is empty in this version. 