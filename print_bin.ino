// Helper function to inspect registers as nicely formatted bytes. Modified from
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