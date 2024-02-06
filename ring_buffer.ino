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
    0,          // no of points collected so far -- npc
    0           // no of points sent to serial port so far -- nps
  };
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Put/Add a Value to the Ring Buffer
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * @param item `int`; The value to be put in the ring buffer.
 * */

int put(ring_buffer *rb, int item) {
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

int get(ring_buffer *rb) {
  extern ring_buffer *rb;
  int value = 0;
  if (data_is_available(rb)) {
    value = rb->rbuf[rb->readIndx];
    rb->readIndx = (rb->readIndx + 1) % RB_SIZE;
    return value;
  } else {
    return 1;  // should this be zero?
  }
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Check if the Ring Buffer has Data in it
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
    Serial.println("\nring buffer is empty");
    return 0;
  } else {
    return 1;  // buffer has data
  }
}

/**
 * @ingroup Ring_Buffer_Functions
 * @brief Report the Ring Buffer Status
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * 
 * */

void report_ring_buffer(ring_buffer *rb) {
  extern ring_buffer *rb;
  int cntr = 0;  // counter for reporting buffer entries; use to avoid scrolling off the right side
  Serial.println("ring buffer:");
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
  Serial.print("\tnp = ");
  Serial.println(rb->np);
  Serial.print("\tnpc = ");
  Serial.println(rb->npc);
  Serial.print("\tnps = ");
  Serial.println(rb->nps);
  Serial.println(" ");
}
