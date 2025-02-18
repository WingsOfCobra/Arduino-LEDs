#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


#define LED_PIN 2
#define ROWS 8
#define COLUMNS 8
#define PAUSE 1000 // DELAY IN MS
#define BRIGHTNESS 255
#define RANDOMBRIGHTNESS false


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, LED_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);


long NUMPIXELS = ROWS * COLUMNS;

long red;
long green;
long blue;

long pixel_brightness = 191;

void regenerateColors() {
  if (RANDOMBRIGHTNESS) {
    pixel_brightness = random(150, 255);
  }
  red = pixel_brightness * random(84, 100) / 255;
  green = pixel_brightness * random(107, 140) / 255;
  blue = pixel_brightness * random(171, 180) / 255;

}

void fill_pixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    regenerateColors();
    matrix.setPixelColor(i, red, green, blue);
    matrix.show();
  }
}

void colorRandomPixel() {
  regenerateColors();
  long randPixel = random(0, NUMPIXELS);
  matrix.setPixelColor(randPixel, red, green, blue);
  matrix.show();
  delay(PAUSE);
}

void setup() {
  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  regenerateColors();
  fill_pixels();
}

void loop() {
  colorRandomPixel();
}


 