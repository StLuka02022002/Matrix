#include <FastLED.h>
#include "letters.h"

#define DATA_PIN 3
#define NUM_LEDS 256
#define SIZE 16
#define LENGTH 8
#define NUMBER_SIZE 4
#define LETTER_SIZE 7
#define BRIGHTNESS 30

uint32_t color = 0xFF0000;
uint8_t grid[SIZE][2];



int pinOut = 3;

int l = 0;

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  clear();
}

void loop() {

  String text = "ВИКА, Я ТЕБЯ ЛЮБЛЮ!";

  int temp = 25;
  runText(text, 18, 4, temp);
  for (int k = 0; k < 6; k++)
    for (int i = 0; i < 6; i++) {
      clear();
      add(grid, i);
      animationRevers();
      delay(50);
    }
}

void setColor(int8_t x, int8_t y, uint32_t color) {
  uint16_t pozition;
  if (x % 2 == 0)
    pozition = SIZE * x + y;
  else pozition = SIZE * (x + 1) - y - 1;
  leds[pozition] = color;
}

void conv(int x, int y) {
}

void make(uint8_t grid[SIZE][2], int n, int y, int x) {
  int ls;
  if (n > 16)
    ls = LETTER_SIZE;
  else ls = NUMBER_SIZE;
  for (int8_t i = 0; i < ls; i++) {
    if (y + i > SIZE - 1 || y + i < 0)
      continue;
    uint8_t letter;
    if (n > 16) {
      letter = pgm_read_byte(&lettes[n - 17][i]);
    } else {
      letter = pgm_read_byte(&number[n][i]);
    }
    for (int8_t j = 0; j < LENGTH; j++) {
      if (x + j > SIZE - 1 || x + j < 0)
        continue;
      uint8_t pixel = letter & (1 << (LENGTH - j - 1));
      if (pixel > 0) {
        if (x + j >= LENGTH) {
          uint8_t line = grid[y + i][1];
          line = line | (1 << (2 * LENGTH - x - j - 1));
          grid[y + i][1] = line;
        } else {
          uint8_t line = grid[y + i][0];
          line = line | (1 << (LENGTH - x - j - 1));
          grid[y + i][0] = line;
        }
      }
    }
  }
}

int sizeText(String text) {
  bool paint = false;
  int size = 0;
  for (int i = 0; i < text.length(); i++) {
    if ((int)text[i] < 0) {
      if (paint) {
        paint = false;
        int p = 112 + (int)text[i];
        size++;
      } else
        paint = true;
    } else {
      int p = numberString.indexOf(text[i]);
      size++;
    }
  }
  return size;
}

void add(uint8_t grid[SIZE][2], int n) {
  int it = 0;
  uint8_t h;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < 2; j++) {
      h = pgm_read_byte(&heart[n][it]);
      grid[i][j] = h;
      Serial.println(h);
      it++;
    }
  }
}

void runText(String text, int startX, int startY, int temp) {
  int size = sizeText(text);
  Serial.println(size);
  int* res = readText(text, size);
  int del = 7;
  int xStart = startX;
  int maxSize = del * size;
  int let = 0;
  int lt = 0;
  int st = 0;
  while (true) {
    clear();
    del = 0;
    for (int i = 0; i < size; i++) {
      if (xStart + del > SIZE)
        break;
      let = res[i];
      make(grid, let, xStart + del, startY);
      lt = pgm_read_byte(&letterSize[let]) - 2;
      del = del + 7 + lt;
    }
    Serial.println();
    animation();
    delay(temp);
    xStart--;
    if (xStart < -maxSize) {
      xStart = startX;
      break;
    }
  }
}

int* readText(String text) {
  int size = sizeText(text);
  return readText(text, size);
}

int* readText(String text, int size) {
  bool paint = false;
  int* mass = new int[size];
  int l = 0;
  for (int i = 0; i < text.length(); i++) {
    if ((int)text[i] < 0) {
      if (paint) {
        paint = false;
        int p = 129 + (int)text[i];
        mass[l] = p;
        l++;
      } else
        paint = true;
    } else {
      int p = numberString.indexOf(text[i]);
      mass[l] = p;
      l++;
    }
  }
  return mass;
}

void clear() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < 2; j++) {
      grid[i][j] = 0;
    }
  }
  FastLED.clear();
}

void animationRevers() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][0] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(j, i, color);
    }
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][1] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(j + LENGTH, i, color);
    }
  }
  FastLED.show();
}

void animation() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][0] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(i, j, color);
    }
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][1] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(i, j + LENGTH, color);
    }
  }
  FastLED.show();
}
