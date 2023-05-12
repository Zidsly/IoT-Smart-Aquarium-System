#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 5 // ESP32 pin GIOP21 connected to DS18B20 sensor's DQ pin
#define RELAY_PIN 4 // ESP32 pin GIOP22 connected to relay's IN pin

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701


#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ARDUINO_ARCH_ESP32)
  #include <WiFi.h>
#endif

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "ipok" ;   // your network SSID (name)
char pass[] = "apaluliat7"  ;  // your network password (use for WPA, or use as key for WEP)

// To connect with SSL/TLS:
// 1) Change WiFiClient to WiFiSSLClient.
// 2) Change port value from 1883 to 8883.
// 3) Change broker value to a server with a known SSL/TLS root certificate 
//    flashed in the WiFi module.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic_suhu[]  = "home/suhu";
const char topic_jarak[] = "home/jarak";

const int trigPin = 12;
const int echoPin = 14;

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit
long duration;
float distanceCm;
float distanceInch;


void ultrasonik() {  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  mqttClient.beginMessage(topic_jarak);
  mqttClient.print(distanceCm);
  mqttClient.endMessage();
  
  delay(3000);
}

void setup() {
    //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
 

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  // You can provide a username and password for authentication
  // mqttClient.setUsernamePassword("username", "password");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  
 if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  DS18B20.begin();    // initialize the DS18B20 sensor
  pinMode(RELAY_PIN, OUTPUT); // set relay pin as output
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
    mqttClient.poll();
    
    DS18B20.requestTemperatures();       // send the command to get temperatures
    tempC = DS18B20.getTempCByIndex(0);  // read temperature in °C
    tempF = tempC * 9 / 5 + 32; // convert °C to °F
    ultrasonik();

    Serial.print("Temperature: ");
    Serial.print(tempC);    // print the temperature in °C
    Serial.print("°C");
    Serial.print("  ~  ");  // separator between °C and °F
    Serial.print(tempF);    // print the temperature in °F
    Serial.println("°F");
    
    mqttClient.beginMessage(topic_suhu);
    mqttClient.print(tempC);
    mqttClient.endMessage();
    
    delay(500);
    if (tempC < 30) {
//      mqttClient.beginMessage(topic_suhu);
//      mqttClient.print("Heater ON");
//      mqttClient.endMessage();

        digitalWrite(RELAY_PIN, LOW); // turn on the relay
        Serial.println("Relay is ON");
        delay(10000);

    } else {
        
        digitalWrite(RELAY_PIN, HIGH); // turn off the relay
    }
}
