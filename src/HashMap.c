#include "../include/../include/HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t fnvHash(const char *key) {
  uint64_t hash = FNV_OFFSET;
  for (const char *p = key; *p; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }

  return hash;
}

uint64_t djb2Hash(char *key) {
  uint64_t hash = 5381;
  int c;

  while ((c = *key++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

HashMap *newHashMap() {
  HashMap *map = calloc(1, sizeof(HashMap));
  if (!map)
    return NULL;

  map->length = 0;
  map->capacity = INITIAL_CAPACITY;

  map->entries = calloc(map->capacity, sizeof(Entry));
  if (!map->entries) {
    free(map);
    return NULL;
  }

  return map;
}

void deallocHashMap(HashMap *map) {
  for (size_t i = 0; i < map->capacity; i++)
    free(map->entries[i].key);

  free(map->entries);
  free(map);
}

void *getHashMap(HashMap *map, char *key, bool isFnv, bool isLinear) {
  uint64_t hash;
  if (isFnv)
    hash = fnvHash(key);
  else
    hash = djb2Hash(key);

  int index = (hash & (map->capacity - 1));

  int i = 0, initial = index;
  while (map->entries[index].key) {
    if (!strcmp(key, map->entries[index].key))
      return map->entries[index].value;

    if (isLinear)
      index = (initial + i) % map->capacity;
    else
      index = (initial + i * i) % map->capacity;

    i += 1;
  }

  return NULL;
}

char *setEntryHashMap(Entry *entries, char *key, void *value, int capacity,
                      int *plength, bool isFnv, bool isLinear) {
  uint64_t hash;
  if (isFnv)
    hash = fnvHash(key);
  else
    hash = djb2Hash(key);

  size_t index = (size_t)(hash & (uint64_t)(capacity - 1));
  int i = 0, initial = index;
  while (entries[index].key != NULL) {
    if (strcmp(key, entries[index].key) == 0) {
      entries[index].value = value;
      return entries[index].key;
    }

    if (isLinear)
      index = (initial + i) % capacity;
    else
      index = (initial + i * i) % capacity;

    i += 1;
  }

  if (plength) {
    key = strdup(key);
    if (!key)
      return NULL;

    (*plength)++;
  }

  entries[index].key = (char *)key;
  entries[index].value = value;
  return key;
}

void deleteHashMap(HashMap *map, char *key, bool isFnv, bool isLinear) {
  uint64_t hash;
  if (isFnv)
    hash = fnvHash(key);
  else
    hash = djb2Hash(key);
  size_t index = (size_t)(hash & (uint64_t)(map->capacity - 1));

  int i = 0, initial = index;
  while (map->entries[index].key) {
    if (strcmp(key, map->entries[index].key) == 0) {
      map->entries[index].value = map->entries[index].key = NULL;
      map->length--;
      return;
    }

    if (isLinear)
      index = (initial + i) % map->capacity;
    else
      index = (initial + i * i) % map->capacity;
    i += 1;
  }
}

bool expandHashMap(HashMap *map, bool isFnv, bool isLinear) {
  int new_capacity = map->capacity * 2;
  if (new_capacity < map->capacity)
    return false;

  Entry *new_entries = calloc(new_capacity, sizeof(Entry));
  if (!new_entries)
    return false;

  for (int i = 0; i < map->capacity; i++) {
    Entry entry = map->entries[i];

    if (entry.key)
      setEntryHashMap(new_entries, entry.key, entry.value, new_capacity, NULL,
                      isFnv, isLinear);
  }

  free(map->entries);

  map->entries = new_entries;
  map->capacity = new_capacity;

  return true;
}

bool setHashMap(HashMap *map, char *key, void *value, bool isFnv,
                bool isLinear) {
  if (!value || !key || !map)
    return false;

  if (map->length == map->capacity)
    if (!expandHashMap(map, isFnv, isLinear))
      return false;

  setEntryHashMap(map->entries, key, value, map->capacity, &map->length, isFnv,
                  isLinear);
  return true;
}

void printProcess(Node *node) {
  if (node)
    printf(" PID: %8d\t | name: %-25s | state: %-20s\t | "
           "priority: %5d\n",
           node->pid, node->name, displayState(node->state), node->priority);
}

void showHashMapByState(HashMap *map, State state) {
  if (!map || !map->entries)
    return;

  for (int i = 0; i < map->capacity; i++)
    if ((Node *)map->entries[i].value)
      if (((Node *)(map->entries[i].value))->state == state)
        printProcess((Node *)map->entries[i].value);
}
