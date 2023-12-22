## Bnmr = Bryan's NMR software.

This repository contains Arduino files that support my implementation of an Earth Field NMR instrument.  It is a WIP.

### Git Tagged Versions
* M1: A working version that creates a `scan_events` struct which contains all the information needed for simple pulse program.  It listens to the serial port for instructions to go or stop.  All user input is in a single file.  The 1H acquisition function is empty in this version.
* M2: