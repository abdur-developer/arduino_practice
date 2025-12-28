#include <SoftwareSerial.h>
#include <Servo.h>
#include <DHT.h>

/* ================= CONFIG ================= */

// Bluetooth
#define BT_RX 10
#define BT_TX 11
#define BT_BAUD 9600

// Output Pins (Relay Connected – Active LOW)
#define LED1_PIN 7
#define LED2_PIN 8
#define FAN_PIN  4
#define LEDY_PIN 5
#define BUZZER_PIN 6
#define SERVO_PIN 9

// Input Pins
#define GAS_PIN A0
#define DHT_PIN A1
#define LDR_PIN A5

// Relay Logic (IMPORTANT)
#define RELAY_ON  LOW
#define RELAY_OFF HIGH

// DHT
#define DHT_TYPE DHT11

// Thresholds
#define GAS_LIMIT 300
#define TEMP_FAN_ON 30
#define TEMP_FAN_OFF 27
#define LDR_LIMIT 160

// Servo
#define SERVO_MIN 0
#define SERVO_MAX 180

// Bluetooth Commands
#define CMD_LED1_ON  "L1_ON"
#define CMD_LED1_OFF "L1_OFF"
#define CMD_LED2_ON  "L2_ON"
#define CMD_LED2_OFF "L2_OFF"
#define CMD_FAN_ON   "FAN_ON"
#define CMD_FAN_OFF  "FAN_OFF"
#define CMD_LEDY_ON  "L3_ON"
#define CMD_LEDY_OFF "L3_OFF"
#define CMD_SERVO    "SV:"
#define TOGGLE_MODE  "M_TOGGLE"

#define LOOP_DELAY 200

/* ================= OBJECTS ================= */

SoftwareSerial BT(BT_RX, BT_TX);
Servo myServo;
DHT dht(DHT_PIN, DHT_TYPE);

/* ================= STATES ================= */

bool isAutoMode = false;

bool led1State = false;
bool led2State = false;
bool fanState  = false;
bool ledYState = false;

int servoAngle = 90;

float lastTemp = -100;
int lastGas = -1;
int lastLdr = -1;

/* ================= SETUP ================= */

void setup() {
  // ---- SAFETY FIRST (Relay OFF before pinMode) ----
  digitalWrite(LED1_PIN, RELAY_OFF);
  digitalWrite(LED2_PIN, RELAY_OFF);
  digitalWrite(FAN_PIN,  RELAY_OFF);
  digitalWrite(LEDY_PIN, RELAY_OFF);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LEDY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(GAS_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  BT.begin(BT_BAUD);
  Serial.begin(BT_BAUD);

  myServo.attach(SERVO_PIN);
  myServo.write(servoAngle);   // Safe neutral

  dht.begin();

  sendBT("SYSTEM:READY_SAFE");
}

/* ================= LOOP ================= */

void loop() {
  handleGas();
  handleTemperature();
  handleLDR();
  handleBluetooth();
  delay(LOOP_DELAY);
}

/* ================= UTIL ================= */

void sendBT(String msg) {
  BT.println(msg);
  Serial.println(msg);
}

/* ================= GAS ================= */

void handleGas() {
  int gas = analogRead(GAS_PIN);

  if (abs(gas - lastGas) > 10) {
    sendBT("GAS:" + String(gas));
    lastGas = gas;
  }

  digitalWrite(BUZZER_PIN, gas > GAS_LIMIT ? HIGH : LOW);
}

/* ================= TEMPERATURE ================= */

void handleTemperature() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) return;

  if (temp != lastTemp) {
    sendBT("TEMP:" + String(temp));
    sendBT("HUM:" + String(hum));
    lastTemp = temp;
  }

  if (isAutoMode) {
    if (temp >= TEMP_FAN_ON && !fanState) {
      fanState = true;
      digitalWrite(FAN_PIN, RELAY_ON);
      sendBT("FAN:ON_AUTO");
    }
    else if (temp <= TEMP_FAN_OFF && fanState) {
      fanState = false;
      digitalWrite(FAN_PIN, RELAY_OFF);
      sendBT("FAN:OFF_AUTO");
    }
  }
}

/* ================= LDR ================= */

void handleLDR() {
  if (!isAutoMode) return;

  int ldr = analogRead(LDR_PIN);

  if (abs(ldr - lastLdr) > 10) {
    sendBT("LDR:" + String(ldr));
    lastLdr = ldr;
  }

  bool newState = (ldr <= LDR_LIMIT);
  if (newState != ledYState) {
    ledYState = newState;
    digitalWrite(LEDY_PIN, ledYState ? RELAY_ON : RELAY_OFF);
    sendBT(String("LEDY:") + (ledYState ? "ON" : "OFF"));
  }
}

/* ================= BLUETOOTH ================= */

void handleBluetooth() {
  if (!BT.available()) return;

  String cmd = BT.readStringUntil('\n');
  cmd.trim();

  if (cmd == CMD_LED1_ON) {
    led1State = true;
    digitalWrite(LED1_PIN, RELAY_ON);
    sendBT("LED1:ON");
  }
  else if (cmd == CMD_LED1_OFF) {
    led1State = false;
    digitalWrite(LED1_PIN, RELAY_OFF);
    sendBT("LED1:OFF");
  }

  else if (cmd == CMD_LED2_ON) {
    led2State = true;
    digitalWrite(LED2_PIN, RELAY_ON);
    sendBT("LED2:ON");
  }
  else if (cmd == CMD_LED2_OFF) {
    led2State = false;
    digitalWrite(LED2_PIN, RELAY_OFF);
    sendBT("LED2:OFF");
  }

  else if (cmd == CMD_FAN_ON) {
    fanState = true;
    digitalWrite(FAN_PIN, RELAY_ON);
    sendBT("FAN:ON");
  }
  else if (cmd == CMD_FAN_OFF) {
    fanState = false;
    digitalWrite(FAN_PIN, RELAY_OFF);
    sendBT("FAN:OFF");
  }

  else if (cmd == CMD_LEDY_ON) {
    ledYState = true;
    digitalWrite(LEDY_PIN, RELAY_ON);
    sendBT("LEDY:ON");
  }
  else if (cmd == CMD_LEDY_OFF) {
    ledYState = false;
    digitalWrite(LEDY_PIN, RELAY_OFF);
    sendBT("LEDY:OFF");
  }

  else if (cmd == TOGGLE_MODE) {
    isAutoMode = !isAutoMode;
    sendBT(String("MODE:") + (isAutoMode ? "AUTO" : "MANUAL"));
  }

  else if (cmd.startsWith(CMD_SERVO)) {
    int angle = cmd.substring(3).toInt();
    angle = constrain(angle, SERVO_MIN, SERVO_MAX);

    if (angle != servoAngle) {
      servoAngle = angle;
      myServo.write(angle);
      sendBT("SERVO:" + String(angle));
    }
  }
}