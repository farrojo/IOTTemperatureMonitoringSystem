#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>

// Definicion de PIN y tipo de sensor
#define DHTPIN 4         
#define DHTTYPE DHT22    

// Instancia del sensor DHT
extern DHT dht;

void setupSensor();
float getTemperature();
float getHumidity();

#endif
