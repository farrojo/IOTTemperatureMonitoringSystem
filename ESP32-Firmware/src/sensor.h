#ifndef SENSOR_H
#define SENSOR_H

#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setupSensor();
float getTemperature();
float getHumidity();

#endif
