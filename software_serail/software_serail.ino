/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
unsigned char data[] = "Hello, world";
int data_len = 12;
int current_cursor = 0;

void setup() {
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  delay(5000);
}

void loop() { // run over and over
  delay(1000);
  
  mySerial.write(data[current_cursor % data_len]);
  current_cursor++;

  int avail = mySerial.available();
  while(avail <= 0) {
    delay(100);
    avail = mySerial.available();
  }
}
