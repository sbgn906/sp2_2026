#define PIN_LED 9

int brightness;
int fade_amount;


void setup() {
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(115200);  // Initialize serial port
  while (!Serial) {
    ;  // wait for serial port to connect.
  }

  Serial.println("LED brightness control start!");
  brightness = 0;
  fade_amount = 5;
  analogWrite(PIN_LED, brightness);  // set initial LED brightness.
}


void loop() {
  analogWrite(PIN_LED, brightness);  // update LED brightness.
  Serial.println(brightness);

  brightness = brightness + fade_amount;

  if (brightness <= 0 || brightness >= 255) {
    fade_amount = -fade_amount;  // reverse brightness direction.
  }

  delay(30);  // wait for 30 milliseconds
}
