/** \defgroup ADC_Functions Functions that access the ADC **/

/**
 * @ingroup ADC_Functions
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
 * @param pp `pulse_program`; Struct containing the pulse program.
 * @param size int; The number of events in the pulse program.
 * @param rb `ring_buffer`; Struct to hold the ADC data and related parameters.
 * @param report int; Should the pulse program be printed to console?
 *
 * */

void capture_FID(pulse_program *pp, int size, ring_buffer *rb, int report) {
  extern pulse_program *pp;
  extern ring_buffer *rb;
  int cntr = 0; // counter for reporting ADC values; use to avoid scrolling off the right side
  config_ADC();
  init_ring_buffer(rb);
  Serial.println("ADC readings: ");
  while (1) {
    if (!rb->adc_running) {
      rb->adc_running = true;
      start_ADC();
    }
    if (rb->adc_done) {
      rb->adc_running = false;
      rb->adc_done = false;
      // report_ring_buffer(rb);
      cntr++;
      Serial.print(" ");
      Serial.print(get(rb)); // one must get the values otherwise the buffer fills quickly
      if ((cntr % 20) == 0) {
        Serial.println(" "); // wrap the output
      }
      delay(250);
    }
    if (rb->np == rb->npc) {  // all points collected
      break;
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
  // ADMUX = _BV(REFS0)     // ref = AVCC
  //         | _BV(ADLAR)   // left adjust result
  //         | A0;          // input channel
  // ADCSRB = 0;            // free running mode
  // ADCSRA = _BV(ADEN)     // enable
  //                        //  | _BV(ADSC)   // start conversion
  //          | _BV(ADATE)  // auto trigger enable
  //          | _BV(ADIF)   // clear interrupt flag
  //          | _BV(ADIE)   // interrupt enable
  //          | 7;          // prescaler = 128

  // This version from N. Gammon
  ADCSRA = bit(ADEN);                              // turn ADC on
  ADCSRA |= bit(ADPS0) | bit(ADPS1) | bit(ADPS2);  // Prescaler of 128
  ADMUX = bit(REFS0) | (RX_PIN & 0x07);            // AVcc and select input port
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
  // ADCSRA |= (1 << ADSC);  // start the ADC
  ADCSRA |= bit(ADSC) | bit(ADIE);
  rb->adc_running = true;
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
  Serial.println("Stopping the ADC...");
  ADCSRA |= (0 << ADEN);
}

/**
 * @ingroup ADC_Functions
 * @brief ADC Interrupt Service Routine.
 *
 * This is the most peculiar function I have run into in a sea of novelties.
 * This is not called by anyone here; it must be called ISR and
 * the argument name is mandatory, and the argument is not used here.
 * It is apparently called each time the ADC data register is full,
 * or, if in free running mode, it is called until the ADC is turned off
 * Gammon says no Serial.x no delays inside an ISR.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * */

ISR(ADC_vect) {
  extern ring_buffer *rb;
  if (rb->np != rb->npc) {  // collect more data
    put(rb, ADC);
    rb->npc++;
    rb->adc_done = true;
  }
}
