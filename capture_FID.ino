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
  int cntr = 0;  // counter for reporting ADC values; use to avoid scrolling off the right side
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
      cntr++;
      Serial.print(" ");
      Serial.print(get(rb));  // one must get the values otherwise the buffer fills quickly
      if ((cntr % 20) == 0) {
        Serial.println(" ");  // wrap the output
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
  DIDR0 |= bit(ADC0D);  // disable digital input to pin A0
  ADCSRA = 0;           // ensure defaults -- needed if ADC was on from a previous run
  ADCSRA = bit(ADEN);  // turn ADC on
  ADCSRA |= bit(ADIE);  // turn on interrupts
  ADCSRA |= bit(ADPS0) | bit(ADPS1) | bit(ADPS2);  // Clock prescaler of 128
  // These next 2 lines are needed for free-running ADC
  // ADCSRA |= bit(ADATE);  // turn on auto-trigger (needed for free-running data collection)
  // ADCSRB = 0;            // activate free-running data collection
  ADMUX = 0;             // ensure defaults
  ADMUX = bit(REFS0);    // AVcc as reference
  ADMUX |= bit(RX_PIN);  // use pin A0 (technically it is the default, but let's be explicit)
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
  ADCSRA |= bit(ADSC);  // start collecting data
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
  if (rb->np != rb->npc) {  // collect more data
    put(rb, ADC);
    rb->npc++;
    rb->adc_done = true;
  }
}

// Helped function to inspect registers as nicely formatted bytes. Modified from
// https://forum.arduino.cc/t/how-can-i-serial-println-a-binary-output-that-will-give-all-the-leading-zeros-of-a-variable/962247/2
void print_bin(byte aByte) {
  for (int8_t aBit = 7; aBit >= 0; aBit--) {
    if (aBit == 3) {
      Serial.print(" ");
    }
    Serial.print(bitRead(aByte, aBit) ? '1' : '0');
  }
  Serial.println(" ");
}