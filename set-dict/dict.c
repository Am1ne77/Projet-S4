#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

struct set
{
        size_t capacity;
        size_t size;
        struct data elements[capacity];
};

struct data
{
        uint32_t hkey;
        char* key;
	void* value;
        struct data* next;
};

uint32_t hash(char *key)
{
  size_t i = 0;
  uint32_t hash = 0;
  while (key != NULL)
  {
    hash += *(key++);
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

