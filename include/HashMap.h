#ifndef HASHMAP_H
#define HASHMAP_H
#include "MaxHeap.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 16

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

uint64_t hash_key(const char *key);

typedef struct {
  char *key;
  int *value;
} Entry;

typedef struct {
  Entry *entries;

  int capacity;
  int length;
} HashMap;

HashMap *newHashMap();
void deallocHashMap(HashMap *map);
int *getHashMap(HashMap *map, char *key);
void setEntryHashMap(HashMap *map, char *key, int *value);
HashMap *expandHashMap(HashMap *map);
bool setHashMap(HashMap *map, char *key, int *value);
void diagnosticHashMap(HashMap *map);

#endif

