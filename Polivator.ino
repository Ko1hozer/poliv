#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Инициализация объекта для работы с дисплеем
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Пины, к которым подключены датчики влажности почвы
int moisturePins[] = {A14, A13, A12, A11};

// Пины, к которым подключены клапаны
int valvePins[] = {19, 18, 17, 16};

int VALUE_1[] = {640, 550, 540, 540, 520, 500, 630, 480};
int VALUE_2[] = {250, 210, 190, 190, 230, 210, 250, 180};
  
// Пин, к которому подключена помпа
int pumpPin = 2;

// Пин, к которому подключен зумер
int buzzerPin = 3;

// Пин, к которому подключена кнопка сброса звукового сигнала
int resetPin = 4;

// Массив для хранения состояний клапанов
bool valveStates[8];

// Массив для хранения состояний зумера
bool buzzerState[15];

// Функция для получения номера датчика влажности по его пину
int getMoistureSensorIndex(int pin) {
  for (int i = 0; i < 4; i++) {
    if (moisturePins[i] == pin) {
      return i;
    }
  }
  return -1;
}

// Функция для получения номера клапана по номеру датчика влажности
int getValveIndex(int sensorIndex) {
  return sensorIndex;
}

void setup() {
  // Инициализация дисплея
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);      // Вывод информации на дисплей
  lcd.print("Moisture System ");
  lcd.setCursor(0, 1);
  lcd.print("by Goroz");
  delay(2000);
  
  // Инициализация пинов клапанов
  for (int i = 0; i < 4; i++) {
    pinMode(valvePins[i], OUTPUT);
    valveStates[i] = false;
  }

  // Инициализация пина помпы
  pinMode(pumpPin, OUTPUT);

  // Инициализация пина зумера
  pinMode(buzzerPin, OUTPUT);


  // Инициализация пина кнопки сброса звукового сигнала
   pinMode(resetPin, INPUT_PULLUP);

  // Закрытие всех клапанов
  for (int i = 0; i < 4; i++) {
    digitalWrite(valvePins[i], LOW);
  }

  // Очистка дисплея
  lcd.clear();
}

void loop() {
  // Цикл для чтения данных с датчиков влажности почвы
  for (int i = 0; i < 4; i++) {
    int moistureLevel = analogRead(moisturePins[i]);
    int valveIndex = getValveIndex(i);
    int moisturePercent = map(moistureLevel, VALUE_1[i], VALUE_2[i], 0, 100);

    // Вывод данных на дисплей
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor ");
    lcd.print(i + 1);
    lcd.print(": ");
    lcd.print(moisturePercent);
    lcd.print("%");
    delay(3000);
    
    // Проверка уровня влажности и запуск полива, если необходимо


      // Отображение сообщения об окончании полива на дисплее
      //lcd.setCursor(0, 1);
      //lcd.print("Watering done    ");

      // Запись состояния клапана
      valveStates[valveIndex] = true;
    
    // Проверка состояния клапана
    if (valveStates[valveIndex]) {
        int moistureLevel = analogRead(moisturePins[i]);
        int moisturePercent = map(moistureLevel, VALUE_1[i], VALUE_2[i], 0, 100);
          if (moisturePercent < 35 && !valveStates[valveIndex]) {
      // Отображение сообщения о начале полива на дисплее
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Watering zone #");
      lcd.print(valveIndex + 1);
      lcd.print("...");
      lcd.setCursor(0, 1);
      lcd.print("Starting pump..."); 
      digitalWrite(valvePins[i], HIGH);
      delay(1000);
  // Вывод сообщения о запуске помпы

      // Включение помпы на 5 секунд
      digitalWrite(pumpPin, HIGH);
      delay(5000);
      digitalWrite(pumpPin, LOW);
      delay(1000);
      digitalWrite(valvePins[i], LOW);
      
      // Проверка прошло ли 5 минут после полива
        if (millis() % 300000 == 0) {
        int moistureLevel = analogRead(moisturePins[i]);
        int moisturePercent = map(moistureLevel, VALUE_1[i], VALUE_2[i], 0, 100);

                // Проверка уровня влажности
        }
          } else if (moisturePercent < 60) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Watering zone #");
      lcd.print(valveIndex + 1);
       lcd.setCursor(0, 1);
      lcd.print("Starting pump..."); 
      digitalWrite(valvePins[i], HIGH); 
      delay(1000);
  // Вывод сообщения о запуске помпы

      // Включение помпы на 5 секунд
      digitalWrite(pumpPin, HIGH);
      delay(5000);
      digitalWrite(pumpPin, LOW);
      delay(1000);
      digitalWrite(valvePins[i], LOW);

                // Запись состояния клапана
          valveStates[valveIndex] = true;
      }
      
      if (moisturePercent < 30) {
          int moistureLevel = analogRead(moisturePins[i]);
        int moisturePercent = map(moistureLevel, VALUE_1[i], VALUE_2[i], 0, 100);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Watering zone #");
      lcd.print(valveIndex + 1);
      lcd.setCursor(0, 1);
      lcd.print("WaterLevel < 30%");

      // Включение зумера для оповещения
      digitalWrite(buzzerPin, HIGH);
      delay(3000);
      digitalWrite(buzzerPin, LOW);
      buzzerState[valveIndex] = true;
      }
    }

    // Проверка состояния зумера и кнопки сброса звукового сигнала
    if (buzzerState[valveIndex]) {
      if (digitalRead(resetPin) == LOW) {
        digitalWrite(buzzerPin, LOW);
        buzzerState[valveIndex] = false;
      }
    }
  }
}
