#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define UART1_TX_PIN 17
#define UART1_RX_PIN 16
#define PASSWORD     129

BLECharacteristic *pCharacteristic;
bool navigationStarted = false;
bool navigationFinished = false;
uint8_t targetCoordCount = 0;
uint8_t receivedCoordCount = 0;

// Store up to 255 coordinates
struct Coord {
  int16_t x;
  int16_t y;
};
Coord coords[255];

// UART packet handling
static bool readingPacket = false;
static uint8_t buffer[4];
static uint8_t bytesRead = 0;

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) override {
    String value = String(pChar->getValue().c_str());
    Serial.print("Received from Python: ");
    Serial.println(value);

    if (value.startsWith("start:")) {
      targetCoordCount = value.substring(6).toInt(); // number of coords (0–255)
      if (targetCoordCount > 0 && targetCoordCount <= 255) {
        Serial.printf("Target coordinates: %d\n", targetCoordCount);
        
        // Send password (1 byte) + coordinate count (1 byte) to UART device
        Serial2.write(PASSWORD);
        Serial2.write(targetCoordCount);
        
        navigationStarted = true;
        navigationFinished = false;
        receivedCoordCount = 0;
      }
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, UART1_RX_PIN, UART1_TX_PIN);
  
  BLEDevice::init("ESP32_UART_BLE");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Ready");
  pService->start();
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();
}

void loop() {
  // Collect coordinates from UART
  if (navigationStarted && receivedCoordCount < targetCoordCount) {
    while (Serial2.available()) {
      uint8_t incomingChar = Serial2.read();

      if (!readingPacket && incomingChar == '!') {
        readingPacket = true;
        bytesRead = 0;
      } 
      else if (readingPacket) {
        buffer[bytesRead++] = incomingChar;
        if (bytesRead == 4) {
          int16_t x = (buffer[0] << 8) | buffer[1];
          int16_t y = (buffer[2] << 8) | buffer[3];
          
          coords[receivedCoordCount] = {x, y};
          Serial.printf("Stored Coord %d/%d: X=%d, Y=%d\n", 
                        receivedCoordCount + 1, targetCoordCount, x, y);

          receivedCoordCount++;
          readingPacket = false;
          bytesRead = 0;

          if (receivedCoordCount == targetCoordCount) {
            navigationFinished = true;
            navigationStarted = false;
          }
        }
      }
    }
  }

  // Once navigation is finished, send all stored coordinates
  if (navigationFinished) {
    
    Serial2.end();
    Serial.println("Navigation finished, sending all coordinates via BLE...");
    delay(50);
    for (uint8_t i = 0; i < targetCoordCount; i++) {
      uint8_t coordData[4] = {
        (uint8_t)(coords[i].x >> 8), (uint8_t)(coords[i].x & 0xFF),
        (uint8_t)(coords[i].y >> 8), (uint8_t)(coords[i].y & 0xFF)
      };
      pCharacteristic->setValue(coordData, 4);
      pCharacteristic->notify();
      delay(20); // allow BLE client to process packets
    }

    delay(1000);
    BLEDevice::deinit(true);

    Serial.println("All coordinates sent.");
    navigationFinished = false;
  }

  delay(5);
}