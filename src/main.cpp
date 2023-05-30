#include "Arduino.h"

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
BluetoothA2DPSource a2dp_source;
SoundData *data = new OneChannelSoundData((int16_t *)piano16bit_raw, piano16bit_raw_len / 2);
int32_t get_data_frames(Frame *frame, int32_t frame_count);
void setup()
{
  HeapRegion_t reg;
  // BluetoothA2DPSource a2dp_SOurce;

  //  vPortDefineHeapRegions(xHeapRegions);
  // heap_caps_add_region();
  // SPIFFS.begin(true, "/SPIFFS", 10U, NULL);
  Serial.begin(115200);
}

void loop()
{

  getCommand(0);
  // printf("nope0");

  switch (fCommand[0])
  {
  case 'k':
  {
    Serial.println(a2dp_source.get_connection_state());
    break;
  }
  case 'j':
  {
    a2dp_source.write_data(data);
    break;
  }
  case 'i':
  {
    a2dp_source.start("AWEI Music"); // TSCO-TH5365TWS
    a2dp_source.set_local_name("ESP32 a2dp SOUrce");
    a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
    a2dp_source.set_volume(20);

    break;
  }
  case 'h':
  {
    BluetoothA2DPSource a2dp_SOurce;

    a2dp_SOurce.start("TSCO-TH5365TWS", get_data_frames);
    a2dp_SOurce.set_volume(30);
    break;
  }
  case 'g':
  {
    Serial.println(String(sizeof(HTTPClient)));
    break;
  }
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

// #include "Arduino.h"
// #include "BluetoothA2DPSource.h"
// #include "Arduino.h"
// #include <math.h>

// #define c3_frequency 500

// BluetoothA2DPSource a2dp_source;

// // The supported audio codec in ESP32 A2DP is SBC. SBC audio stream is encoded
// // from PCM data normally formatted as 44.1kHz sampling rate, two-channel 16-bit sample data
// int32_t get_data_frames(Frame *frame, int32_t frame_count)
// {
//     static float m_time = 0.0;
//     float m_amplitude = 10000.0; // -32,768 to 32,767
//     float m_deltaTime = 1.0 / 44100.0;
//     float m_phase = 0.0;
//     float pi_2 = PI * 2.0;
//     // fill the channel data
//     for (int sample = 0; sample < frame_count; ++sample)
//     {
//         float angle = pi_2 * c3_frequency * m_time + m_phase;
//         frame[sample].channel1 = m_amplitude * sin(angle);
//         frame[sample].channel2 = frame[sample].channel1;
//         m_time += m_deltaTime;
//     }

//     return frame_count;
// }

// void setup()
// {
//      a2dp_source.set_auto_reconnect(true);
//     a2dp_source.start("TSCO-TH5365TWS", get_data_frames);
//     a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);

//     a2dp_source.set_volume(150);
// }

// void loop()
// {
//     // to prevent watchdog in release > 1.0.6
//     delay(10);
// }

// #include "BluetoothA2DPSource.h" //////////code on sink
// #include "piano16bit.h"

// void a2dp_start()
// {
//   // a2dp_source.set_auto_reconnect(false);
//   Serial.println(a2dp_source.get_connection_state());
//   Serial.println("1");

//   // a2dp_source.start("AWEI Music"); // TSCO-TH5365TWS
//   // a2dp_source.set_local_name("ESP32 a2dp SOUrce");
//   // a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
//   // Serial.println(a2dp_source.get_connection_state());
//   // Serial.println("2");

//   // a2dp_source.set_volume(20);
//   // a2dp_source.write_data(data);
// }
// // ==> Example A2DP Receiver which uses I2S to an external DAC

// #include "BluetoothA2DPSink.h"   //////////code on source

// BluetoothA2DPSink a2dp_sink;

// void setup() {
//   Serial.begin(115200);
//   a2dp_sink.start("TH5365TWS");

// }

// void loop() {
//   delay(1000); // do nothing
//   Serial.println(a2dp_sink.is_connected());
// }
