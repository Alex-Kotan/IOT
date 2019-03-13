#include <ESP8266WiFi.h> // библиотека для использования чипа WIFI
#include <BlynkSimpleEsp8266.h> // Библиотека для подключения к сервис Blynk
#include <DHT.h> // библиотека для работы с датчиком DHT11
int stat = 0;

char auth[] = "e63aab07d9384d6bb0204baac597bc3c"; //Blynk token полученный при регистрации
char ssid[] = "ssid"; //WIFI SSID имя сети
char pass[] = "pass"; // пароль от сети

#define DHTPIN 14          // к какому пину подключен датчик
#define DHTTYPE DHT11     // используем DHT 11


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() //юлок работы с дачиком DHT11
{
  float h = dht.readHumidity(); //считываем уровень влажности
  float t = dht.readTemperature(); // считываем температуру

  
 {
  Blynk.virtualWrite(V5, h); //указываем виртуальный пин для влажности
  Blynk.virtualWrite(V6, t); //указываем виртуальный пин для температуры
 }
}

void setup() //блок работы с сервисом Blynk
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass); //взять данные из переменных


  dht.begin(); //передача данных от DHT11

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
BLYNK_WRITE(V1) // read data from DHT 11
{
  stat = param.asInt();
  }

void loop() //цикл запуска процедур для работы с сервисом Blynk
{
  Blynk.run();
  timer.run();
}
