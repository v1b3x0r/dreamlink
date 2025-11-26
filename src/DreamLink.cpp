#include "DreamLink.h"
#include "globals.h"
#include "core/board.hpp"

// ========================================
// CONDITION HELPERS
// ========================================
const Condition ALWAYS_CONDITION(NONE, ALWAYS, 0);

// ========================================
// RULE BUILDER IMPLEMENTATION
// ========================================
RuleBuilder& RuleBuilder::then(ActionType act, int p) {
  action = act;
  param = p;
  return *this;
}

RuleBuilder& RuleBuilder::sometimes(uint8_t prob) {
  probability = prob;
  return *this;
}

Rule RuleBuilder::build() {
  Rule r;
  r.name = name;
  r.sensor = condition.sensor;
  r.op = condition.op;
  r.threshold = condition.threshold;
  r.action = action;
  r.param = param;
  r.probability = probability;
  return r;
}

// ========================================
// DREAMLINK IMPLEMENTATION
// ========================================

DreamLink::DreamLink()
  : ruleCount(0), reflexEngine(nullptr), isAwake(false),
    debugEnabled(false), lastDebugTime(0), pendingBuilder(nullptr) {

  movement = new Movement();
  distanceSensor = new DistanceSensor();
  batterySensor = new BatterySensor();
  audio = new AudioFeedback();

  // Clear drivers
  for (int i = 0; i < 16; i++) {
    drivers[i] = nullptr;
  }
}

DreamLink::~DreamLink() {
  if (reflexEngine) delete reflexEngine;
  if (movement) delete movement;
  if (distanceSensor) delete distanceSensor;
  if (batterySensor) delete batterySensor;
  if (audio) delete audio;
  if (pendingBuilder) delete pendingBuilder;
}

// ========================================
// CORE LIFECYCLE
// ========================================

void DreamLink::begin(const BoardConfig& config) {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n========================================");
  Serial.println("   DreamLink - Where Physical Meets Meaning");
  Serial.println("========================================\n");

  randomSeed(analogRead(0));

  // Initialize Subsystems with Config
  movement->begin(config);
  distanceSensor->begin(config.ultrasonicTrig, config.ultrasonicEcho);
  batterySensor->begin(config.batteryPin);
  audio->begin(config.buzzerPin);

  Serial.println("[DreamLink] System initialized");
}

ConfigBuilder DreamLink::configure() {
  return ConfigBuilder(this);
}

void ConfigBuilder::begin() {
  probe->begin(config);
}

void DreamLink::detectSensors() {
  Wire.begin();
  Serial.println("\n[DreamLink] Scanning I2C bus...");
  
  byte error, address;
  int nDevices = 0;

  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0) {
      Serial.print("  - Found I2C device at 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      
      // Known sensors
      if (address == 0x76 || address == 0x77) Serial.print(" (BME280/BMP280?)");
      else if (address == 0x3C || address == 0x3D) Serial.print(" (OLED Display?)");
      else if (address == 0x68) Serial.print(" (MPU6050/DS3231?)");
      
      Serial.println();
      nDevices++;
    }
  }
  
  if (nDevices == 0)
    Serial.println("  - No I2C devices found\n");
  else
    Serial.println("  - Scan complete\n");
}

void DreamLink::wakeup() {
  // Finalize pending builder first!
  if (pendingBuilder) {
    rules[ruleCount++] = pendingBuilder->build();
    delete pendingBuilder;
    pendingBuilder = nullptr;
  }

  if (ruleCount == 0) {
    Serial.println("[WARNING] No rules loaded! Add rules before wakeup()");
    return;
  }

  // Create reflex engine with current rules
  reflexEngine = new Reflex(rules, ruleCount, audio, [this](SensorType type) {
    return this->readSensor(type);
  });

  isAwake = true;

  Serial.print("[DreamLink] Awakened with ");
  Serial.print(ruleCount);
  Serial.println(" rules\n");

  if (debugEnabled) {
    printRules();
  }
}

void DreamLink::sleep() {
  isAwake = false;
  movement->stop();
  Serial.println("[DreamLink] Entering sleep mode");
}

void DreamLink::live() {
  if (!isAwake) return;

  // Execute reflex engine
  reflexEngine->tick();

  // Optional debug output
  if (debugEnabled && (millis() - lastDebugTime > 1000)) {
    lastDebugTime = millis();
    Serial.print("[SENSORS] Distance: ");
    Serial.print(readDistance());
    Serial.print("cm | Battery: ");
    Serial.print(readBattery());
    Serial.println("%");
  }

  delay(50); // 20Hz loop rate
}

// ========================================
// SIMPLE API
// ========================================

RuleBuilder& DreamLink::when(Condition cond) {
  if (pendingBuilder) {
    // Finalize previous builder
    rules[ruleCount++] = pendingBuilder->build();
    delete pendingBuilder;
  }

  static char nameBuffer[32];
  snprintf(nameBuffer, sizeof(nameBuffer), "rule-%d", ruleCount + 1);

  pendingBuilder = new RuleBuilder(nameBuffer, cond);
  return *pendingBuilder;
}

void DreamLink::addRule(const char* name, Condition cond, ActionType action, int param, uint8_t prob) {
  if (ruleCount >= MAX_RULES) {
    Serial.println("[ERROR] Max rules reached!");
    return;
  }

  Rule r;
  r.name = name;
  r.sensor = cond.sensor;
  r.op = cond.op;
  r.threshold = cond.threshold;
  r.action = action;
  r.param = param;
  r.probability = prob;

  rules[ruleCount++] = r;
}

// ========================================
// PATTERN API
// ========================================

void DreamLink::behave(const char* patternName) {
  clearRules();

  if (strcmp(patternName, "explorer") == 0 || strcmp(patternName, "Explorer") == 0) {
    loadPattern(Explorer::rules, Explorer::count);
  }
  else if (strcmp(patternName, "cautious") == 0 || strcmp(patternName, "Cautious") == 0) {
    loadPattern(Cautious::rules, Cautious::count);
  }
  else if (strcmp(patternName, "wall-follower") == 0 || strcmp(patternName, "WallFollower") == 0) {
    loadPattern(WallFollower::rules, WallFollower::count);
  }
  else if (strcmp(patternName, "energy-saver") == 0 || strcmp(patternName, "EnergySaver") == 0) {
    loadPattern(EnergySaver::rules, EnergySaver::count);
  }
  else if (strcmp(patternName, "obstacle-avoidance") == 0 || strcmp(patternName, "ObstacleAvoidance") == 0) {
    loadPattern(ObstacleAvoidance::rules, ObstacleAvoidance::count);
  }
  else {
    Serial.print("[ERROR] Unknown pattern: ");
    Serial.println(patternName);
  }
}

void DreamLink::loadPattern(Rule* pattern, int count) {
  clearRules();
  for (int i = 0; i < count && ruleCount < MAX_RULES; i++) {
    rules[ruleCount++] = pattern[i];
  }
  Serial.print("[DreamLink] Loaded pattern: ");
  Serial.print(count);
  Serial.println(" rules");
}

// ========================================
// ADVANCED API
// ========================================

void DreamLink::loadRules(Rule* customRules, int count) {
  clearRules();
  for (int i = 0; i < count && ruleCount < MAX_RULES; i++) {
    rules[ruleCount++] = customRules[i];
  }
}

void DreamLink::clearRules() {
  ruleCount = 0;
  if (pendingBuilder) {
    delete pendingBuilder;

void DreamLink::forward(int speed) {
  movement->forward(speed);
}

void DreamLink::backward(int speed) {
  movement->backward(speed);
}

void DreamLink::turnLeft(int speed) {
  movement->turnLeft(speed);
}

void DreamLink::turnRight(int speed) {
  movement->turnRight(speed);
}

void DreamLink::stop() {
  movement->stop();
}

// ========================================
// DEBUG & UTILITIES
// ========================================

void DreamLink::enableDebug(bool enable) {
  debugEnabled = enable;
}

void DreamLink::printRules() {
  Serial.println("Current rules:");
  for (int i = 0; i < ruleCount; i++) {
    Serial.print("  [");
    Serial.print(i + 1);
    Serial.print("] ");
    Serial.print(rules[i].name);
    Serial.print(" (prob: ");
    Serial.print(rules[i].probability);
    Serial.println("%)");
  }
  Serial.println();
}

void DreamLink::identify(const char* id) {
  Serial.print("[DreamLink] Identity: ");
  Serial.println(id);
}
