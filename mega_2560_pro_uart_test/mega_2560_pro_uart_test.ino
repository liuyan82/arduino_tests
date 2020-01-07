
int SAFE_BAUD_RATE = 19200;
int FREQUENCY = 16000000;

char data_buffer[64];
int buf_head;


void resetBuffer() {
  data_buffer[0] = 0;
  buf_head = 0;
}

void setup() {
  // put your setup code here, to run once:
  unsigned int ubrr = F_CPU / 16 / SAFE_BAUD_RATE - 1;
  UBRR2H = (unsigned char) (ubrr >> 8);
  UBRR2L = (unsigned char) ubrr;

  UCSR2A = 0;

  UCSR2B = (1 << RXEN2) | (1 << TXEN2);

  UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);

  resetBuffer();

  Serial.begin(19200);
  
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  
    delay(100);
  
  if ((UCSR2A & (1 << RXC2)) != 0) {
    data_buffer[buf_head] = UDR2;
    buf_head++;
    data_buffer[buf_head] = 0;
    Serial.write(data_buffer[buf_head - 1]);

    while((UCSR2A & (1 << UDRE2)) == 0) {}
    UDR2 ='o';
  }


  if (buf_head == 62) {
    buf_head = 0;
    data_buffer[0] = 0;
 }
}
