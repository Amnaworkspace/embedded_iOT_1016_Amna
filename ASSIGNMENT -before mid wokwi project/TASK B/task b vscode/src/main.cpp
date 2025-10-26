// NAME: AMNAKHALID

// NAME: AMNA KHALID

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- OLED CONFIG ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// If your OLED has a reset pin, replace -1 with the pin number
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------- PIN DEFINITIONS ----------
#define BUTTON 32
#define LED 25
#define BUZZER 14

// ---------- GLOBAL VARIABLES ----------
bool ledState = false;
unsigned long pressStart = 0;
bool isPressed = false;

// ---------- FUNCTION PROTOTYPES ----------
void playMelody();
void shortBeep();
void showMessage(String msg);

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);           // For debug
  pinMode(BUTTON, INPUT_PULLUP);  // button connected to GND
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Wire.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;); // stop here if OLED fails
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("System Ready...");
  display.display();
  delay(1000);

  showMessage("Waiting for button...");
}

// ---------- MAIN LOOP ----------
void loop() {
  int buttonState = digitalRead(BUTTON);

  // Detect button press
  if (buttonState == LOW && !isPressed) {
    isPressed = true;
    pressStart = millis(); // time press began
  }

  // Detect button release
  if (buttonState == HIGH && isPressed) {
    isPressed = false;
    unsigned long pressDuration = millis() - pressStart;

    if (pressDuration > 1500) {
      // Long press -> play melody
      playMelody();
      showMessage("Long Press -> Melody");
    } else {
      // Short press -> toggle LED + short beep
      ledState = !ledState;
      digitalWrite(LED, ledState);
      shortBeep();
      showMessage("Short Press -> LED " + String(ledState ? "ON" : "OFF"));
    }
  }
}

// ---------- FUNCTIONS ----------
void playMelody() {
  // Simple 3-tone melody for long press
  tone(BUZZER, 500, 200);   // low tone
  delay(250);
  tone(BUZZER, 800, 200);   // medium tone
  delay(250);
  tone(BUZZER, 1200, 300);  // high tone
  delay(350);
  noTone(BUZZER);
}

void shortBeep() {
  // Quick beep for short press
  tone(BUZZER, 1000, 100);
  delay(150);
  noTone(BUZZER);
}

void showMessage(String msg) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Button Event:");
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}
