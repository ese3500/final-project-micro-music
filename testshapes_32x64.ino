/* Derived from Adafruit RGB_matrix_Panel library */

#include <Adafruit_GFX.h>  // Core graphics library
#include "P3RGB64x32MatrixPanel.h"
#include <arduinoFFT.h>
// #include <ESP32SPISlave.h>
//#include "P3RGB64x32MatrixPanel.cpp"

// constructor with default pin wiring
//P3RGB64x32MatrixPanel matrix;

// use this constructor for custom pin wiring instead of the default above
// these pins are an example, you may modify this according to your needs
P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 23, 15, 32, 33, 12, 16, 17, 18, false);

int prevHeights[16];
int heights[16];
char string[10];

int r = 0;
int g = 0;
int b = 15;

// ESP32SPISlave slave;

/*
int i = 0;

int mode = 0;

int position;

const uint16_t sineLookupTables[][65] = {
  { 16, 31, 16, 1 },
  { 16, 30, 25, 6, 1 },
  { 16, 29, 29, 16, 2, 2 },
  { 16, 28, 31, 22, 9, 1, 3 },
  { 16, 26, 31, 26, 16, 5, 1, 5 },
  { 16, 25, 31, 29, 21, 10, 2, 0, 6 },
  { 16, 25, 30, 30, 25, 16, 6, 1, 1, 6 },
  { 16, 24, 30, 31, 27, 20, 11, 4, 0, 1, 7 },
  { 16, 23, 29, 31, 29, 23, 16, 8, 2, 0, 2, 8 },
  { 16, 23, 28, 31, 30, 26, 19, 12, 5, 1, 0, 3, 8 },
  { 16, 22, 28, 31, 31, 28, 22, 16, 9, 3, 0, 0, 3, 9 },
  { 16, 22, 27, 30, 31, 29, 25, 19, 12, 6, 2, 0, 1, 4, 9 },
  { 16, 21, 26, 30, 31, 30, 26, 21, 16, 10, 5, 1, 0, 1, 5, 10 },
  { 16, 21, 26, 29, 31, 30, 28, 24, 18, 13, 7, 3, 1, 0, 2, 5, 10 },
  { 16, 21, 25, 29, 31, 31, 29, 25, 21, 16, 10, 6, 2, 0, 0, 2, 6, 10 },
  { 16, 21, 25, 28, 31, 31, 30, 27, 23, 18, 13, 8, 4, 1, 0, 0, 3, 6, 10 },
  { 16, 20, 25, 28, 30, 31, 30, 28, 25, 20, 16, 11, 6, 3, 1, 0, 1, 3, 6, 11 },
  { 16, 20, 24, 28, 30, 31, 31, 29, 26, 22, 18, 13, 9, 5, 2, 0, 0, 1, 3, 7, 11 },
  { 16, 20, 24, 27, 30, 31, 31, 30, 27, 24, 20, 16, 11, 7, 4, 1, 0, 0, 1, 4, 7, 11 },
  { 16, 20, 24, 27, 29, 31, 31, 30, 28, 25, 22, 18, 13, 9, 6, 3, 1, 0, 0, 2, 4, 7, 11 },
  { 16, 20, 23, 26, 29, 30, 31, 30, 29, 26, 23, 20, 16, 11, 8, 5, 2, 1, 0, 1, 2, 5, 8, 11 },
  { 16, 19, 23, 26, 29, 30, 31, 31, 30, 27, 25, 21, 17, 14, 10, 6, 4, 1, 0, 0, 1, 2, 5, 8, 12 },
  { 16, 19, 23, 26, 28, 30, 31, 31, 30, 28, 26, 23, 19, 16, 12, 8, 5, 3, 1, 0, 0, 1, 3, 5, 8, 12 },
  { 16, 19, 22, 25, 28, 30, 31, 31, 30, 29, 27, 24, 21, 17, 14, 10, 7, 4, 2, 1, 0, 0, 1, 3, 6, 9, 12 },
  { 16, 19, 22, 25, 28, 29, 31, 31, 31, 29, 28, 25, 22, 19, 16, 12, 9, 6, 3, 2, 0, 0, 0, 2, 3, 6, 9, 12 },
  { 16, 19, 22, 25, 27, 29, 30, 31, 31, 30, 28, 26, 23, 20, 17, 14, 11, 8, 5, 3, 1, 0, 0, 1, 2, 4, 6, 9, 12 },
  { 16, 19, 22, 25, 27, 29, 30, 31, 31, 30, 29, 27, 25, 22, 19, 16, 12, 9, 6, 4, 2, 1, 0, 0, 1, 2, 4, 6, 9, 12 },
  { 16, 19, 22, 24, 27, 29, 30, 31, 31, 31, 29, 28, 26, 23, 20, 17, 14, 11, 8, 5, 3, 2, 0, 0, 0, 1, 2, 4, 7, 9, 12 },
  { 16, 19, 21, 24, 26, 28, 30, 31, 31, 31, 30, 28, 26, 24, 21, 19, 16, 12, 10, 7, 5, 3, 1, 0, 0, 0, 1, 3, 5, 7, 10, 12 },
  { 16, 18, 21, 24, 26, 28, 30, 31, 31, 31, 30, 29, 27, 25, 23, 20, 17, 14, 11, 8, 6, 4, 2, 1, 0, 0, 0, 1, 3, 5, 7, 10, 13 },
  { 16, 18, 21, 24, 26, 28, 29, 30, 31, 31, 30, 29, 28, 26, 24, 21, 18, 16, 13, 10, 7, 5, 3, 2, 1, 0, 0, 1, 2, 3, 5, 7, 10, 13 },
  { 16, 18, 21, 23, 26, 28, 29, 30, 31, 31, 31, 30, 28, 27, 25, 22, 20, 17, 14, 11, 9, 6, 4, 3, 1, 0, 0, 0, 1, 2, 3, 5, 8, 10, 13 },
  { 16, 18, 21, 23, 25, 27, 29, 30, 31, 31, 31, 30, 29, 27, 25, 23, 21, 18, 16, 13, 10, 8, 6, 4, 2, 1, 0, 0, 0, 1, 2, 4, 6, 8, 10, 13 },
  { 16, 18, 21, 23, 25, 27, 29, 30, 31, 31, 31, 30, 29, 28, 26, 24, 22, 19, 17, 14, 12, 9, 7, 5, 3, 2, 1, 0, 0, 0, 1, 2, 4, 6, 8, 10, 13 },
  { 16, 18, 21, 23, 25, 27, 28, 30, 31, 31, 31, 31, 30, 28, 27, 25, 23, 21, 18, 16, 13, 10, 8, 6, 4, 3, 1, 0, 0, 0, 0, 1, 3, 4, 6, 8, 10, 13 },
  { 16, 18, 20, 23, 25, 27, 28, 30, 30, 31, 31, 31, 30, 29, 28, 26, 24, 22, 19, 17, 14, 12, 9, 7, 5, 3, 2, 1, 0, 0, 0, 1, 1, 3, 4, 6, 8, 11, 13 },
  { 16, 18, 20, 23, 25, 26, 28, 29, 30, 31, 31, 31, 30, 29, 28, 26, 25, 23, 20, 18, 16, 13, 11, 8, 6, 5, 3, 2, 1, 0, 0, 0, 1, 2, 3, 5, 6, 8, 11, 13 },
  { 16, 18, 20, 22, 24, 26, 28, 29, 30, 31, 31, 31, 30, 30, 29, 27, 25, 23, 21, 19, 17, 14, 12, 10, 8, 6, 4, 2, 1, 1, 0, 0, 0, 1, 2, 3, 5, 7, 9, 11, 13 },
  { 16, 18, 20, 22, 24, 26, 28, 29, 30, 31, 31, 31, 31, 30, 29, 28, 26, 24, 22, 20, 18, 16, 13, 11, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 5, 7, 9, 11, 13 },
  { 16, 18, 20, 22, 24, 26, 27, 29, 30, 30, 31, 31, 31, 30, 29, 28, 27, 25, 23, 21, 19, 17, 14, 12, 10, 8, 6, 4, 3, 2, 1, 0, 0, 0, 1, 1, 2, 4, 5, 7, 9, 11, 13 },
  { 16, 18, 20, 22, 24, 26, 27, 29, 30, 30, 31, 31, 31, 30, 30, 29, 27, 26, 24, 22, 20, 18, 16, 13, 11, 9, 7, 5, 4, 2, 1, 1, 0, 0, 0, 1, 1, 2, 4, 5, 7, 9, 11, 13 },
  { 16, 18, 20, 22, 24, 25, 27, 28, 29, 30, 31, 31, 31, 31, 30, 29, 28, 26, 25, 23, 21, 19, 17, 14, 12, 10, 8, 6, 5, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 9, 11, 13 },
  { 16, 18, 20, 22, 24, 25, 27, 28, 29, 30, 31, 31, 31, 31, 30, 29, 28, 27, 25, 24, 22, 20, 18, 16, 13, 11, 9, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 9, 11, 13 },
  { 16, 18, 20, 22, 23, 25, 27, 28, 29, 30, 31, 31, 31, 31, 30, 30, 29, 27, 26, 24, 22, 21, 19, 17, 14, 12, 10, 9, 7, 5, 4, 2, 1, 1, 0, 0, 0, 0, 1, 2, 3, 4, 6, 8, 9, 11, 13 },
  { 16, 18, 20, 21, 23, 25, 26, 28, 29, 30, 30, 31, 31, 31, 30, 30, 29, 28, 26, 25, 23, 21, 20, 18, 16, 13, 11, 10, 8, 6, 5, 3, 2, 1, 1, 0, 0, 0, 1, 1, 2, 3, 5, 6, 8, 10, 11, 13 },
  { 16, 17, 19, 21, 23, 25, 26, 28, 29, 30, 30, 31, 31, 31, 31, 30, 29, 28, 27, 26, 24, 22, 20, 18, 16, 15, 13, 11, 9, 7, 5, 4, 3, 2, 1, 0, 0, 0, 0, 1, 1, 2, 3, 5, 6, 8, 10, 12, 14 },
  { 16, 17, 19, 21, 23, 25, 26, 27, 29, 30, 30, 31, 31, 31, 31, 30, 30, 29, 27, 26, 25, 23, 21, 19, 17, 16, 14, 12, 10, 8, 6, 5, 4, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 4, 5, 6, 8, 10, 12, 14 },
  { 16, 17, 19, 21, 23, 24, 26, 27, 28, 29, 30, 31, 31, 31, 31, 30, 30, 29, 28, 27, 25, 24, 22, 20, 18, 16, 15, 13, 11, 9, 7, 6, 4, 3, 2, 1, 1, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 14 },
  { 16, 17, 19, 21, 23, 24, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 30, 29, 28, 27, 26, 24, 23, 21, 19, 17, 16, 14, 12, 10, 8, 7, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 14 },
  { 16, 17, 19, 21, 23, 24, 26, 27, 28, 29, 30, 30, 31, 31, 31, 31, 30, 29, 29, 28, 26, 25, 23, 22, 20, 18, 16, 15, 13, 11, 9, 8, 6, 5, 3, 2, 2, 1, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 7, 8, 10, 12, 14 },
  { 16, 17, 19, 21, 22, 24, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 30, 30, 29, 28, 27, 25, 24, 22, 21, 19, 17, 16, 14, 12, 10, 9, 7, 6, 4, 3, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 10, 12, 14 },
  { 16, 17, 19, 21, 22, 24, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 30, 30, 29, 28, 27, 26, 25, 23, 22, 20, 18, 16, 15, 13, 11, 9, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 10, 12, 14 },
  { 16, 17, 19, 21, 22, 24, 25, 26, 28, 29, 29, 30, 31, 31, 31, 31, 31, 30, 29, 29, 28, 26, 25, 24, 22, 21, 19, 17, 16, 14, 12, 10, 9, 7, 6, 5, 3, 2, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3, 5, 6, 7, 9, 10, 12, 14 },
  { 16, 17, 19, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 30, 30, 29, 28, 27, 26, 24, 23, 21, 20, 18, 16, 15, 13, 11, 10, 8, 7, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 14 },
  { 16, 17, 19, 20, 22, 23, 25, 26, 27, 28, 29, 30, 30, 31, 31, 31, 31, 30, 30, 29, 28, 27, 26, 25, 23, 22, 20, 19, 17, 16, 14, 12, 11, 9, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 9, 11, 12, 14 },
  { 16, 17, 19, 20, 22, 23, 25, 26, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 30, 29, 29, 28, 27, 25, 24, 23, 21, 20, 18, 16, 15, 13, 11, 10, 8, 7, 6, 4, 3, 2, 2, 1, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 9, 11, 12, 14 },
  { 16, 17, 19, 20, 22, 23, 25, 26, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 30, 30, 29, 28, 27, 26, 25, 23, 22, 20, 19, 17, 16, 14, 12, 11, 9, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 9, 11, 12, 14 },
  { 16, 17, 19, 20, 22, 23, 24, 26, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 30, 30, 29, 28, 27, 26, 25, 24, 22, 21, 19, 18, 16, 15, 13, 12, 10, 9, 7, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 7, 8, 9, 11, 12, 14 },
  { 16, 17, 19, 20, 22, 23, 24, 26, 27, 28, 29, 29, 30, 31, 31, 31, 31, 31, 31, 30, 29, 29, 28, 27, 26, 24, 23, 22, 20, 19, 17, 16, 14, 12, 11, 9, 8, 7, 5, 4, 3, 2, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3, 4, 5, 7, 8, 9, 11, 12, 14 },
  { 16, 17, 19, 20, 22, 23, 24, 25, 27, 28, 29, 29, 30, 30, 31, 31, 31, 31, 31, 30, 30, 29, 28, 27, 26, 25, 24, 22, 21, 19, 18, 16, 15, 13, 12, 10, 9, 7, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 6, 7, 8, 9, 11, 12, 14 },
  { 16, 17, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 30, 30, 29, 28, 27, 26, 25, 24, 23, 21, 20, 19, 17, 16, 14, 12, 11, 10, 8, 7, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 14 },
};

int pixelVals[64];
*/

void IRAM_ATTR ISR() {
    matrix.fillScreen(matrix.color444(0, 0, 0));
}

void IRAM_ATTR isr2() {
  matrix.fillScreen(matrix.color444(0, 0, 0));
  for (int i = 0; i < 16; i++) {
    prevHeights[i] = 0;
  }
  if (r == 15 && g == 0 && b == 0) {
    r = 0;
    g = 15;
  } else if (r == 0 && g == 15 && b == 0) {
    r = 15;
    b = 15;
  } else if (r == 0 && g == 0 && b == 15) {
    b = 0;
    r = 15;
  } else if (r == 15 && g == 15 && b == 15) {
    r = 0;
    g = 0;
  }
}

void setup() {
  // configure SPI
  /*
  slave.setDataMode(SPI_MODE0, 5, 19, 18, 33);
  slave.begin();
  */
  Serial2.begin(1000000, SERIAL_8N2, 14);
  Serial.begin(9600);
  pinMode(39, INPUT);
  attachInterrupt(39, ISR, FALLING);
  attachInterrupt(4, isr2, FALLING);
  // configure LCD graphics library
  matrix.begin();
}

void loop() {
  if (Serial2.find('x')) {
    for (int i = 0; i < 16; i++) {
      while (Serial2.available() == 0);
      int height = Serial2.read() - '0';
      if (height <= 9) {
        heights[i] = height;
      }
    }
    /*
    for (int i = 0; i < 16; i++) {
      sprintf(string, "%d ", heights[i]);
      Serial.print(string);
    }
    Serial.println();
    */

    for (int i = 0; i < 16; i++) {
      // normalize
      heights[i] = (heights[i] * 31) / 9;
      if ((heights[i] - prevHeights[i]) >= 25) {
        continue;
      }

      if (heights[i] > prevHeights[i]) {
        matrix.fillRect(i * 4, 31 - heights[i], 1, heights[i] - prevHeights[i] + 1, matrix.color444(r, g, b));
      } else if (heights[i] < prevHeights[i]) {
        matrix.fillRect(i * 4, 31 - prevHeights[i], 1, prevHeights[i] - heights[i] + 1, matrix.color444(0, 0, 0));
      }
      prevHeights[i] = heights[i];
    }
  }

}
