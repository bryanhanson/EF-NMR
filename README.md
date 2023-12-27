[![Project Status: WIP – Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](https://www.repostatus.org/badges/latest/wip.svg)](https://www.repostatus.org/#wip)

## Bnmr = Bryan's NMR software.

This repository contains Arduino files that comprise the software for an Earth Field NMR instrument. For history and general updates, please consult my [blog](https://chemospec.org). Search for "EF-NMR".

### License
Released under GPL-3, help yourself *if you dare*.  After all, it is a WIP and I am new to `C` and `Arduino`.  Code here is not likely to be "ideal" for some definitions of "ideal".

### Development Standards
* Code is written in ANSI C as described in K&R, except of course for the changes that Arduino implements/requires.
* The Arduino IDE is used for development and testing.
* Use the built-in format tool in most cases.
* Doxygen is used for documentation.

### Releases
Releases are not made on any particular schedule.  Prior to a release:
* Edit the version number in `package.json`, `CHANGELOG.md`.
* Review the documentation and run `doxygen`.
* Code is tested with Arduino Uno R3 hardware.

### Things That Should be Tested Before Release
* Start up message is emitted.
* Invalid `EXPT` is captured and reported.
* Different values of `REPORT` are handled appropriately.
* 