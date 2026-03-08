//Transmitter side program implementation
##include <SPI.h>
#include <LoRa.h>

#define BUTTON_PIN 35 // Button pin
#define MIC_PIN 32 // Microphone analog pin (ADC1)
#define LORA_CS 5 // LoRa chip select
#define LORA_RST 14 // LoRa reset
#define LORA_DIO0 2 // LoRa DIO0

const int micThreshold = 1200; // Set this after observing Serial Monitor output

void setup() {
 pinMode(BUTTON_PIN, INPUT_PULLUP);
 Serial.begin(9600);

 LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);
 if (!LoRa.begin(433E6)) {
 Serial.println("LoRa init failed. Check connections.");
 while (true);
 }
 Serial.println("LoRa Transmitter Initialized");
}
void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  int micValue = analogRead(MIC_PIN); // 0-4095

  Serial.print("Button: ");
  Serial.print(buttonState == LOW ? "PRESSED" : "RELEASED");
  Serial.print(" | Mic Value: ");
  Serial.println(micValue);

  if (buttonState == LOW && micValue > micThreshold) { // AND condition
    LoRa.beginPacket();
    LoRa.print("BTN ON,");
    LoRa.print(micValue);
    LoRa.endPacket();
    Serial.print("Sent: BTN ON,"); Serial.println(micValue);
  } else {
    LoRa.beginPacket();
    LoRa.print("BTN OFF,");
    LoRa.print(micValue);
    LoRa.endPacket();
    Serial.print("Sent: BTN OFF,"); Serial.println(micValue);
  }
 delay(100); // debounce and prevent spam
}
}




}
