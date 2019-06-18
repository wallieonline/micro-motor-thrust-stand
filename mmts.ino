// Assign motor pins
#define PWMD5_OUT_PIN 5
#define PWMD6_OUT_PIN 6
#define PWMD9_OUT_PIN 9
#define PWMD10_OUT_PIN 10

unsigned long previousMillis = 0;
unsigned int test = 0;
unsigned int pwmv = 0;
unsigned long interval = 0; // interval (milliseconds)

void setup()
{
  Serial.begin(9600);
  pinMode(PWMD5_OUT_PIN,OUTPUT);
  pinMode(PWMD6_OUT_PIN,OUTPUT);
  pinMode(PWMD9_OUT_PIN,OUTPUT);
  pinMode(PWMD10_OUT_PIN,OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (test == 0) { // Small delay for starting tests
      interval = 5000;
      pwmv = 0;
      analogWrite(PWMD5_OUT_PIN,0);
      analogWrite(PWMD6_OUT_PIN,0);
      analogWrite(PWMD9_OUT_PIN,0);
      analogWrite(PWMD10_OUT_PIN,0);
      test = 1;
    } else if (test == 1) { // Start motor 60 sec speed 255/3v*2v=170
      interval = 60000;
      pwmv = 170;
      analogWrite(PWMD5_OUT_PIN,170);
      analogWrite(PWMD6_OUT_PIN,170);
      analogWrite(PWMD9_OUT_PIN,170);
      analogWrite(PWMD10_OUT_PIN,170);
      test = 2;
    } else if (test == 2) { // Start motor 60 sec speed 255/3v*2v=212,5
      interval = 60000;
      pwmv = 212;
      analogWrite(PWMD5_OUT_PIN,212);
      analogWrite(PWMD6_OUT_PIN,212);
      analogWrite(PWMD9_OUT_PIN,212);
      analogWrite(PWMD10_OUT_PIN,212);
      test = 3;
    } else if (test == 3) { // Start motor 60 sec full speed
      interval = 60000;
      pwmv = 255;
      analogWrite(PWMD5_OUT_PIN,255);
      analogWrite(PWMD6_OUT_PIN,255);
      analogWrite(PWMD9_OUT_PIN,255);
      analogWrite(PWMD10_OUT_PIN,255);
      test = 4;
    } else if (test == 4) { // Stop motors wait 30 sec and goto test1
      interval = 30000;
      pwmv = 0;
      analogWrite(PWMD5_OUT_PIN,0);
      analogWrite(PWMD6_OUT_PIN,0);
      analogWrite(PWMD9_OUT_PIN,0);
      analogWrite(PWMD10_OUT_PIN,0);
      test = 1;
    }
      Serial.print("Motor PWM = ");
      Serial.print(pwmv);
      Serial.print("    ");
      Serial.print("Duration = ");
      Serial.println(interval);
  }
}
