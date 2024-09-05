#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ESP32Firebase.h>
#include <PulseSensorPlayground.h>

#define WIFI_SSID "xxxxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxx"   
#define REFERENCE_URL "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  

// Define the I2C pins for ESP32
#define CUSTOM_SDA_PIN 21
#define CUSTOM_SCL_PIN 22 

PulseSensorPlayground pulseSensor;

Firebase firebase(REFERENCE_URL);

Adafruit_BMP280 bmp280; // Create an instance of the BMP280 class

void setup() {
  Serial.begin(115200); // Initialize the serial communication
   WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  
  Wire.begin(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN); 

  Serial.println("I2C Initialized");

  if (!bmp280.begin(0x76)) { // Initialize the BMP280 sensor with the default I2C address
    Serial.println("Could not find a valid BMP280 sensor, check wiring or address!");
    while (1); // Stay in a loop if the sensor is not found
  }

  bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,
                     Adafruit_BMP280::SAMPLING_X2, // Temperature sampling
                     Adafruit_BMP280::SAMPLING_X16, // Pressure sampling
                     Adafruit_BMP280::FILTER_X16,
                     Adafruit_BMP280::STANDBY_MS_500);

  pulseSensor.analogInput(34); // Set the analog pin used for the pulse sensor
  pulseSensor.setThreshold(550); // Set the threshold for detecting pulses
  pulseSensor.begin(); // Initialize the pulse sensor
}

void loop() {
  float temperature = bmp280.readTemperature(); // Read the temperature from the sensor
    // Convert temperature to a string with two decimal points
  String temperatureString = String(temperature, 2);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C"); // Print the temperature to the serial monitor

  firebase.setString("numbers/number3", temperatureString);
  if(temperature > 38){
    firebase.setInt("sensors/sensor3", 1);
  }else{
    firebase.setInt("sensors/sensor3", 0);
  }

  int bpm = pulseSensor.getBeatsPerMinute(); // Get the current BPM
  if (pulseSensor.sawStartOfBeat()) { // If a beat is detected
    Serial.println("Heartbeat detected!");
    Serial.print("Current BPM: ");
    Serial.println(bpm);
    firebase.setInt("numbers/number1", bpm);
  }


  if(bpm > 120){
    firebase.setInt("sensors/sensor1", 1);
  }else{
    firebase.setInt("sensors/sensor1", 0);
  }
}
