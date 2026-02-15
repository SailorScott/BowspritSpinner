/*
 * BowspritSpinner
 *
 * Slow rotation stepper motor controller for refinishing a bowsprit.
 * Uses YEJMKJ NEMA 17 stepper with integrated IDC1-42 driver.
 *
 * Hardware: Arduino Nano v3
 * Motor: 42BL4002-24Ypro with IDC1-42 driver
 */

// Pin definitions - Outputs
#define PIN_PULSE     9   // PU- on driver
#define PIN_DIR       8   // DR- on driver
#define PIN_LED      13   // Built-in LED (running indicator)

// Pin definitions - Inputs
#define PIN_FASTER    2   // Speed up button (INPUT_PULLUP)
#define PIN_SLOWER    3   // Speed down button (INPUT_PULLUP)

// Motor configuration
#define STEPS_PER_REV 200   // Set via DIP switches (SW2=on, SW3=on, SW4=on)
#define BELT_RATIO    3     // 3:1 belt drive (motor:bowsprit)

// Speed settings (RPM)
#define RPM_MIN       0
#define RPM_MAX       10
#define RPM_DEFAULT   0     // Start stopped
#define RPM_STEP      1

// Current speed
int currentRPM = RPM_DEFAULT;
unsigned long pulseIntervalUs;

// Button debounce
unsigned long lastButtonTime = 0;
#define DEBOUNCE_MS 200

// Direction: true = CW, false = CCW
bool direction = true;

// LED blink state
int pulseCount = 0;
bool ledState = false;

// Serial reporting
unsigned long lastReportTime = 0;
#define REPORT_INTERVAL_MS 10000

void calculatePulseInterval() {
  if (currentRPM == 0) {
    pulseIntervalUs = 0;
    return;
  }
  // Motor RPM = bowsprit RPM * belt ratio
  // pulse_interval = 60,000,000 / (STEPS_PER_REV * motor_RPM)
  unsigned long motorRPM = (unsigned long)currentRPM * BELT_RATIO;
  pulseIntervalUs = 60000000UL / ((unsigned long)STEPS_PER_REV * motorRPM);
}

void setup() {
  Serial.begin(9600);
  Serial.println("BowspritSpinner starting...");
  Serial.print("Steps/rev: ");
  Serial.println(STEPS_PER_REV);

  // Configure output pins
  pinMode(PIN_PULSE, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  // Configure input pins with internal pullups
  pinMode(PIN_FASTER, INPUT_PULLUP);
  pinMode(PIN_SLOWER, INPUT_PULLUP);

  // Set initial direction
  digitalWrite(PIN_DIR, direction ? HIGH : LOW);
  delayMicroseconds(100);  // Allow direction to settle

  // Calculate initial pulse interval
  calculatePulseInterval();

  Serial.print("RPM: ");
  Serial.println(currentRPM);
  Serial.print("Pulse interval: ");
  Serial.print(pulseIntervalUs);
  Serial.println(" us");
  Serial.println("Motor running...");
}

void loop() {
  // Check speed buttons
  if (millis() - lastButtonTime > DEBOUNCE_MS) {
    if (digitalRead(PIN_FASTER) == LOW) {
      if (currentRPM < RPM_MAX) {
        currentRPM += RPM_STEP;
        calculatePulseInterval();
        Serial.print("RPM: ");
        Serial.println(currentRPM);
      }
      lastButtonTime = millis();
    }
    else if (digitalRead(PIN_SLOWER) == LOW) {
      if (currentRPM > RPM_MIN) {
        currentRPM -= RPM_STEP;
        calculatePulseInterval();
        Serial.print("RPM: ");
        Serial.println(currentRPM);
      }
      lastButtonTime = millis();
    }
  }

  // Only pulse if running
  if (currentRPM > 0) {
    // Generate pulse - rising edge triggers step
    digitalWrite(PIN_PULSE, HIGH);
    delayMicroseconds(10);  // Pulse width > 2.5us per spec
    digitalWrite(PIN_PULSE, LOW);

    // Blink LED every 100 pulses
    pulseCount++;
    if (pulseCount >= 100) {
      pulseCount = 0;
      ledState = !ledState;
      digitalWrite(PIN_LED, ledState);
    }

    // Wait for next step
    delayMicroseconds(pulseIntervalUs - 10);
  } else {
    digitalWrite(PIN_LED, LOW);  // LED off when stopped
    delay(10);  // Idle delay when stopped
  }

  // Report current speed every 10 seconds
  if (millis() - lastReportTime >= REPORT_INTERVAL_MS) {
    lastReportTime = millis();
    Serial.print("Current RPM: ");
    Serial.println(currentRPM);
  }
}
