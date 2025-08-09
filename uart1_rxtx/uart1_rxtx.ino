#define UART1_TX_PIN 12
#define UART1_RX_PIN 13

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, UART1_RX_PIN, UART1_TX_PIN);

  Serial.println("UART1 initialized with TX=12, RX=13");
}

void loop() {
  static uint8_t number = 0;

  // Send the current number over UART1
  Serial1.write(number);

  // Print the current number to Serial Monitor
  //Serial.print("Sent number: ");
  //Serial.println(number);

  // Increment and wrap number
  number++;
  if (number > 129) {
    number = 0;
  }

  // Check for incoming data on UART1 and print to Serial Monitor
  while (Serial1.available()) {
    char incomingChar = Serial1.read();
    Serial.print("Received: ");
    Serial.println(incomingChar);
  }

  //delay(500);
}

//will receive 5 byte packets that begin with "S"
//need to store them in a vector => v[0] = x1; v[1] = y1 //odd even logic
//they wil come as little endian so they need parsing