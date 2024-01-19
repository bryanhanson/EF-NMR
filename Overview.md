
This page provides:
 
* An overview of how the `Bnmr` program is structured and operates
* How to use `Bnmr` (eventually)
* FAQ (eventually)
* Hardware notes (eventually)

## Program Structure

* Once uploaded to the board, `setup()` runs and then `loop()` listens for either a `g` for "go" or `s` for "stop".
* When a `g` is found, an experiment starts.
* The experimental parameters and pulse program found in `user_input.h` are loaded.
* A loop counts the scans; at each scan `acquire()` is called.
* The events described in the pulse program, each with a particular duration (time) and perhaps a pin to be used, are carried out in sequence.
* If the event is `rx`, pin A0 is attached to the ADC and data is collected, placed in a ring buffer, and sent up the serial port to the host computer.  This is handled by `capture_FID()`.

## How to Use Bnmr

-# Use the Arduino IDE to edit the file `user_input.h`.  That file has its own documentation about the individual paramters that should be reviewed and adjusted.
-# Use the Arduino IDE to compile and upload `Bnmr` to the board.
-# In the IDE, open the Serial Monitor.
-# Set the baud rate to 115200 in the Serial Monitor.
-# In the communication box at the top of the Serial Monitor, type `g` to start (`g` = *go*) an experiment or `s` to stop an experiment.
 
## FAQ

*coming when needed*

## Hardware Notes

*coming later*