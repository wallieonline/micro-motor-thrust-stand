// Assign motor pins
#define PWMD5_OUT_PIN 5
#define PWMD6_OUT_PIN 6
#define PWMD9_OUT_PIN 9
#define PWMD10_OUT_PIN 10
#define BIND_IN_PIN 11

uint8_t bindState;
uint8_t prevBindState = HIGH;
uint32_t prevBindMillis = 0;
uint8_t testState = 0;
uint8_t testPWMV = 0;
uint32_t prevTestMillis = 0;
uint32_t debounce = 1000; // interval (milliseconds)
uint32_t interval = 0; // interval (milliseconds)

void setup()
{
  Serial.begin(9600);
  pinMode(PWMD5_OUT_PIN,OUTPUT);
  pinMode(PWMD6_OUT_PIN,OUTPUT);
  pinMode(PWMD9_OUT_PIN,OUTPUT);
  pinMode(PWMD10_OUT_PIN,OUTPUT);
  pinMode(BIND_IN_PIN,INPUT);
}

void loop() {
  bindState = digitalRead(BIND_IN_PIN);
  if (bindState == LOW && prevBindState == HIGH && millis() - prevBindMillis >= debounce) {
    if (testState == 0) {
      testState = 1;
      Serial.println("Test Started...");
    } else {
      testState = 0;
      testPWMV = 0;
      interval = 0;
      myWriteMotors(testPWMV);
      Serial.println("Test Stopped...");
    }
    prevBindMillis = millis();
  }
  prevBindState = bindState;
  if (testState >= 1 && millis() - prevTestMillis >= interval) {
    prevTestMillis = millis();
      if (testState == 1) { // Start motor 60 sec speed 255/3v*2,0v=170
        interval = 60000;
        testPWMV = 170;
        testState = 2;
    } else if (testState == 2) { // Start motor 60 sec speed 255/3v*2,5v=212,5
        interval = 60000;
        testPWMV = 212;
        testState = 3;
    } else if (testState == 3) { // Start motor 60 sec full speed
        interval = 60000;
        testPWMV = 255;
        testState = 4;
    } else if (testState == 4) { // Stop motors wait 30 sec and goto test1
        interval = 30000;
        testPWMV = 0;
        testState = 1;
    }
    myWriteMotors(testPWMV);
    prevTestMillis = millis();
    Serial.print("Motor PWM = ");
    Serial.print(testPWMV);
    Serial.print("    ");
    Serial.print("Duration = ");
    Serial.println(interval);
  }
}

void myWriteMotors(uint8_t pwmv) {
  analogWrite(PWMD5_OUT_PIN,pwmv);
  analogWrite(PWMD6_OUT_PIN,pwmv);
  analogWrite(PWMD9_OUT_PIN,pwmv);
  analogWrite(PWMD10_OUT_PIN,pwmv);
}
