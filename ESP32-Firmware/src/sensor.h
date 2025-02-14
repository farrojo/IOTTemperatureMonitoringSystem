#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>

// Definir el pin del sensor y el tipo de sensor
#define DHTPIN 4         
#define DHTTYPE DHT22    // DHT11 o DHT22

DHT dht(DHTPIN, DHTTYPE);

void setupSensor();
float getTemperature();
float getHumidity();

#endif
