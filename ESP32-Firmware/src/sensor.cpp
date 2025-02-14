#include "sensor.h"

DHT dht(DHTPIN, DHTTYPE);

void setupSensor() {
    dht.begin();
}

float getTemperature() {
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("❌ Error al leer la temperatura");
        return -1;
    }
    return temp;
}

float getHumidity() {
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        Serial.println("❌ Error al leer la humedad");
        return -1;
    }
    return humidity;
}
