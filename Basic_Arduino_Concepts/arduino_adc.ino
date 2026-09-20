/*
Arduino ADC
*/

// globals
int adcReading  = 0;
int adcLowByte  = 0;
int adcHighByte = 0;

void setup() {
  // starting up
  Serial.begin(9600);
  Serial.println("< Starting measurements... >");
  delay(1000);

  // Set registers
  
  // DIDR0 = digital input disable register 0
  // |-|-|ADC5D|ADC4D|ADC3D|ADC2D|ADC1D|ADC0D|
  DIDR0 = 0xFF; // Disable digital inputs, analog read usually does this
  
  // ADMUX = ADC multiplexer selection register 
  // |REFS1|REFS0|ADLAR|-|MUX3|MUX2|MUX1|MUX0|
  // ADLAR = analog to digital left adjust
  ADMUX = 0xC5; // 1.1V ref, Right adjust, pin A5 (MUX5)

  // ADCSRA = ADC control and status register A
  // |ADEN|ADSC|ADATE|ADIF|ADIE|ADPS2|ADPS1|ADPS0|
  ADCSRA |= (1<<ADEN); // Sets the ADEN HIGH so ADC is enabled
}

void loop() {
  // start conversion, wait until done, read it in, display it
  
  // START CONVERSION
  // setting ADSC to 1 will start a conversion
  // ADSC will drop low once conversion is done, then read 
  ADCSRA |= (1<<ADEN) | (1<<ADSC); // make sure enabled, start conversion

  // WAIT UNTIL DONE
  // while ADSC bit is high
  while (ADCSRA & (1<<ADSC)) { /*hang around till ADSC "clears"*/ }
  
  // READ IT 
  adcLowByte  = ADCL; // read low byte
  adcHighByte = ADCH;
  adcReading = (adcHighByte<<8) | (adcLowByte); // D9 D8 shift to front then combine 
  float milliVolts = adcReading * (1100.0/1023.0); // convert to millivolts 
  
  // DISPLAY IT
  Serial.println(milliVolts);
  delay(100);
}
