#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


#define PIN 2
#define ROWS 8
#define COLUMNS 8
#define PAUSE 10 // DELAY IN MS
#define CUSTOMBRIGHTNESS true

long NUMPIXELS = ROWS * COLUMNS;

// COLOR PALETTE

long randRed;
long randGreen;
long randBlue;
long BRIGHTNESS = 255;

void regen_colors() {
  BRIGHTNESS = random(0, 255);

  randRed = BRIGHTNESS * random(180, 220) / 255;
  randGreen = BRIGHTNESS * random(219, 255) / 255;
  randBlue = BRIGHTNESS * random(244, 255) / 255;
}

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void fill_pixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    regen_colors();
    matrix.setPixelColor(i, randRed, randGreen, randBlue);
    matrix.show();
  }
}
void setup() {
  matrix.begin();
  regen_colors();
  fill_pixels();
}


void loop() {
  regen_colors();
  long randPixel = random(0, NUMPIXELS);
  matrix.setPixelColor(randPixel, randRed, randGreen, randBlue);
  matrix.show();
  delay(PAUSE);
}


 