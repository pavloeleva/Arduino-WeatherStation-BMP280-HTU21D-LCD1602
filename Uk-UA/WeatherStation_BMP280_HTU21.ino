/**************************************************************************************
================================================
WeatherStation_BMP280_HTU21
================================================ 
  (с)П.Єлєва для СТЕМ-клубу GeekOn!, червень 2022 
    [ https://github.com/pavloeleva/Arduino-WeatherStation-BMP280-HTU21D-LCD1602 ]
 

Скетч для роботи метеостанції (температура, атмосферний тиск, вологість повітря).

  Список компонентів:
    - Плата розробника Arduino Uno;

    - Модуль датчика температури та тиску BMP280     
        Підключений по шині І2С.
        Використовується для отримання показів температури та атмосферного тиску.
        Для роботи з датчиком у скетчі застосовується бібліотека iarduino_Pressure_BMP
          [ https://github.com/tremaru/iarduino_Pressure_BMP ] 

    - Модуль датчика температури та вологості повітря HTU21D
        Підключений по шині І2С.
        Використовується для отримання значення вологості повітря. 
        Для роботи з датчиком у скетчі застосовується бібліотека Adafruit_HTU21DF.
          [ https://github.com/adafruit/Adafruit_HTU21DF_Library ] 

    - Дисплей LCD1602 з модулем І2С
        Для роботи з дисплеєм використана бібліотека LiquidCrystal_I2C
          [ https://github.com/johnrickman/LiquidCrystal_I2C ]

    - Модуль тактової кнопки (при використанні просто кнопки варто передбачити стягуючого резистора, або зконфігурувати пін кнопки в INPUT_PULLUP)
        Для обробки брязкоту кнопки використано алгоритм, 
        наведений у прикладі Debounce, написаному David A. Mellis
          [ https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce ]

**************************************************************************************/

#include <LiquidCrystal_I2C.h>
#include <iarduino_Pressure_BMP.h>
#include <Adafruit_HTU21DF.h>

// змінні для обробки натискання кнопки і її брязкоту
const byte pinBtn = 10;              // пін плати Arduino, на який заведений вивід OUT модуля кнопки
byte btnState;                       // стан кнопки (HIGH - нптиснута, LOW - не натиснута)
byte lastBtnState;                   // попередній стан кнопки
unsigned long lastDebounceTime = 0;  // час в мс (з моменту запуску скетча) останнього брязкоту
unsigned long debounceDelay = 50;    // інтервал в мс на встановлення стабільного стану

// Масиви для створення користувацьких символів на LCD
byte thermChar[8] = {  // "малюємо" термометра
  0b01101,
  0b01100,
  0b01110,
  0b01100,
  0b01110,
  0b01100,
  0b11110,
  0b11110
};

byte ambrellaChar[8] = {  // "малюємо" парасолю
  0b01110,
  0b11101,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b10100,
  0b11000
};

byte degreeChar[8] = {  // "Млюємо" градус
  0b01100,
  0b10010,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte dropChar[8] = {  // "Малюємо" краплю
  0b00000,
  0b00100,
  0b01010,
  0b01110,
  0b10111,
  0b11111,
  0b11111,
  0b01110
};

byte arrowDown[8] = {  // "Малюємо" стрілку вниз 
  0b00000,
  0b00100,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b11111  
};

byte logoO[8] = {  // "Малюємо" логотипну "О"
  0b00100,
  0b01110,
  0b10101,
  0b10101,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};

// створюємо об'єкт sensor (для BMP280) з адресою 0х76 на шині І2С.
//   (якщо адреса 0х77, то можна писати порсто sensor без дужок)
iarduino_Pressure_BMP sensor(0x76);

// створення об'єкту lcd (для роботи з дисплеєм LCD1602)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27 - адреса пристрою на шині І2С; 16 - к-сть символів у рядку; 2 - к-сть рядків

// створення об'єкту htu (для роботи з сенсором HTU21D)
Adafruit_HTU21DF htu = Adafruit_HTU21DF();


////////////////////// Функція виконується один раз при запуску скетча //////////////////////
void setup() {   
  // Задаємо режим піна pinBtn на читання
  pinMode(pinBtn, INPUT);
  
  // ініціюємо об'єкт lcd
  lcd.init();

  // Створюємо символи користувача char(n) із промальованих масивів (можна, максимум, 8)
  lcd.createChar(0, thermChar);     // char(0) - термометр
  lcd.createChar(1, ambrellaChar);  // char(1) - парасоля
  lcd.createChar(2, degreeChar);    // char(2) - символ градуса
  lcd.createChar(3, dropChar);      // char(3) - крапля
  lcd.createChar(4, arrowDown);     // char(4) - стрілка вниз
  lcd.createChar(5, logoO);         // char(5) - логотипга "О"
  
  // ініціюємо об'єкт sensor
  sensor.begin();

  // ініціюємо об'єкт htu
  htu.begin();
}


//////////////////////  Функція виконується у нескінченному циклі //////////////////////
void loop() {   
  // вимикаємо підсвітку дисплея
  lcd.noBacklight();

  ///////// Обробка натискання та брязкоту кнопки
  int reading = digitalRead(pinBtn);
  if (reading != lastBtnState) {
    lastDebounceTime = millis();
  }
  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != btnState) {
      btnState = reading;
      if (btnState == HIGH) {
        
        ////// Зчитування показів датчиків
        // читаємо покази HTU21D і зберігаємо їх до цілих змінних
        int tempHtu21 = round(htu.readTemperature());  
        int humidity = round(htu.readHumidity());        
        // читанємо покази з BMP280 і зберігаємо їх до цілих змінних
        // (значення аргументу в методі read():  1 - атм.тиск в мм рт.ст.; 2 - в Па)
        sensor.read(1);
        int pressure = round(sensor.pressure);
        int temperature = round(sensor.temperature); // покази температури беремо з BMP280. Якщо потрыбно брати з HTU21D, цей рядок слід закоментувати ...
        //int temperature = round(tempHtu21); // ... і розкоментувати цей рядок
        
        ////// Вивід на дисплей
        // встановлюємо курсор на першу позицію верхнього рядка
        lcd.setCursor(0, 0);
        // виводимо символ термометра та значення температури на дисплей
        lcd.print(char(0));  // можна, також, lcd.print("\0")
        if (temperature > 0) lcd.print("+");
        lcd.print(String(temperature));
        // прописуємо "°С"
        lcd.print(char(2));  // можна, також, lcd.print("\2")
        lcd.print("C");        
        lcd.setCursor(11, 0); // встановлюэмо курсор на одинадцяту позицію першого рядка
        // виводимо символ краплі та значення вологості повітря
        lcd.print(char(3));  // можна, також, lcd.print("\3")
        lcd.print(String(humidity));
        // знак відсотків
        lcd.print("%");
        lcd.setCursor(0, 1); // переводимо курсор на перший символ другого рядка 
        // виводимо символ парасолі, стрілки та значення атмосферного тиску на дисплей
        lcd.print(char(1));  // можна, також, lcd.print("\1")
        lcd.print(char(4));  // можна, також, lcd.print("\4")
        lcd.print(String(pressure));
        lcd.print("mmH");        
        lcd.setCursor(12, 1); // переводимо курсор на 14-у позицію другого рядка
        // логотип для випендрьожу)))
        lcd.print("G");
        lcd.print(char(5)); // можна, також, lcd.print("\5")
        lcd.print("!");
        // Вмикаємо підсвітку на час, зазначений аргументом в delay() ...
        lcd.backlight();
        delay(10000);
        // ... та очищуємо дисплей
        lcd.clear();
      }
    }
  }

  // запам'ятовуємо останній кнопки 
  lastBtnState = reading;
}
