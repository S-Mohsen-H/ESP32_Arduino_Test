#include "Inclusions.h"
#include "funcSet1.h"
#include "MemoryPool.h"
#include "esp_heap_caps.h"
#include "esp_heap_trace.h"
// #include "heap_4.c"
// spiffs_config cfg;
const HeapRegion_t xHeapRegions[] = {
    {(uint8_t *)0x3f800000, 0x4000},
    {(uint8_t *)0x3f840000, 0x4000},
    {NULL, 0}};
void setup()
{
  HeapRegion_t reg;

  //vPortDefineHeapRegions(xHeapRegions);
heap_caps_add_re  gion()
  SPIFFS.begin(true, "/SPIFFS", 10U, NULL);
  Serial.begin(115200);
}

void loop()
{

  getCommand(0);
  // printf("nope0");

  switch (fCommand[0])
  {
  case 'c': // mempool
  {
    const size_t blockSize = 32;
    const uint8_t blockCount = 10;
    MemoryPool memoryPool(blockSize, blockCount);
    void *ptr = nullptr;
    ptr = memoryPool.allocate();
    if (!(ptr == nullptr))
    {
      Serial.println(F("Memory allocated from the memory pool."));

      // Use the memory (e.g., store data, perform calculations, etc.)
      // ptr = (char *)ptr;
      strcpy((char *)ptr, (char *)F("hi this is a text in flash"));

      Serial.println((char *)ptr);
      // Deallocate the memory when done
      memoryPool.deallocate(ptr);
      Serial.println(F("Memory deallocated."));
    }
    else
    {
      Serial.println(F("Memory allocation failed."));
    }
    break;
  }
  case 'd': // mempool doesn't deallocate
  {
    const size_t blockSize = 32;
    const uint8_t blockCount = 10;
    MemoryPool memoryPool(blockSize, blockCount);
    void *ptr = nullptr;
    ptr = memoryPool.allocate();
    if (!(ptr == nullptr))
    {
      Serial.println(F("Memory allocated from the memory pool."));

      // Use the memory (e.g., store data, perform calculations, etc.)
      // ptr = (char *)ptr;
      strcpy((char *)ptr, (char *)F("hi this is a text in flash"));

      Serial.println((char *)ptr);
      // Deallocate the memory when done
      // memoryPool.deallocate(ptr);
      Serial.println(F("Memory deallocated."));
    }
    else
    {
      Serial.println(F("Memory allocation failed."));
    }
    break;
  }
  case 'e': // 1 new char without free
  {
    char *ptr = new (std::nothrow) char;
  }
  break;
  case 'f': // 1 new char with free
  {
    char *ptr = new (std::nothrow) char;
    free(ptr);
  }
  break;
  case '1':
    Serial.println(F("something"));
    Serial.println(F("something else"));
    break;
  case '2':
    Heap_Information();
    break;
  case '3':
    fillHeap(1, 1);
    break;
  case '4':
    fillHeap(1, 0);
    break;
  case '9':
    fillHeap(1, 2);
    break;
  case 'a':
    fillHeap(1, 3);
    break;
  case 'b':
    Serial.println(heap_caps_get_largest_free_block(MALLOC_CAP_32BIT));
    Serial.println(heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

    Serial.println(heap_caps_get_free_size(MALLOC_CAP_32BIT));
    Serial.println(heap_caps_get_free_size(MALLOC_CAP_8BIT));
    heap_caps_dump(MALLOC_CAP_8BIT);
    heap_caps_dump(MALLOC_CAP_32BIT);

    Serial.println(heap_caps_check_integrity_all(1));

    break;

  case '5':
    getTime();
    break;
  case '6':
    getTime2();
    break;
  case '7':
    plainSmash();
    break;
  case '8':
    Serial.println("\nSelect size: ");
    // if (!getCommand(1))
    //   Serial.printf("nope1");
    getCommand(1);
    switch (fCommand[1])
    {
    case 'a':
      smash("1234");
      break;
    case 'b':
      smash("12345");
      break;
    case 'c':
      smash("123456789");
      break;

    default:
      break;
    }

    break;
  default:
    break;
  }
  for (int i = 0; i < 256; i++)
    fCommand[i] = '0';
}
