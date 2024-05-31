<<<<<<< HEAD:include/HashMap.h
#ifndef HASHMAP_H
#define HASHMAP_H
#include "MaxHeap.h"
=======
#include "AVLtree.h"
>>>>>>> upstream/master:HashMap.h

#include <stdbool.h>
#include <stdint.h>

#define INITIAL_CAPACITY 16

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

uint64_t hash_key(const char *key);

typedef enum TypeEntry { PROCESS, FUNCTION } TypeEntry;

typedef struct {
  char *key;
  void *value;
} Entry;

typedef struct {
  Entry *entries;

  int capacity;
  int length;
} HashMap;

HashMap *newHashMap();
void showHashMapByState(HashMap *map, State state);
void deallocHashMap(HashMap *map);
<<<<<<< HEAD:include/HashMap.h
int *getHashMap(HashMap *map, char *key);
void setEntryHashMap(HashMap *map, char *key, int *value);
HashMap *expandHashMap(HashMap *map);
bool setHashMap(HashMap *map, char *key, int *value);
void diagnosticHashMap(HashMap *map);

#endif

=======
void *getHashMap(HashMap *map, char *key);
bool expandHashMap(HashMap *map);
bool setHashMap(HashMap *map, char *key, void *value);
void diagnosticHashMap(HashMap *map, TypeEntry type);
>>>>>>> upstream/master:HashMap.h
