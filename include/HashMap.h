#include "AVLtree.h"
#include <stdbool.h>
#include <stdint.h>

#define INITIAL_CAPACITY 16

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct {
  char *key;
  void *value;
} Entry;

typedef struct {
  Entry *entries;

  int capacity;
  int length;
  int colisionTracker;
} HashMap;

HashMap *newHashMap();
void showHashMapByState(HashMap *map, State state);
void deallocHashMap(HashMap *map);
void *getHashMap(HashMap *map, char *key, bool isFnv, bool isLinear);
// bool expandHashMap(HashMap *map);
void printProcess(Node *node);
bool setHashMap(HashMap *map, char *key, void *value, bool isFnv,
                bool isLinear);
// void diagnosticHashMap(HashMap *map, TypeEntry type);
void deleteHashMap(HashMap *map, char *key, bool isFnv, bool isLinear);
