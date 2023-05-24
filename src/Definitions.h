#include "Inclusions.h"

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define ssid "TelsaCo2"
#define password "2300723007"
#define c3_frequency 130.81


extern WiFiClient WIFI_C;
// extern HTTPClient http_C;

extern unsigned long httpTime;
extern unsigned long serialTime;
struct nodeList
{
    void *data;
    nodeList *next;
};
extern nodeList *node1;

// extern String jsonBuffer;

extern char fCommand[256];

#endif