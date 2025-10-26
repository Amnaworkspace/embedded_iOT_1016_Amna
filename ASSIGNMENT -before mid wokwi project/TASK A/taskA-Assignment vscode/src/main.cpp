//name:Amna khalid
//reg no:23-NTU-CS-1016
//TASK 1:1. Both OFF 
//2. Alternate blink 
//3. Both ON 
//4. PWM fade 
//Use the second button to reset to OFF.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LED1 25
#define LED2 27
#define LED3 26
#define BTN_MODE 32
#define BTN_RESET 33

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int mode = 1;

void showMode() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Mode: ");
  display.print(mode);

  if (mode == 1) display.print(" OFF");
  if (mode == 2) display.print(" ALT");
  if (mode == 3) display.print(" ON");
  if (mode == 4) display.print(" FADE");

  display.display();
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN_MODE, INPUT);
  pinMode(BTN_RESET, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showMode();
}

void loop() {

  if (digitalRead(BTN_RESET) == HIGH) {
    mode = 1;
    showMode();
  }

  if (digitalRead(BTN_MODE) == HIGH) {
    mode++;
    if (mode > 4) mode = 1;
    showMode();
    delay(300);
  }
// 
  if (mode == 1) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }

  if (mode == 2) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    delay(300);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(300);
  }

  if (mode == 3) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  }

  if (mode == 4) {
    for (int i = 0; i < 255; i++) {
      analogWrite(LED3, i);
      delay(5);
    }
    for (int i = 255; i > 0; i--) {
      analogWrite(LED3, i);
      delay(5);
    }
  }
}
