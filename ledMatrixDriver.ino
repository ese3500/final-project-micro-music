#include <Adafruit_GFX.h>
#include "P3RGB64x32MatrixPanel.h"

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 23, 15, 32, 33, 12, 16, 17, 18, false);

int prevHeights[16];
int heights[16];
char string[10];

int r = 0;
int g = 0;
int b = 15;

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
  Serial2.begin(1000000, SERIAL_8N2, 14);
  Serial.begin(9600);
  pinMode(39, INPUT);
  attachInterrupt(39, ISR, FALLING);
  attachInterrupt(4, isr2, FALLING);

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

    for (int i = 0; i < 16; i++) {
      heights[i] = (heights[i] * 31) / 9;
      if ((heights[i] - prevHeights[i]) >= 12) {
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
