/*
Программа представляет собой комплексный скетч для Arduino, 
предназначенный для управления 16x16 адресной светодиодной
матрицей с использованием библиотеки FastLED. Он обеспечивает
различные возможности отображения текста, символов, анимаций
и специальных эффектов на светодиодной матрице.

Версия - v1.6.1 
-> ассинхронная бегущая трока
*/

#include <FastLED.h>  // Подключаем библиотеку для управления светодиодной матрицей
#include "letters.h"  // Подключаем заголовок с кодами символов, букв и картинок

#define DATA_PIN 3     // Пин, к которому подключена матрица
#define NUM_LEDS 256   // Количество светодиодов на матрице 16x16
#define BRIGHTNESS 10  // Яркость (0-255)

#define SIZE 16        // Размер матрицы
#define LENGTH 8       // Количество бит при перерасчёте
#define NUMBER_SIZE 4  // Количество байт для описания символов
#define LETTER_SIZE 7  // Количество символов для описания букв
#define STEP 16        // Смещение букв относительно символов

const String numberString = "0123456789 !,.:;?";                 // Строка для анализа символов
const String letterString = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";  // Строка для анализа букв

uint32_t color = 0x220000;  // Цвет светодиодов
uint8_t grid[SIZE][2];      // Матрица светодиодов (по 2 байта на строку)

int* res;
int xStart;
int yStart;
int x;
int y;
int size;
int tempSpeed;
unsigned long runTextTime = 0;

CRGB leds[NUM_LEDS];  // Массив с цветами светодиодов

void setup() {
  // put your setup code here, to run once:
  // Настройка светодиодной матрицы
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  clear();  // Очищаем матрицу
}

void loop() {
  // put your main code here, to run repeatedly:
  // Примеры использования функций:

  // Отображение одного символа
  // clear();
  // make(grid, 18, 0, 0);
  // animation();
  // delay(200);

  // Поочерёдное отображение букв строки s
  // String s = "ПРОГРАММА";
  // int size = sizeText(s);
  // int* res = readText(s, size);
  // for (int i = 0; i < size; i++) {
  //   clear();
  //   make(grid, res[i], 0, 0);
  //   animation();
  //   delay(200);
  // }

  // Бегущая строка s с задержкой 200 мс
  if (Serial.available() > 0) {
    int c = Serial.parseInt();
    if (c == 1) {
      String s = "ЗАНЯТО";
      runText(s, 18, 4, 100);
    }else{
      String s = "НЕТ";
      runText(s, 18, 2, 50);
    }
    Serial.read();
  }

  // Анимация сердца
  // for (int i = 0; i < 6; i++) {
  //   clear();
  //   add(grid, i);
  //   animationRevers();
  //   delay(50);
  //
  runText();
}

/*
Установка цвета светодиода.
x -> слева на право
y -> сверху вниз
Так как светодиоды в матрицы идут последовательно (змейкой),
то необходимо при x поразному расчитывать y
*/
void setColor(int8_t x, int8_t y, uint32_t color) {
  uint16_t pozition;
  if (x % 2 == 0)
    pozition = SIZE * x + y;               //Змейка вниз
  else pozition = SIZE * (x + 1) - y - 1;  //Змейка вверх
  leds[pozition] = color;
}

//Очищаем матрицу
void clear() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < 2; j++) {
      grid[i][j] = 0;
    }
  }
  FastLED.clear();
}

//Отображение
void animation() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][0] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(i, j, color);  //Заполняем светодиод левой половины цветом
    }
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][1] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(i, j + LENGTH, color);  //Заполняем светодиод правой половины цветом
    }
  }
  FastLED.show();  //Отправляем данные на матрицу
}

/*
Отображение
Применяется для отображения картинки.
Так как представление картинки и символов и букв различной,
то для отображения картинки (сердечка) необходимо пользоваться методом
anumationRevers().
*/
void animationRevers() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][0] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(j, i, color);  //Заполняем светодиод левой половины цветом
    }
    for (int8_t j = 0; j < LENGTH; j++) {
      uint8_t pixel = (grid[i][1] & (1 << (LENGTH - j - 1)));
      if (pixel > 0)
        setColor(j + LENGTH, i, color);  //Заполняем светодиод правой половины цветом
    }
  }
  FastLED.show();  //Отправляем данные на матрицу
}

//Метод добавления символа, буквы
void make(uint8_t grid[SIZE][2], int n, int y, int x) {
  int8_t size_simbol;
  uint8_t letter;
  uint8_t pixel;
  uint8_t line;
  if (n > STEP)                    //Для описания символов
    size_simbol = LETTER_SIZE;     //и букв используется
  else size_simbol = NUMBER_SIZE;  //различное количество байт

  for (int8_t i = 0; i < size_simbol; i++) {
    if (y + i > SIZE - 1 || y + i < 0)
      continue;
    if (n > STEP)
      letter = pgm_read_byte(&lettes[n - STEP - 1][i]);  //Получаем букву
    else
      letter = pgm_read_byte(&number[n][i]);  //Получаем символ

    for (int8_t j = 0; j < LENGTH; j++) {
      if (x + j > SIZE - 1 || x + j < 0)
        continue;
      pixel = letter & (1 << (LENGTH - j - 1));  //Получаем значение светодиода
      if (pixel > 0) {
        if (x + j >= LENGTH) {
          line = grid[y + i][1];
          line = line | (1 << (2 * LENGTH - x - j - 1));
          grid[y + i][1] = line;  //Устанавливаем значение светодиода
        } else {
          line = grid[y + i][0];
          line = line | (1 << (LENGTH - x - j - 1));
          grid[y + i][0] = line;  //Устанавливаем значение светодиода
        }
      }
    }
  }
}

//Метод добавления картинки (сердечка)
void add(uint8_t grid[SIZE][2], int n) {
  int8_t iterator = 0;
  uint8_t line;
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < 2; j++) {
      line = pgm_read_byte(&heart[n][iterator]);  //Получаем строку картинки
      grid[i][j] = line;
      iterator++;
    }
  }
}

//Метод определения размера текста (количество символов)
int sizeText(String text) {
  bool paint = false;
  int size = 0;
  for (int i = 0; i < text.length(); i++) {
    if ((int)text[i] < 0) {
      if (paint) {
        paint = false;
        size++;  //Для русских букв
      } else
        paint = true;
    } else {
      size++;  //Для символов
    }
  }
  return size;
}

//Метод возвращает массив индексов, которые являются ссылками на символы и буквы
int* readText(String text, int size) {
  bool paint = false;
  int* mass = new int[size];  //Массив индексов
  int iterator = 0;
  int p;
  for (int i = 0; i < text.length(); i++) {
    if ((int)text[i] < 0) {
      if (paint) {
        paint = false;
        p = 129 + (int)text[i];
        mass[iterator] = p;
        iterator++;
      } else
        paint = true;
    } else {
      p = numberString.indexOf(text[i]);
      mass[iterator] = p;
      iterator++;
    }
  }
  return mass;
}

//Метод автоматически получает размер строки и возвращает массиы индексов
int* readText(String text) {
  int size = sizeText(text);
  return readText(text, size);
}
void runText(String text, int startX, int startY, int temp) {
  size = sizeText(text);
  res = readText(text, size);
  xStart = startX;
  yStart = startY;
  x = startX;
  y = startY;
  tempSpeed = temp;
}

void runText() {
  int del = 0;
  int maxSize = 7 * size;
  int letter = 0;
  int past = 0;
  if (millis() - runTextTime > tempSpeed) {
    clear();
    del = 0;
    for (int i = 0; i < size; i++) {
      if (x + del > SIZE)
        break;
      letter = res[i];                                //Получаем индекс
      make(grid, letter, x + del, y);                 //Добавляем символ или букву
      past = pgm_read_byte(&letterSize[letter]) - 2;  //Получаем длину промежутка между буквами
      del += 7 + past;
    }
    animation();
    x--;
    if (x < -maxSize) {
      x = xStart;
    }
    runTextTime = millis();
  }
}
