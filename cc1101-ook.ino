#include "EEPROM.h"
#include "cc1101.h"

CC1101 cc1101;

byte counter;
byte syncWord[] = {0x55, 0x55};

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting CC1101...");

  // reset the counter
  counter = 0;
  Serial.println("Initialize and set registers.");

  cc1101.init();

  cc1101.setSyncWord(syncWord, false);
  cc1101.setCarrierFreq(CFREQ_433);
  cc1101.disableAddressCheck();
  //cc1101.setTxPowerAmp(PA_LowPower);

  delay(1000);

  Serial.print("CC1101_PARTNUM ");
  Serial.println(cc1101.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_VERSION ");
  Serial.println(cc1101.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_MARCSTATE ");
  Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

  Serial.println("device initialized");
}


void send_data() {
  CCPACKET data;
  byte blinkCount = counter++;

  data.length = 13;
  data.data[0] = 0b10001110;
  data.data[1] = 0b10001110;
  data.data[2] = 0b10001110;
  data.data[3] = 0b10001110;
  data.data[4] = 0b10001110;
  data.data[5] = 0b10001110;
  data.data[6] = 0b10001110;
  data.data[7] = 0b10001110;
  data.data[8] = 0b11101110;
  data.data[9] = 0b10001000;
  data.data[10] = 0b10001000;
  data.data[11] = 0b10001000;
  data.data[12] = 0b10000000;

  if (cc1101.sendData(data)) {
    Serial.print(blinkCount, HEX);
    Serial.println(" sent ok :)");
  } else {
    Serial.println("sent failed :(");
  }
}

void loop()
{
  for (int i = 0; i <= 10; i++) {
    send_data();
    delay(10);
  }
  delay(2000);
}
