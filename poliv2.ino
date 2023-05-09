#include <SPI.h>
#include <Wire.h>

 #include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x3F
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#define SENSOR_COUNT 6
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

int PIN_LED1 = 7;       // led2 connected at pin 7 (второй светодиод) PIN_LED1 8 // Определяем пин, используемый для подключения реле 6
const int AirValue = 790;   //you need to replace this value with Value_1
const int WaterValue = 250;  //you need to replace this value with Value_2

int ledState = LOW; // состояние светодиода
// последний момент времени, когда состояние светодиода изменялось
unsigned long previousMillis = 0;
unsigned long previousMillisTFT = 0;
long intervalled = 36000000; // длительность свечения светодиода (в миллисекундах)
long intervalTFT = 10000; // длительность свечения светодиода (в миллисекундах)  

const int SensorPin1 = A0;
const int SensorPin2 = A1;
const int SensorPin3 = A2;
const int SensorPin4 = A3;
int soilMoistureValue1 = 0;
int soilMoistureValue2 = 0;
int soilMoistureValue3 = 0;
int soilMoistureValue4 = 0;
int soilmoisturepercent1=0;
int soilmoisturepercent2=0;
int soilmoisturepercent3=0;
int soilmoisturepercent4=0;

void setup() {
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
    lcd.init();
    lcd.noBacklight();
    lcd.setCursor(0, 0);
    lcd.print("Moisture");
    pinMode(PIN_LED1, OUTPUT); // Объявляем пин реле как выход
    digitalWrite(PIN_LED1, HIGH); // Выключаем реле - посылаем высокий сигнал
}
 
 
void loop() 
{
unsigned long currentMillis = millis();
  
  //проверяем не прошел ли нужный интервал, если прошел то
  if(currentMillis - previousMillis > intervalled) {
    // сохраняем время последнего переключения
    previousMillis = currentMillis; 
 
    // если светодиод не горит, то зажигаем, и наоборот
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
 
    // устанавливаем состояния выхода, чтобы включить или выключить светодиод
    digitalWrite(PIN_LED1, ledState);
  }

    float sensorValue1 = analogRead(SensorPin1);
    float sensorValue2 = analogRead(SensorPin2);
    float sensorValue3 = analogRead(SensorPin3);
    float sensorValue4 = analogRead(SensorPin4);
  
  soilMoistureValue1 = analogRead(SensorPin1);  //put Sensor insert into soil
  soilMoistureValue2 = analogRead(SensorPin2);  //put Sensor insert into soil
  soilMoistureValue3 = analogRead(SensorPin3);  //put Sensor insert into soil
  soilMoistureValue4 = analogRead(SensorPin4);  //put Sensor insert into soil
  soilmoisturepercent1 = map(soilMoistureValue1, AirValue, WaterValue, 0, 100);
  soilmoisturepercent2 = map(soilMoistureValue2, AirValue, WaterValue, 0, 100);
  soilmoisturepercent3 = map(soilMoistureValue3, AirValue, WaterValue, 0, 100);
  soilmoisturepercent4 = map(soilMoistureValue4, AirValue, WaterValue, 0, 100);
 //проверяем не прошел ли нужный интервал, если прошел то
/////////////////////////////////////////////////////////////////////////////////////////

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture levels:");
    lcd.print("S- ");

    lcd.print(soilmoisturepercent1);
    lcd.print("  ");
    /*
  delay(10000);
  display.clearDisplay();
  display.setCursor(40,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");

  display.setCursor(2,20);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil D1- ");
  display.setCursor(55,20);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent1);
  display.setCursor(65,20);
  display.setTextSize(1);
  display.println(" %");

  display.setCursor(2,32);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil D2- ");
  display.setCursor(55,32);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent2);
  display.setCursor(65,32);
  display.setTextSize(1);
  display.println(" %");

  display.setCursor(2,44);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil D3- ");
  display.setCursor(55,44);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent3);
  display.setCursor(65,44);
  display.setTextSize(1);
  display.println(" %");

  display.setCursor(2,56);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil D4- ");
  display.setCursor(55,56);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent4);
  display.setCursor(65,56);
  display.setTextSize(1);
  display.println(" %");
  display.display();
  */
}
