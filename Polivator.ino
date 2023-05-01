//Каждому датчику влажности прикреплен свой клапан подачи воды. при понижении % влажности почвы клапан открывается
//
//

#include <LiquidCrystal.h>

// подключаем дисплей
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// определяем пины для клапанов и датчиков влажности
int valvePin1 = 13;
int valvePin2 = 12;
int valvePin3 = 10;
int valvePin4 = 9;
int moisturePin1 = A0;
int moisturePin2 = A1;
int moisturePin3 = A2;
int moisturePin4 = A3;

// определяем порог влажности и переменные для хранения текущей влажности
int threshold1 = 50;
int threshold2 = 50;
int threshold3 = 50;
int threshold4 = 50;
int moisture1 = 0;
int moisture2 = 0;
int moisture3 = 0;
int moisture4 = 0;

// переменные для хранения состояний клапанов
bool valve1State = false;
bool valve2State = false;
bool valve3State = false;
bool valve4State = false;

// переменные для работы с меню
int currentMenu = 0;
int currentSubMenu = 0;
int lastEncoderState = LOW;
int encoderPin = 2;
int encoderButtonPin = 6;

void setup() {
  // настраиваем пины для клапанов как выходы
  pinMode(valvePin1, OUTPUT);
  pinMode(valvePin2, OUTPUT);
  pinMode(valvePin3, OUTPUT);
  pinMode(valvePin4, OUTPUT);

  // настраиваем пины для датчиков влажности как входы
  pinMode(moisturePin1, INPUT);
  pinMode(moisturePin2, INPUT);
  pinMode(moisturePin3, INPUT);
  pinMode(moisturePin4, INPUT);

  // инициализируем дисплей
  lcd.begin(16, 2);

  // выводим приветственное сообщение на дисплей
  lcd.print("Контроллер влажности");
  lcd.setCursor(0, 1);
  lcd.print("почвы");
  delay(2000);
}

void loop() {
  // считываем значения влажности по 4 точкам
  moisture1 = analogRead(moisturePin1);
  moisture2 = analogRead(moisturePin2);
  moisture3 = analogRead(moisturePin3);
  moisture4 = analogRead(moisturePin4);

  // преобразуем значения влажности в проценты
  moisture1 = map(moisture1, 0, 1023, 0, 100);
  moisture2 = map(moisture2, 0, 1023, 0, 100);
  moisture3 = map(moisture3, 0, 1023, 0,100);
  moisture4 = map(moisture4, 0, 1023, 0, 100);

  // выводим значения влажности на дисплей
  lcd.clear();
  lcd.print("Влажность почвы:");
  lcd.setCursor(0, 1);
  lcd.print("1:");
  lcd.print(moisture1);
  lcd.print("% 2:");
  lcd.print(moisture2);
  lcd.print("%");
  lcd.setCursor(0, 2);
  lcd.print("3:");
  lcd.print(moisture3);
  lcd.print("% 4:");
  lcd.print(moisture4);
  lcd.print("%");

  // выводим меню на дисплей
  if (currentMenu == 0) {
    lcd.setCursor(0, 0);
    lcd.print("1. Настройка клапанов");
    lcd.setCursor(0, 1);
    lcd.print("2. Настройка зумера");
    if (currentSubMenu == 0) {
      lcd.setCursor(15, 0);
      lcd.print(">");
    } else if (currentSubMenu == 1) {
      lcd.setCursor(15, 1);
      lcd.print(">");
    }
  } else if (currentMenu == 1) {
    lcd.setCursor(0, 0);
    lcd.print("1. Клапан 1: ");
    lcd.print(threshold1);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("2. Клапан 2: ");
    lcd.print(threshold2);
    lcd.print("%");
    lcd.setCursor(0, 2);
    lcd.print("3. Клапан 3: ");
    lcd.print(threshold3);
    lcd.print("%");
    lcd.setCursor(0, 3);
    lcd.print("4. Клапан 4: ");
    lcd.print(threshold4);
    lcd.print("%");
    if (currentSubMenu == 0) {
      lcd.setCursor(15, 0);
      lcd.print(">");
    } else if (currentSubMenu == 1) {
      lcd.setCursor(15, 1);
      lcd.print(">");
    } else if (currentSubMenu == 2) {
      lcd.setCursor(15, 2);
      lcd.print(">");
    }
  }

  // проверяем, нужно ли открыть или закрыть клапаны для датчика 1
  if (moisture1 < threshold1 && !valve1State) {
    digitalWrite(valvePin1, HIGH);
    valve1State = true;
  } else if (moisture1 > threshold1 && valve1State) {
    digitalWrite(valvePin1, LOW);
    valve1State = false;
  }

  // проверяем, нужно ли открыть или закрыть клапаны для датчика 2
  if (moisture2 < threshold2 && !valve2State) {
    digitalWrite(valvePin2, HIGH);
    valve2State = true;
  } else if (moisture2 > threshold2 && valve2State) {
    digitalWrite(valvePin2, LOW);
    valve2State = false;
  }

  // проверяем, нужно ли открыть или закрыть клапаны для датчика 3
  if (moisture3 < threshold3 && !valve3State) {
    digitalWrite(valvePin3, HIGH);
    valve3State = true;
  } else if (moisture3 > threshold3 && valve3State) {
    digitalWrite(valvePin3, LOW);
    valve3State = false;
  }

  // проверяем, нужно ли открыть или закрыть клапаны для датчика 4
  if (moisture4 < threshold4 && !valve4State) {
    digitalWrite(valvePin4, HIGH);
    valve4State = true;
  } else if (moisture4 > threshold4 && valve4State) {
    digitalWrite(valvePin4, LOW);
    valve4State = false;
  }

  // обрабатываем нажатия на кнопку энкодера для навигации по меню
  int encoderState = digitalRead(encoderPin);
  if (encoderState != lastEncoderState) {
    if (encoderState == HIGH) {
      if (digitalRead(encoderButtonPin) == HIGH) {
        if (currentMenu == 0) {
          if (currentSubMenu == 0) {
            currentSubMenu = 1;
          } else if (currentSubMenu == 1) {
            currentSubMenu = 2;
          }
        } else if (currentMenu == 1) {
          if (currentSubMenu == 0) {
            currentSubMenu = 1;
          } else if (currentSubMenu == 1) {
            currentSubMenu = 2;
          } else if (currentSubMenu == 2) {
            currentSubMenu = 3;
          }
        }
      } else {
        if (currentMenu == 0) {
          currentMenu = 1;
        } else if (currentMenu == 1) {
          currentSubMenu = 0;
          currentMenu = 0;
        }
      }
    }
    lastEncoderState = encoderState;
  }

  // обрабатываем нажатие на кнопку энкодера для изменения порогов или возврата на предыдущий уровень меню
  if (digitalRead(encoderButtonPin) == LOW) {
    delay(50);
    if (digitalRead(encoderButtonPin) == LOW) {
      if (currentMenu == 1 && currentSubMenu != 0) {
        currentSubMenu = 0;
      } else if (currentMenu == 1 && currentSubMenu == 0) {
        currentMenu = 0;
      } else if (currentMenu == 0 && currentSubMenu == 1) {
        // настраиваем пороги для клапанов
        currentSubMenu = 0;
      } else if (currentMenu == 0 && currentSubMenu == 2) {
        // настраиваем порог для зумера
        currentSubMenu = 0;
      }
    }
    while (digitalRead(encoderButtonPin) == LOW) {}
  }

  // обрабатываем изменение порогов для клапанов
  if (currentMenu == 1 && currentSubMenu == 1) {
    int encoderVal = analogRead(A4);
    int thresholdVal = map(encoderVal, 0, 1023, 0, 100);
    if (currentSubMenu == 1 && thresholdVal != threshold1) {
      threshold1 = thresholdVal;
      lcd.clear();
      lcd.print("Пороги клапанов");
      lcd.setCursor(0, 0);
      lcd.print("Клапан 1: ");
      lcd.print(threshold1);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Клапан 2: ");
      lcd.print(threshold2);
      lcd.print("%");
      lcd.setCursor(0, 2);
      lcd.print("Клапан 3: ");
      lcd.print(threshold3);
      lcd.print("%");
      lcd.setCursor(0, 3);
      lcd.print("Клапан 4: ");
      lcd.print(threshold4);
      lcd.print("%");
      delay(2000);
    } else if (currentSubMenu == 2 && thresholdVal != threshold2) {
      threshold2 = thresholdVal;
      lcd.clear();
      lcd.print("Пороги клапанов");
      lcd.setCursor(0, 0);
      lcd.print("Клапан 1: ");
      lcd.print(threshold1);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Клапан 2: ");
      lcd.print(threshold2);
      lcd.print("%");
      lcd.setCursor(0, 2);
      lcd.print("Клапан 3: ");
      lcd.print(threshold3);
      lcd.print("%");
      lcd.setCursor(0, 3);
      lcd.print("Клапан 4: ");
      lcd.print(threshold4);
      lcd.print("%");
      delay(2000);
    } else if (currentSubMenu == 3 && thresholdVal != threshold3) {
      threshold3 = thresholdVal;
      lcd.clear();
      lcd.print("Пороги клапанов");
      lcd.setCursor(0, 0);
      lcd.print("Клапан 1: ");
      lcd.print(threshold1);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Клапан 2: ");
      lcd.print(threshold2);
      lcd.print("%");
      lcd.setCursor(0, 2);
      lcd.print("Клапан 3: ");
      lcd.print(threshold3);
      lcd.print("%");
      lcd.setCursor(0, 3);
      lcd.print("Клапан 4: ");
      lcd.print(threshold4);
      lcd.print("%");
      delay(2000);
    } else if (currentSubMenu == 4 && thresholdVal != threshold4) {
      threshold4 = thresholdVal;
      lcd.clear();
      lcd.print("Пороги клапанов");
      lcd.setCursor(0, 0);
      lcd.print("Клапан 1: ");
      lcd.print(threshold1);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Клапан 2: ");
      lcd.print(threshold2);
      lcd.print("%");
      lcd.setCursor(0, 2);
      lcd.print("Клапан 3: ");
      lcd.print(threshold3);
      lcd.print("%");
      lcd.setCursor(0, 3);
      lcd.print("Клапан 4: ");
      lcd.print(threshold4);
      lcd.print("%");
      delay(2000);
    }
  }

  // обрабатываем изменение порога для зумера
  if (currentMenu == 1 && currentSubMenu == 2) {
    int encoderVal = analogRead(A4);
    int thresholdVal = map(encoderVal, 0, 1023, 0, 100);
    if (thresholdVal != threshold1 && thresholdVal != threshold2 && thresholdVal != threshold3 && thresholdVal != threshold4) {
      threshold1 = thresholdVal;
      threshold2 = thresholdVal;
      threshold3 = thresholdVal;
      threshold4 = thresholdVal;
      lcd.clear();
      lcd.print("Порог для зумера");
      lcd.setCursor(0, 1);
      lcd.print(thresholdVal);
      lcd.print("%");
      delay(2000);
    }
  }
}