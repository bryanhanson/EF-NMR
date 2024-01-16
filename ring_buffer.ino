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
    { 0 },      // zero the buffer
    0,          // write index
    0,          // read index
    NO_POINTS,  // no of points to collect
    0,          // no of points collected so far
    0,          // no of points sent to serial port so far
    false,      // is adc_running?
    false       // is adc_done?
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
    return 1; // should this be zero?
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
  Serial.println("ring buffer:");
  for (int i = 0; i < RB_SIZE; i++) {
    Serial.print(rb->rbuf[i]);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("\twriteIndx = ");
  Serial.println(rb->writeIndx);
  Serial.print("\treadIndx = ");
  Serial.println(rb->readIndx);
  Serial.println(" ");
}
