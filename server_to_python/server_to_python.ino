#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define UART1_TX_PIN 12
#define UART1_RX_PIN 13
#define PASSWORD     129

BLECharacteristic *pCharacteristic;
bool navigationStarted = false;
bool stopRequested = false;

// Coordinate storage
struct Coord {
  int16_t x;
  int16_t y;
};
std::vector<Coord> coordHistory;

// UART packet handling
static bool readingPacket = false;
static uint8_t buffer[4]; // X high, X low, Y high, Y low
static uint8_t bytesRead = 0;

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) override {
    String value = String(pChar->getValue().c_str());
    Serial.print("Received from Python: ");
    Serial.println(value);

    if (value == "start") {
      Serial.println("Sending password to STM32...");
      Serial1.write(PASSWORD);
      navigationStarted = true;
      stopRequested = false;
    }
    else if (value == "stop") {
      Serial.println("Stop requested from Python.");
      stopRequested = true;
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, UART1_RX_PIN, UART1_TX_PIN);
  Serial.println("UART1 initialized");

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

  Serial.println("BLE ready!");
}

void loop() {
  if (navigationStarted) {
    while (Serial1.available()) {
      char incomingChar = Serial1.read();

      if (!readingPacket) {
        if (incomingChar == '!') {
          readingPacket = true;
          bytesRead = 0;
          Serial.println("Packet start detected");
        }
      } else {
        buffer[bytesRead++] = (uint8_t)incomingChar;
        if (bytesRead == 4) {
          int16_t x = (buffer[0] << 8) | buffer[1];
          int16_t y = (buffer[2] << 8) | buffer[3];

          coordHistory.push_back({x, y});

          Serial.printf("Parsed X: %d, Y: %d\n", x, y);

          // Send acknowledgment to STM32
          if (stopRequested) {
            Serial1.write('0'); // Tell STM to stop
            navigationStarted = false; // stop receiving
            sendStoredCoordinates();
          } else {
            Serial1.write('1'); // Continue
          }

          readingPacket = false;
          bytesRead = 0;
        }
      }
    }
  }
  delay(5);
}

void sendStoredCoordinates() {
  Serial.println("Sending stored coordinates to Python...");

  for (const auto &coord : coordHistory) {
    uint8_t data[4];

    pCharacteristic->setValue(data, 4);
    pCharacteristic->notify();
    delay(20); // Small gap to prevent BLE congestion
  }

  coordHistory.clear();
  Serial.println("Coordinate dump complete.");
}
