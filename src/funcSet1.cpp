
// #include "Inclusions.h"
#include "funcSet1.h"

#include "Inclusions.h"
// #include "Definitions.h"

#define ssid "TelsaCo2"
#define password "2300723007"

WiFiClient WIFI_C;
// HTTPClient http_C;

unsigned long serialTime = 0;
unsigned long httpTime = 0;
nodeList *node1 = NULL;

char fCommand[256];

// String errF = "error at: " + __ASSERT_FUNC;
void errFunc(String err)
{
  Serial.print(err);
  Serial.print(" error at: ");
  // Serial.print(__ASSERT_FUNC);
}

WiFiClient *initWiFi(WiFiClient *pWIFI_C)
{
  pWIFI_C = (WiFiClient *)new (std::nothrow) WiFiClient;
  if (!pWIFI_C)
  {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print('.');
      delay(1000);
    }
    Serial.println(WiFi.localIP());
    return pWIFI_C;
  }
  else
  {
    errFunc("Memory");
    return NULL;
  }
}

String httpGETRequest(const char *serverName)
{
  HTTPClient *phttp_C;
  int *p = NULL;
  phttp_C = (HTTPClient *)new (std::nothrow) HTTPClient;
  p = (int *)new (std::nothrow) int;
  if (p == NULL)
  {

    // pWIFI_C = initWiFi(pWIFI_C);

    // if (!pWIFI_C)
    // {
    // #define WIFI_C (*pWIFI_C)

    // Your Domain name with URL path or IP address with path
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print('.');
      delay(1000);
    }
    Serial.println(WiFi.localIP());
    (*phttp_C).begin(WIFI_C, serverName);

    // Send HTTP POST request
    int httpResponseCode = (*phttp_C).GET(); // returns http content legth

    String payload = "{}";

    if (httpResponseCode > 0)
    {
      // Serial.print("HTTP Response code: ");
      // Serial.println(httpResponseCode);
      payload = (*phttp_C).getString();
    }
    else
    {
      // Serial.print("Error code: ");
      // Serial.println(httpResponseCode);
    }
    // Free resources
    (*phttp_C).end();
    delete phttp_C;
    return payload;
  }
  // #undef WIFI_C
  // #undef http_C
  //     }
  //     else
  //     {
  //       errFunc("Memory. WIFI");
  //       return "NULL";
  // #undef WIFI_C
  // #undef http_C
  //     }
  //   }
  else
  {
    errFunc("Memory. HTTP");
    Serial.print(__ASSERT_FUNC);
    return "NULL";
    // #undef WIFI_C
    // #undef http_C
  }
}
// extern void vPortGetHeapStats( HeapStats_t * pxHeapStats );
void getTime()
{
  String jsonBuffer;

  String serverPath = "http://worldtimeapi.org/api/ip";
  // HTTPClient phttp_C;
  // WiFiClient pWIFI_C;
  jsonBuffer = httpGETRequest(serverPath.c_str());
  // delete phttp_C;
  // delete pWIFI_C;
  JSONVar myObject = JSON.parse(jsonBuffer);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined")
  {
    Serial.println("Parsing input failed!");
    return;
  }

  Serial.print("Time: ");
  Serial.println(myObject["utc_datetime"]);
}
void Heap_Information(void)
{
  // printf("Heap_Information:\n");
  // printf("\nHeap - size: %d - ", ESP.getHeapSize());
  // printf("Free: %d - ", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  // printf("Min Free: %d - ", heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT));
  // printf("Max Alloc: %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  // multi_heap_info_t *info = NULL;
  // info = (multi_heap_info_t *)new (std::nothrow) multi_heap_info_t;
  multi_heap_info_t info;

// #define iiii (*info)
#define iiii info

  heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
  printf("Current HeapSize: %d\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));
  printf("--------------------------------------------\n");
  printf("free_blocks: %d\n", iiii.free_blocks);
  printf("largest_free block: %d\n", iiii.largest_free_block);
  printf("minimum_free bytes: %d\n", iiii.minimum_free_bytes);
  printf("total_allocated bytes: %d\n", iiii.total_allocated_bytes);
  printf("total_blocks: %d\n", iiii.total_blocks);
  printf("total_free bytes: %d\n", iiii.total_free_bytes);
  printf("total_free + total_allocated bytes: %d\n", iiii.total_free_bytes + iiii.total_allocated_bytes);

  printf("--------------------------------------------\n");
  // delete info;

  // errFunc("Memory");
}

void printFragStats()
{
  // Serial.print("free heap :");
  // Serial.print(ESP.getFreeHeap());
  // Serial.print("\n");

  // Serial.print("max acllocatable heap :");
  // Serial.println(ESP.getMaxAllocHeap());
  // Serial.print("\n");

  // Serial.print("free psram :");
  // Serial.println(ESP.getFreePsram());
  // Serial.print("\n");

  // Serial.print("max acllocatable psram :");
  // Serial.println(ESP.getMaxAllocPsram());
  // Serial.print("\n");

  HeapStats_t *xHeapStats;
  vPortGetHeapStats(xHeapStats);

  Serial.print(F(xPortGetFreeHeapSize()));
  Serial.println(xPortGetFreeHeapSize());
  Serial.print(F(xPortGetMinimumEverFreeHeapSize()));
  Serial.println(xPortGetMinimumEverFreeHeapSize());

  Serial.print(F("xHeapStats->xAvailableHeapSpaceInBytes"));
  Serial.println(xHeapStats->xAvailableHeapSpaceInBytes);

  Serial.print(F("xHeapStats->xMinimumEverFreeBytesRemaining"));
  Serial.println(xHeapStats->xMinimumEverFreeBytesRemaining);

  Serial.print(F("xHeapStats->xNumberOfFreeBlocks"));
  Serial.println((xHeapStats->xNumberOfFreeBlocks));

  Serial.print(F("xHeapStats->xNumberOfSuccessfulAllocations"));
  Serial.println(xHeapStats->xNumberOfSuccessfulAllocations);

  Serial.print(F("xHeapStats->xNumberOfSuccessfulFrees"));
  Serial.println(xHeapStats->xNumberOfSuccessfulFrees);

  Serial.print(F("xHeapStats->xSizeOfLargestFreeBlockInBytes"));
  Serial.println(xHeapStats->xSizeOfLargestFreeBlockInBytes);

  Serial.print(F("xHeapStats->xSizeOfSmallestFreeBlockInBytes"));
  Serial.println(xHeapStats->xSizeOfSmallestFreeBlockInBytes);
}
String generateRandomString()
{
  String result;
  int len = random(8, 1024);
  while (len--)
    result += '?';
  return result;
}
void goLoud(uint8_t j)
{
  for (int i = 0; i < j; i++)
  {
    generateRandomString();
  }
}
bool getCommand(uint8_t num)
{
  if (Serial.available())
  {
    fCommand[num] = Serial.read();
    if (fCommand[num] == -1)
      return 0;
    else
    {
      Serial.print("got command"); //%c ->%c", num, fCommand[num]);
      Serial.print(num);
      // String s(2,fCommand[num]);
      Serial.println(fCommand[num]);

      return 1;
    }
  }
  else
    return 0;
}
void *newChar(void *p, int size, int nMethod)
{
  switch (nMethod)
  {
  case 0:
    p = new char[size];
    break;
  case 1:
    p = new (std::nothrow) char[size];
    break;
  case 2:
    p = heap_caps_malloc(size, MALLOC_CAP_32BIT);
    break;
  case 3:
    p = heap_caps_malloc(size, MALLOC_CAP_8BIT);

  default:
    break;
  }
  return p;
}
void fillHeap(int size, int nMethod)
{
  int i = 0;
  String msg = "Allocation times: ";
  while (1)
  {
    i++;
    char *str = NULL;

    str = (char *)newChar(str, size, nMethod);
    // if (nMethod)
    //   str = (char *)new (std::nothrow) char[size];
    // else
    //   str = (char *)new char[size];
    if (str == NULL)
    {
      Serial.println("Heap Full");
      break;
    }
  }
  Serial.print(msg);
  Serial.println(i);
}
void FillHeap(bool nMethod)
{
  char *p1 = NULL;
  char *p2 = NULL;
  char *p3 = NULL;
  // p1 = New(p3 , , nMethod);
}

// void deleteAddress()
// {

// }

void getTime2()
{
  String json_array;

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Serial.println("First set of readings will appear after 10 seconds");
  if (WiFi.status() == WL_CONNECTED)
  {
    String server = "http://worldtimeapi.org/api/ip";

    json_array = GET_Request(server.c_str());
    Serial.println(json_array);
    JSONVar my_obj = JSON.parse(json_array);

    if (JSON.typeof(my_obj) == "undefined")
    {
      Serial.println("Parsing input failed!");
      return;
    }

    Serial.print("Time: ");
    Serial.println(my_obj["utc_datetime"]);
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
}

String GET_Request(const char *server)
{
  HTTPClient http;
  http.begin(server);
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return payload;
}

void smash(String str)
{
  char buffer[5];
  strcpy(buffer, str.c_str());
  Serial.print("ok");
}
int getNum()
{
  while (1)
    if (Serial.available())
    {
      return (Serial.parseInt());
      break;
    }
}
void plainSmash()
// {
//   char buf[3];
//   strcpy(buf, "123456789 hg nhgm hgj fjhfy ujdty jd ghjh d hg");
//   Serial.print("ok");
// }
{
  char buffer[16];
  strcpy(buffer, "This text is longer than 16 bytes!");
  strcpy(buffer, "123456789123456");
}
// bool addToList()
// {
// }
// struct nodeList
// {
//   void *data;
//   nodeList *next;
// };

// nodeList *node1 = NULL;

// Allocate a block of memory and add it to the free list
void addBlockToFreeList(size_t size)
{
  void *mem = NULL;
  mem = heap_caps_malloc(size, MALLOC_CAP_DEFAULT);
  if (mem == NULL)
  {
    Serial.println("Error: Out of memory");
    return;
  }
  nodeList *node = new nodeList{mem, node1};
  node1 = node;
}

// Allocate a block of memory from the free list
void *allocateFromFreeList(size_t size)
{
  nodeList *prev = nullptr;
  nodeList *curr = node1;
  while (curr != nullptr)
  {
    if (heap_caps_get_free_size(MALLOC_CAP_DEFAULT) >= size)
    {
      // Found a block of memory that is big enough
      void *mem = curr->data;
      if (prev == nullptr)
      {
        node1 = curr->next;
      }
      else
      {
        prev->next = curr->next;
      }
      delete curr;
      return mem;
    }
    prev = curr;
    curr = curr->next;
  }
  // No free blocks available, add a new block to the free list
  addBlockToFreeList(size);
  return allocateFromFreeList(size); // Try again
}



class Stack {
public:
  Stack() {
    top_ = NULL;
  }

  void push(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = top_;
    top_ = node;
  }

  int pop() {
    if (top_ == NULL) {
      return -1;
    }
    int data = top_->data;
    Node* node = top_;
    top_ = top_->next;
    free(node);
    return data;
  }

private:
  Node* top_;
};
