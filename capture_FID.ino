/** \defgroup ADC_Functions Functions that access the ADC **/

/**
 * @ingroup ADC_Functions
 * @brief Capture the FID and Send it to the Serial Port
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 *
 * */

void capture_FID(ring_buffer *rb, int report) {
  extern ring_buffer *rb;
  int val = 0;   // holder for ADC value pulled from ring buffer
  int max = 40;  // max no of values to dump to serial port before starting a new line
  init_ring_buffer(rb);
  config_ADC(REPORT);
  start_ADC(REPORT);
  do {
    if (data_is_available(rb)) {
      val = get(rb);
      // Serial.print(val);
      // Serial.print(", ");
      rb->nps++;
      // spew_forth_data(rb);
    }
    // if (rb->nps % max) {
    //   Serial.println(""); // wrap to new line
    // }
  } while ((rb->nps < rb->np));
  stop_ADC(REPORT);
  cli();
  // report_ring_buffer_contents(rb); // should this respond to REPORT?
  if (report > 1) report_ring_buffer_extra_data(rb);
}

// Helper Functions

/**
 * @ingroup ADC_Functions
 * @brief Configure the ADC
 *
 * Configures the ADC by setting the appropriate bits.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */
void config_ADC(int report) {
  if (report > 1) Serial.println("Configuring the ADC...");
  // PRR &= ~(1 << PRADC);                                            // power up the ADC
  DIDR0 |= bit(RX_PIN);                            // disable digital input
  ADCSRA = 0;                                      // ensure defaults -- needed if ADC was on from a previous run
  ADCSRA = bit(ADEN);                              // turn ADC on
  ADCSRA |= bit(ADIE);                             // turn on interrupts
  ADCSRA |= bit(ADPS0) | bit(ADPS1) | bit(ADPS2);  // Clock prescaler of 128
  // These next 2 lines set up the ADC in free-running mode
  ADCSRA |= bit(ADATE);  // turn on auto-trigger (needed for free-running data collection)
  ADCSRB = 0;            // activate free-running data collection
  ADMUX = 0;             // ensure defaults
  ADMUX = bit(REFS0);    // AVcc as reference
  ADMUX |= bit(RX_PIN);  // input pin
  sei();                 // enable interrupts gobally
  delay(20);             // allow voltage to settle
}

/**
 * @ingroup ADC_Functions
 * @brief Start the ADC
 *
 * Initiates data acquisition.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */
void start_ADC(int report) {
  if (report > 1) Serial.println("Starting the ADC...");
  ADCSRA |= bit(ADSC);  // start collecting data
}

/**
 * \ingroup ADC_Functions
 * @brief Stop the ADC
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */
void stop_ADC(int report) {
  if (report > 1) Serial.println("Stopping the ADC...");
  ADCSRA |= (0 << ADEN);
}

/**
 * @ingroup ADC_Functions
 * @brief ADC Interrupt Service Routine.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

ISR(ADC_vect) {
  extern ring_buffer *rb;
  if (rb->npc < rb->np) {
    put(rb, ADC);
    rb->npc++;
  }
}
