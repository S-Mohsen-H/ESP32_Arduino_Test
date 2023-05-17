#ifndef FUNCSET1_H
#define FUNCSET1_H

#include "Definitions.h"

struct Node
{
    int data;
    Node *next;
};

extern WiFiClient *initWiFi(WiFiClient *pWIFI_C);
extern String httpGETRequest(const char *serverName);
extern void printFragStats();
// extern String generateRandomString();
extern bool getCommand(uint8_t num);
extern void goLoud(uint8_t j);
extern void fillHeap(int size, int nMethod);
extern void Heap_Information(void);
extern void errFunc(String err);
extern void FillHeap(bool nMethod);
extern void *newChar(void *p, int size, int nMethod);
extern void getTime();

extern void getTime2();
extern String GET_Request(const char *server);
extern void smash(String str);
extern int getNum();
extern void plainSmash();
// extern bool addToList();

#endif