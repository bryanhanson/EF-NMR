/**
 * @file
 * @brief Capture the FID and Send it to the Serial Port
 *
 * Code here follows very closely the material in Dunbar 2020, Chapter 9.2
 * See the commentary there for even more details.
 *
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @note The code here is hard-wired to use pin A0 as the analog input.
 * 
 * */

void capture_FID(pulse_program *pp, int size, int report) {
  extern pulse_program *pp;
  // Serial.println("\tHello from capture_FID!");

  volatile uint16_t ADC_output = 0;  // max value 65536

  config_ADC();
  start_ADC();
  for (int i = 1; i <= 5; i++) {
    Serial.print("\t\tADC = ");
    Serial.println(ADC_output);
    stop_ADC();
  }
}

// Helper Functions

// ADC Configuration
void config_ADC() {
  PRR &= ~(1 << PRADC);                                            // power up the ADC
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);             // slow the clock
  ADMUX = (0 << REFS1) | (1 << REFS0);                             // use 5 V internal reference
  ADMUX &= ~(1 << ADLAR);                                          // right-align the 10 bit output in 2 byte/16 bit space
  ADMUX |= (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);  // multiplexer input; use A0
  DIDR0 |= (1 << ADC0D);                                           // disable digital input to pin A0
  ADCSRA |= (1 << ADIE);                                           // set interupt to notify data is available for further use
  ADCSRA |= (1 << ADATE);                                          // auto-trigger on
  ADCSRB = 0;                                                      // free-running mode
  ADCSRA |= (1 << ADEN);                                           // enable ADC
  delay(20);                                                       // wait for voltage to settle
}

// Start the ADC
void start_ADC() {
  ADCSRA |= (1 << ADSC);
}

// Stop the ADC
void stop_ADC() {
  ADCSRA |= (0 << ADSC);
}

// Interupt Handler (ISR = interupt service routine)
// This is the most peculiar function I have run into in a sea of novelties.
// This is not called by anyone here; it must be called ISR and
// the argument name is mandatory, and not used here.
ISR(ADC_vect) {
  volatile uint16_t ADC_output;  // max value 65536
  ADC_output = ADCW;
}
