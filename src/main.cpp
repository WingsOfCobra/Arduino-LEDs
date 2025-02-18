#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 2 // WS2812 LEDs
#define NUMPIXELS 64 // Anzahl LEDs
#define BRIGHTNESS 230
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int pause=1000; // Millisekunden

struct RGB {
  int r;
  int g;
  int b;
};

void resetColors() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.clear();
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void fillPixel(int pixel, int red, int green, int blue) {
  pixels.setPixelColor(pixel, pixels.Color(red, green, blue));
  pixels.show();
}

void colorRandomPixel(int red, int green, int blue) {
  // randomSeed(analogRead(A0)); Get Random noise from unused Analog Port
  randomSeed(millis()); // Generate Random noise for Wokwi Simulation
  int randomPixel = random(0, NUMPIXELS);
  pixels.setPixelColor(randomPixel, pixels.Color(red, green, blue));
  pixels.show();
}

void fillAllPixels(int red, int green, int blue, int delayTime) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
    pixels.show();
    delay(delayTime);
  }
}

void flashAllPixels(int red, int green, int blue, int delayTime, int count) {
  for (int i = 0; i < count; i++) {
    for (int p = 0; p < NUMPIXELS; p++) {
      pixels.setPixelColor(p, pixels.Color(red, green, blue));
    }
    pixels.show();
    delay(delayTime);

    for (int p = 0; p < NUMPIXELS; p++) {
      pixels.setPixelColor(p, pixels.Color(0, 0, 0));
    }
    pixels.show();
    delay(delayTime);
  }
}

void breathePixel(int pixel, RGB color, int duration) {
  int steps = 50; // The number of steps for smooth breathing
  int delayTime = duration / (steps * 2); // Controls breathing speed

  // Fade In
  for (int i = 0; i <= steps; i++) {
    float factor = (float)i / steps; // Scale factor from 0 to 1
    int r = color.r * factor;
    int g = color.g * factor;
    int b = color.b * factor;
    
    pixels.setPixelColor(pixel, pixels.Color(r, g, b));
    pixels.show();
    delay(delayTime);
  }

  // Fade Out
  for (int i = steps; i >= 0; i--) {
    float factor = (float)i / steps; // Scale factor from 1 to 0
    int r = color.r * factor;
    int g = color.g * factor;
    int b = color.b * factor;
    
    pixels.setPixelColor(pixel, pixels.Color(r, g, b));
    pixels.show();
    delay(delayTime);
  }
}

// Function to create breathing effect on multiple pixels



RGB generatePinkStarColor() {
  RGB color;
  int brightness = random(10, BRIGHTNESS + 1);
  // Randomly select a pink variation
  int pinkType = random(0, 3); // 0 = Soft Pink, 1 = Vibrant Pink, 2 = Magenta-Pink

  if (pinkType == 0) {
    // Soft Pink
    color.r = random(200, 255);
    color.g = random(100, 150);
    color.b = random(200, 255);
  } else if (pinkType == 1) {
    // Vibrant Pink
    color.r = random(220, 255);
    color.g = random(50, 120);
    color.b = random(220, 255);
  } else {
    // Magenta-Pink
    color.r = random(230, 255);
    color.g = random(30, 80);
    color.b = random(230, 255);
  }

  // Scale brightness
  color.r = (color.r * brightness) / BRIGHTNESS;
  color.g = (color.g * brightness) / BRIGHTNESS;
  color.b = (color.b * brightness) / BRIGHTNESS;

  return color;
}

RGB generateStarColor() {
  
  RGB color;
  int brightness = random(10, BRIGHTNESS + 1);
  int starType = random(0, 3);  // 0 = Blueish, 1 = White, 2 = Reddish

  if (starType == 0) {
    // Blueish star (cool, young stars)
    color.r = random(180, 220);
    color.g = random(180, 220);
    color.b = random(220, 255);
  } else if (starType == 1) {
    // White star (neutral, Sun-like stars)
    color.r = random(200, 255);
    color.g = random(200, 255);
    color.b = random(200, 255);
  } else {
    // Reddish star (old, cool stars)
    color.r = random(220, 255);
    color.g = random(180, 220);
    color.b = random(180, 220);
  }

  // Scale color brightness
  color.r = (color.r * brightness) / BRIGHTNESS;
  color.g = (color.g * brightness) / BRIGHTNESS;
  color.b = (color.b * brightness) / BRIGHTNESS;

  return color;
}

void breatheMultipleStars(int numStars, int duration) {
  int steps = 50;  // Number of steps for smooth breathing
  int delayTime = duration / (steps * 2); // Speed of breathing (duration divided by steps)

  // Create an array to hold random pixels and their associated colors
  int pixelsArray[numStars];
  RGB colorsArray[numStars];

  // Randomly pick pixels and generate colors
  for (int i = 0; i < numStars; i++) {
    pixelsArray[i] = random(0, NUMPIXELS); // Random pixel
    colorsArray[i] = generatePinkStarColor(); // Random pink color
  }

  // Breathing effect: Fade In & Out
  for (int step = 0; step <= steps; step++) {
    float factor = (float)step / steps;  // Scale factor for brightness

    // Update each pixel with the current brightness factor
    for (int i = 0; i < numStars; i++) {
      int r = (colorsArray[i].r * factor);  // Apply brightness factor to Red
      int g = (colorsArray[i].g * factor);  // Apply brightness factor to Green
      int b = (colorsArray[i].b * factor);  // Apply brightness factor to Blue

      // Ensure brightness scaling is applied correctly
      pixels.setPixelColor(pixelsArray[i], pixels.Color(r, g, b));
    }

    pixels.show();  // Apply changes to all pixels
    delay(delayTime);
  }

  // Fade out
  for (int step = steps; step >= 0; step--) {
    float factor = (float)step / steps;  // Scale factor for brightness

    // Update each pixel with the current brightness factor
    for (int i = 0; i < numStars; i++) {
      int r = (colorsArray[i].r * factor);  // Apply brightness factor to Red
      int g = (colorsArray[i].g * factor);  // Apply brightness factor to Green
      int b = (colorsArray[i].b * factor);  // Apply brightness factor to Blue

      // Ensure brightness scaling is applied correctly
      pixels.setPixelColor(pixelsArray[i], pixels.Color(r, g, b));
    }

    pixels.show();  // Apply changes to all pixels
    delay(delayTime);
  }
}



void startupAnimation() {
  fillAllPixels(255, 255, 255, 5);
  // flashAllPixels(0, 0, 255, 300, 1);

  // resetColors();

  for (int i = 0; i < NUMPIXELS; i++) {
    RGB starColor = generateStarColor();
    fillPixel(i, starColor.r, starColor.g, starColor.b);
  }
}

void breatheSingleMode() {
  int pixel = random(0, NUMPIXELS);  // Select a random pixel
  RGB starColor = generatePinkStarColor(); // Get a pink star color
  breathePixel(pixel, starColor, 2000);
}

void breatheMultipleMode() {
  int numStars = 20;
  int duration = 2000;
  breatheMultipleStars(numStars, duration);
}

void naturalStars() {
  RGB starColor = generateStarColor();
  colorRandomPixel(starColor.r, starColor.g, starColor.b);
  delay(pause);
}

void fullNaturalStars() {
  for (int i = 0; i < NUMPIXELS; i++) {
    RGB starColor = generateStarColor();
    fillPixel(i, starColor.r, starColor.g, starColor.b);
  }
  delay(pause * 10);
}

void fullPinkStars() {
  for (int i = 0; i < NUMPIXELS; i++) {
    RGB starColor = generatePinkStarColor();
    fillPixel(i, starColor.r, starColor.g, starColor.b);
  }
  delay(pause * 10);
}

void pinkStars() {
  RGB starColor = generatePinkStarColor();
  colorRandomPixel(starColor.r, starColor.g, starColor.b);
  delay(pause);
}


void initPixels() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  startupAnimation();
}

void setup() 
{
  initPixels();
}

void loop() 
{
  pinkStars();
  // fullPinkStars();

  // naturalStars();
  // fullNaturalStars();

  // breatheSingleMode();
  // breatheMultipleMode();
}