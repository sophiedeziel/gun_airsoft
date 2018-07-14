const int trigger_pin = 3;
const int cutoff_pin = 2;
const int relay_pin = 4;

int toShoot = 0;
bool enabled = true;

int debounceDelay = 50;

void setup() {
  attachInterrupt(digitalPinToInterrupt(trigger_pin), shoot, RISING);
  attachInterrupt(digitalPinToInterrupt(cutoff_pin), reenable, RISING);

  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);
}

void loop() {
  if (enabled && toShoot > 0) {
    enabled = false;
    digitalWrite(relay_pin, HIGH);
    toShoot--;
  }
  delay(debounceDelay);
}

void shoot() {
  enabled = true;
  toShoot = 2;
  detachInterrupt(digitalPinToInterrupt(trigger_pin));
  attachInterrupt(digitalPinToInterrupt(trigger_pin), reset_trigger, FALLING);
  digitalWrite(relay_pin, LOW);
}

void reenable() {
  digitalWrite(relay_pin, LOW);
  enabled = true;
}

void reset_trigger() {
  detachInterrupt(digitalPinToInterrupt(trigger_pin));
  attachInterrupt(digitalPinToInterrupt(trigger_pin), shoot, RISING);
  toShoot = 0;
  enabled = false;
  digitalWrite(relay_pin, LOW);
}

