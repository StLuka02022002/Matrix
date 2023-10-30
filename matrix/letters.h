const uint8_t number[][4] PROGMEM = {
  {0x7C,0x82,0x82,0x7C}, //0
  {0x40,0xFE,0x00,0x00}, //1
  {0x46,0x8A,0x92,0x62}, //2
  {0x44,0x82,0x92,0x6C}, //3
  {0x18,0x28,0x48,0xFE}, //4
  {0xF4,0xA2,0xA2,0x9C}, //5
  {0x7C,0x92,0x92,0x4C}, //6
  {0x80,0x8E,0xB0,0xC0}, //7
  {0x6C,0x92,0x92,0x6C}, //8
  {0x64,0x92,0x92,0x7C}, //9
  {0x0,0x0,0x0,0x0}, // 
  {0xFA,0x0,0x0,0x0}, //!
  {0x3,0x0,0x0,0x0}, //,
  {0x2,0x0,0x0,0x0}, //.
  {0x22,0x0,0x0,0x0}, //:
  {0x23,0x0,0x0,0x0}, //;
  {0x40,0x9A,0x90,0x60}, //?
};

const uint8_t lettes[][7] PROGMEM = {
  {0x1E,0x68,0x88,0x68,0x1E,0x0,0x0}, //А
  {0xFE,0x92,0x92,0xC,0x0,0x0,0x0}, //Б
  {0xFE,0x92,0x92,0x7C,0x0,0x0,0x0}, //В
  {0xFE,0x80,0x80,0x80,0x0,0x0,0x0}, //Г
  {0x3,0x6,0xFA,0x82,0x82,0xFE,0x3}, //Д
  {0xFE,0x92,0x92,0x92,0x92,0x0,0x0}, //Е
  {0xC6,0x28,0x10,0xFE,0x10,0x28,0xC6}, //Ж
  {0x44,0x82,0x92,0x6C,0x0,0x0,0x0}, //З
  {0xFE,0xC,0x30,0x40,0xFE,0x0,0x0}, //И
  {0xFE,0xC,0x90,0x20,0xFE,0x0,0x0}, //Й
  {0xFE,0x10,0x6C,0x82,0x0,0x0,0x0}, //К
  {0x2,0xFC,0x80,0x80,0xFE,0x0,0x0}, //Л›
  {0xFE,0x60,0x10,0x8,0x10,0x60,0xFE}, //М
  {0xFE,0x10,0x10,0x10,0xFE,0x0,0x0}, //Н
  {0x7C,0x82,0x82,0x82,0x7C,0x0,0x0}, //О
  {0xFE,0x80,0x80,0x80,0xFE,0x0,0x0}, //П
  {0xFE,0x90,0x90,0xF0,0x0,0x0,0x0}, //Р 
  {0x7C,0x82,0x82,0x82,0x44,0x0,0x0}, //С
  {0x80,0x80,0xFE,0x80,0x80,0x0,0x0}, //Т
  {0xC2,0x32,0xC,0x30,0xC0,0x0,0x0}, //У
  {0x38,0x44,0xFE,0x44,0x38,0x0,0x0}, //Ф
  {0x82,0x6C,0x10,0x6C,0x82,0x0,0x0}, //Х
  {0xFE,0x2,0x2,0x2,0xFE,0x3,0x0}, //Ц
  {0xF0,0x8,0x8,0xFE,0x0,0x0,0x0}, //Ч
  {0xFE,0x2,0x2,0xFE,0x2,0x2,0xFE}, //Ш
  {0xFE,0x2,0x2,0xFE,0x2,0x2,0xFF}, //Щ
  {0x80,0xFE,0x12,0x12,0xC,0x0,0x0}, //Ъ
  {0xFE,0x12,0x12,0xC,0x0,0xFE,0x0}, //Ы
  {0xFE,0x12,0x12,0xC,0x0,0x0,0x0}, //Ь
  {0x44,0x92,0x92,0x7C,0x0,0x0,0x0}, //Э
  {0xFE,0x10,0x7C,0x82,0x82,0x82,0x7C}, //Ю
  {0x66,0x98,0x90,0x90,0xFE,0x0,0x0}, //Я
};

const uint8_t letterSize[] PROGMEM = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,4,2,4,1,2,2,1,2,4,2,2,2,1,2,2,2,2,2,3,1,4,4,2,3,1,1,4,2};

const uint8_t heart[][32] PROGMEM = {
  {0,0,0,0,0,0,0,0,0,0,0,0,6,96,7,224,7,224,3,192,1,128,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,6,96,15,240,15,240,15,240,7,224,3,192,1,128,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,6,96,15,240,31,248,31,248,31,248,31,248,15,240,7,224,3,192,1,128,0,0,0,0,0,0},
  {0,0,0,0,12,48,30,120,63,252,63,252,63,252,63,252,63,252,31,248,15,240,7,224,3,192,1,128,0,0,0,0},
  {0,0,24,24,60,60,126,126,127,254,127,254,127,254,127,254,127,254,63,252,31,248,15,240,7,224,3,192,1,128,0,0},
  {56,28,126,126,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127,254,63,252,31,248,15,240,7,224,3,192,1,128},
};

