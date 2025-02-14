#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "wifi_config.h"
#include "azure_iot_config.h"
#include "certificates.h"
#include "sensor.h"

// Instancias
WiFiClientSecure espClient;
PubSubClient client(espClient);

// Conexión WiFi
void connectToWiFi() {
    Serial.print("Conectando a WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(" Conectado!");
}

// Conexión a Azure IoT Hub
void connectAzureIoT() {
    espClient.setCACert(root_ca);
    espClient.setCertificate(client_cert);
    espClient.setPrivateKey(client_key);
    client.setServer(MQTT_SERVER, 8883);

    Serial.print("Conectando a Azure IoT Hub...");
    while (!client.connect(DEVICE_ID)) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" Conectado!");
}

void setup() {
    Serial.begin(115200);
    setupSensor();
    connectToWiFi();
    connectAzureIoT();
}

void loop() {
    if (!client.connected()) {
        connectAzureIoT();
    }

    float temperature = getTemperature();
    float humidity = getHumidity();

    StaticJsonDocument<200> doc;
    doc["deviceId"] = DEVICE_ID;
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["timestamp"] = millis();

    char buffer[256];
    serializeJson(doc, buffer);

    client.publish(MQTT_TOPIC, buffer);
    Serial.println("Datos enviados: " + String(buffer));

    delay(5000);
}
