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
    { 0 }, // zero the buffer
    0, // write index
    0, // read index
    NO_POINTS, // no of points to collect
    0, // no of points collected so far
    0 // no of points sent to serial port so far
  };
}

int put(ring_buffer *rb, int item) {
  extern ring_buffer *rb;
  if ((rb->writeIndx + 1) % RB_SIZE == rb->readIndx) {
    Serial.println("receiver buffer is full");
    return 0;
  }
  rb->rbuf[rb->writeIndx] = item;
  rb->writeIndx = (rb->writeIndx + 1) % RB_SIZE;
  return 1;
}

int get(ring_buffer *rb) {
  extern ring_buffer *rb;
  if (rb->readIndx == rb->writeIndx) {
    Serial.println("receiver buffer is empty");
    return 0;
  }
  rb->readIndx = (rb->readIndx + 1) % RB_SIZE;
  return 1;
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