/** \defgroup ADC_Functions Functions that access the ADC **/

/**
 * @ingroup ADC_Functions
 * @brief Capture the FID and Send it to the Serial Port
 *
 * Code here follows very closely the material in Dunbar 2020, Chapter 9.2 NO LONGER TRUE
 * See the commentary there for even more details.  Also, excellent info
 * available at [Gammon's site](http://www.gammon.com.au/adc).
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 *
 * */

void capture_FID(ring_buffer *rb) {
  extern ring_buffer *rb;
  int val = 0;   // holder for ADC value
  int cntr = 0;  // counter for reporting ADC values; use to avoid scrolling off the right side
  init_ring_buffer(rb);
  config_ADC();
  start_ADC();
  Serial.println("ADC readings: ");
  while (rb->npc < rb->np) {
    val = get(rb);
    // reporting
    Serial.println(rb->npc);
    Serial.print(" ");
    Serial.print(val);
    cntr++;
    if ((cntr % 20) == 0) {
      Serial.println(" ");  // wrap the output
    }
  }
  stop_ADC();
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
void config_ADC() {
  Serial.println("Configuring the ADC...");
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
void start_ADC() {
  Serial.println("\nStarting the ADC...");
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
void stop_ADC() {
  Serial.println("\nStopping the ADC...");
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
  while (rb->npc < rb->np) {
    put(rb, ADC);
    rb->npc++;
  }
}
