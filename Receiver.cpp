//Receiver side program implementation
#include <SPI.h>
#include <LoRa.h>

#define LED_PIN     22    // LED pin
#define LORA_CS     5     // LoRa chip select
#define LORA_RST    14    // LoRa reset
#define LORA_DIO0   2     // LoRa DIO0

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections.");
    while (true);
  }
  Serial.println("LoRa Receiver Initialized");
}

}
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String rxMsg = "";
    while (LoRa.available()) {
      rxMsg += (char)LoRa.read();
    }
    rxMsg.trim();
    Serial.print("Received: ");
    Serial.println(rxMsg);

    if (rxMsg.startsWith("BTN ON")) {
      digitalWrite(LED_PIN, HIGH);
    } else if (rxMsg.startsWith("BTN OFF")) {
      digitalWrite(LED_PIN, LOW);
    }

    // If needed, extract mic value for further processing
    int commaIndex = rxMsg.indexOf(',');
    if (commaIndex > 0) {
      int micValue = rxMsg.substring(commaIndex + 1).toInt();
      Serial.print("Mic Value: ");
      Serial.println(micValue);
    }
    }

