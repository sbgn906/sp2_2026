#define PIN_LED 7

unsigned int count;


void setup() {
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  Serial.println("GPIO LED control start!");
  count = 0;
  digitalWrite(PIN_LED, LOW);
}


void loop() {
  Serial.println(++count);

  digitalWrite(PIN_LED, HIGH);
  delay(1000);

  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_LED, LOW);
    delay(100);

    digitalWrite(PIN_LED, HIGH);
    delay(100);
  }

  digitalWrite(PIN_LED, LOW);

  while (1) {
    ;
  }
}
