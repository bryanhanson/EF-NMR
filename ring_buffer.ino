/** \defgroup Ring_Buffer_Functions Functions for working with the ring buffer
* @note `get()` and `put()` modified from [Wikipedia](https://en.wikipedia.org/wiki/Circular_buffer).
**/

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Initialize the Ring Buffer
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * 
 * */

void init_ring_buffer(ring_buffer *rb) {
  extern ring_buffer *rb;
  *rb = {
    { 0 },      // zero the buffer -- the buffer itself
    0,          // write index -- writeIndx
    0,          // read index -- readIndx
    NO_POINTS,  // no of points to collect -- np
    0,          // no of times the ISR has been called -- isrcalls
    0,          // no of points collected so far -- npc
    0           // no of points sent to serial port so far -- nps
  };
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Put/Add a Value to the Ring Buffer
 * @note If one gets the "buffer is full" message that means it is not being emptied fast enough
 * -- this is a serious problem.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * @param item `int`; The value to be put in the ring buffer.
 * */

int put_rb(ring_buffer *rb, int item) {
  extern ring_buffer *rb;
  if ((rb->writeIndx + 1) % RB_SIZE == rb->readIndx) {
    Serial.println("\nring buffer is full");
    return 0;
  }
  rb->rbuf[rb->writeIndx] = item;
  rb->writeIndx = (rb->writeIndx + 1) % RB_SIZE;
  return 1;
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Get a Value from the Ring Buffer
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * 
 * */

int get_rb(ring_buffer *rb) {
  extern ring_buffer *rb;
  int value = 0;
  if (data_is_available(rb)) {
    value = rb->rbuf[rb->readIndx];
    rb->readIndx = (rb->readIndx + 1) % RB_SIZE;
    return value;
  } else {
    return 0;
  }
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Check if the Ring Buffer has Data in it
 * @note An empty buffer message is not a big deal -- it means one is emptying the buffer faster than one is filling it.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * 
 * */

int data_is_available(ring_buffer *rb) {
  extern ring_buffer *rb;
  if (rb->readIndx == rb->writeIndx) {
    // Serial.println("\nring buffer is empty");
    return 0;
  } else {
    return 1;  // buffer has data
  }
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Report the Ring Buffer Contents
 *
 * Used in development and troubleshooting only, not final `Bnmr`.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * 
 * */

void report_ring_buffer_contents(ring_buffer *rb) {
  extern ring_buffer *rb;
  int cntr = 0;  // counter for reporting buffer entries; use to avoid scrolling off the right side
  Serial.println("ring buffer contents:");
  for (int i = 0; i < RB_SIZE; i++) {
    cntr++;
    Serial.print(rb->rbuf[i]);
    Serial.print(" ");
    if ((cntr % 10) == 0) {
      Serial.println(" ");  // wrap the output
    }
  }
  Serial.print("\n\twriteIndx = ");
  Serial.println(rb->writeIndx);
  Serial.print("\treadIndx = ");
  Serial.println(rb->readIndx);
  Serial.println(" ");
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Dump Data to Serial Port
 *
 * Used in development and troubleshooting only, not final `Bnmr`.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * 
 * */

void spew_forth_data(ring_buffer *rb) {
  // spit out RB_SIZE chunks
  extern ring_buffer *rb;
  for (int i = 0; i < RB_SIZE; i++) {
    Serial.print(rb->rbuf[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Report the Ring Buffer Extra Data
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * 
 * */

void report_ring_buffer_extra_data(ring_buffer *rb) {
  extern ring_buffer *rb;
  Serial.println("ring buffer extra data:");
  Serial.print("\tnp = ");
  Serial.println(rb->np);
  Serial.print("\tnpc = ");
  Serial.println(rb->npc);
  Serial.print("\tnps = ");
  Serial.println(rb->nps);
  Serial.println(" ");
}
