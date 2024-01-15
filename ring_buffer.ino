/**
 * @file
 * @brief Functions for Handling the Ring Buffer
 *
 * Heavily modified and extended from [Wikipedia](https://en.wikipedia.org/wiki/Circular_buffer).
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
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
    0           // no of points sent to serial port so far
  };
}

int put(ring_buffer *rb, int item) {
  extern ring_buffer *rb;
  // if ((rb->writeIndx + 1) % RB_SIZE == rb->readIndx) {
  //   Serial.println("\nreceive buffer is full");
  //   return 0;
  // }
  rb->rbuf[rb->writeIndx] = item;
  rb->writeIndx = (rb->writeIndx + 1) % RB_SIZE;  // advance index for next time (wraps around)
  return 1;
}

// get is not currently called anywhere I can find

int get(ring_buffer *rb) {
  extern ring_buffer *rb;
  int value = 0;
  if (data_is_available(rb)) {
    value = rb->rbuf[rb->readIndx];
    rb->readIndx = (rb->readIndx + 1) % RB_SIZE;  // advance index for next time (wraps around)
    return rb->rbuf[rb->readIndx];
  } else {
    return 1;
  }
}

int data_is_available(ring_buffer *rb) {
  extern ring_buffer *rb;
  if (rb->readIndx == rb->writeIndx) {
    Serial.println("\nreceive buffer is empty");
    return 0;
  } else {
    return 1; // there is something in the buffer
  }
}

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
