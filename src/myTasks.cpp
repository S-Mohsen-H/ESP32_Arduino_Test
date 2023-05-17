#include "Inclusions.h"
#include "myTasks.h"
void task1(void *a)
{
  while (1)
  {
    char *str = NULL;

    str = (char *)new (std::nothrow) char;

    if (str == NULL)
    {
      Serial.println("Heap Full");
      break;
    }
  }
}
void task2(void *a)
{
  while (1)
  {
    char *str = NULL;

    str = (char *)new (std::nothrow) char;

    if (str == NULL)
    {
      Serial.println("Heap Full");
      break;
    }
  }
}