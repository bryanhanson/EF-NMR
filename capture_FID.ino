/**
 * @file
 * @brief Capture the FID and Send it to the Serial Port
 *
 * Code here follows very closely the material in Dunbar 2020, Chapter 9.2
 * See the commentary there for even more details.  Also, excellent info
 * available at [Gammon's site](http://www.gammon.com.au/adc).
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @note The code here is hard-wired to use pin A0 as the analog input.
 * 
 * */

void capture_FID(pulse_program *pp, int size, ring_buffer *rb, int report) {
  extern pulse_program *pp;
  extern volatile ring_buffer *rb;
  config_ADC();
  init_ring_buffer(rb);
  Serial.println("initialized state:");
  report_ring_buffer(rb);
  start_ADC();
  if (rb->np == rb->npc) {  // all points collected, stop the ADC
    stop_ADC();
  }
}

// Helper Functions (written mostly in pure AVR C)

// ADC Configuration
void config_ADC() {
  Serial.println("Configuring the ADC...");
  // PRR &= ~(1 << PRADC);                                            // power up the ADC
  // ADCSRA |= (1 << ADEN);                                           // enable ADC
  // ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);             // slow the clock
  // ADCSRA |= (1 << ADIE);                                           // set interupt to notify data is available for further use
  // ADCSRA |= (1 << ADATE);                                          // auto-trigger on
  // ADCSRB = 0;                                                      // free-running mode
  // ADMUX = (0 << REFS1) | (1 << REFS0);                             // use 5 V internal reference
  // ADMUX &= ~(1 << ADLAR);                                          // right-align the 10 bit output in 2 byte/16 bit space
  // ADMUX |= (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);  // multiplexer input; use A0
  // DIDR0 |= (1 << ADC0D);                                           // disable digital input to pin A0
  // delay(20);                                                       // wait for voltage to settle
  //
  // The following settings taken from https://gist.github.com/edgar-bonet/0b03735d70366bc05fc6
  ADMUX = _BV(REFS0)     // ref = AVCC
          | _BV(ADLAR)   // left adjust result
          | A0;          // input channel
  ADCSRB = 0;            // free running mode
  ADCSRA = _BV(ADEN)     // enable
                         //  | _BV(ADSC)   // start conversion
           | _BV(ADATE)  // auto trigger enable
           | _BV(ADIF)   // clear interrupt flag
           | _BV(ADIE)   // interrupt enable
           | 7;          // prescaler = 128
}

// Start the ADC = start acquiring data
void start_ADC() {
  Serial.println("Starting the ADC...");
  ADCSRA |= (1 << ADSC);  // start the ADC
  // do {
  // } while (bit_is_set(ADCSRA, ADSC));  // ADSC returns to 0 when the reading is complete; this waits for first reading to settle
}

// Stop the ADC = stop acquiring data
void stop_ADC() {
  Serial.println("Stopping the ADC...");
  ADCSRA |= (0 << ADEN);
}

// Interupt Handler (ISR = interupt service routine)
// This is the most peculiar function I have run into in a sea of novelties.
// This is not called by anyone here; it must be called ISR and
// the argument name is mandatory, and the argument is not used here.
// It is apparently called each time the ADC data register is full.
ISR(ADC_vect) {
  extern volatile ring_buffer *rb;
  uint16_t ADC;
  // Serial.println("Hello from ISR");
  if (rb->np != rb->npc) {  // collect more data
    rb->npc++;
    put(rb, ADC);  // send the value to the ring buffer
    Serial.println("ADC collected a point:");
    report_ring_buffer(rb);
  }
}
