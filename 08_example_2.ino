// Arduino pin assignment
#define PIN_LED  9
#define PIN_TRIG 12   // sonar sensor TRIGGER
#define PIN_ECHO 13   // sonar sensor ECHO

// configurable parameters
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25       // sampling interval (unit: msec)
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL)     // coefficient to convert duration to distance

unsigned long last_sampling_time;   // unit: msec


void setup() {
  // initialize GPIO pins
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // sonar TRIGGER
  pinMode(PIN_ECHO, INPUT);   // sonar ECHO

  digitalWrite(PIN_TRIG, LOW);  // turn-off Sonar
  analogWrite(PIN_LED, 255);    // turn off LED (active low)

  // initialize serial port
  Serial.begin(57600);
}


void loop() {
  float distance;
  int duty;

  // wait until next sampling time.
  if ((millis() - last_sampling_time) < INTERVAL)
    return;

  // update scheduled sampling time.
  last_sampling_time += INTERVAL;

  distance = USS_measure(PIN_TRIG, PIN_ECHO);  // read distance

  // calculate LED duty value (active low)
  if ((distance == 0.0) || (distance <= 100.0) || (distance >= 300.0)) {
    duty = 255;  // LED off
  } else if (distance <= 200.0) {
    duty = (int)(255.0 * (200.0 - distance) / 100.0 + 0.5);
  } else {
    duty = (int)(255.0 * (distance - 200.0) / 100.0 + 0.5);
  }

  analogWrite(PIN_LED, duty);  // update LED brightness

  // output the distance and duty to the serial port
  Serial.print("distance:");
  Serial.print(distance);
  Serial.print(",duty:");
  Serial.println(duty);
}


// get a distance reading from USS. return value is in millimeter.
float USS_measure(int TRIG, int ECHO) {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE;  // unit: mm
}
