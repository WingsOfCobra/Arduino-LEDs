// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


#define PIN 2
#define ROWS 8
#define COLUMNS 8
#define PAUSE 0 // Pause in MS

long NUMPIXELS = ROWS * COLUMNS;
long randGreen;
long randRed;
long randBlue;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void fill_pixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    randRed = random(225);
    randGreen = 0;
    randBlue = 0;
    matrix.setPixelColor(i, randRed, randGreen, randBlue);
    matrix.show();
  }
}
void setup() {
  matrix.begin();
  fill_pixels();
}


void loop() {
  randRed = random(225);
  randGreen = 0;
  randBlue = 0;
  long randPixel = random(0, NUMPIXELS);
  matrix.setPixelColor(randPixel, randRed, randGreen, randBlue);
  matrix.show();
  delay(PAUSE);
}


 