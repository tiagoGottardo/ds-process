#include "../include/HashMap.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t hash_key(const char *key) {
  uint64_t hash = FNV_OFFSET;
  for (const char *p = key; *p; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }
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

void *getHashMap(HashMap *map, char *key) {
  uint64_t hash = hash_key(key);
  int index = (hash & (map->capacity - 1));

  while (map->entries[index].key) {
    if (!strcmp(key, map->entries[index].key))
      return map->entries[index].value;

    index = (index + 1) % map->capacity;
  }

  return NULL;
}

char *setEntryHashMap(Entry *entries, char *key, void *value, int capacity,
                      int *plength) {
  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

  while (entries[index].key != NULL) {
    if (strcmp(key, entries[index].key) == 0) {
      entries[index].value = value;
      return entries[index].key;
    }

    index = (index + 1) % capacity;
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

bool expandHashMap(HashMap *map) {
  int new_capacity = map->capacity * 2;
  if (new_capacity < map->capacity)
    return false;

  Entry *new_entries = calloc(new_capacity, sizeof(Entry));
  if (!new_entries)
    return false;

  for (int i = 0; i < map->capacity; i++) {
    Entry entry = map->entries[i];

    if (entry.key) {
      setEntryHashMap(new_entries, entry.key, entry.value, new_capacity, NULL);
    }
  }

  free(map->entries);

  map->entries = new_entries;
  map->capacity = new_capacity;

  return true;
}

bool setHashMap(HashMap *map, char *key, void *value) {
  if (!value || !key || !map)
    return false;

  if (map->length == map->capacity)
    if (!expandHashMap(map))
      return false;

  setEntryHashMap(map->entries, key, value, map->capacity, &map->length);
  return true;
}

void printProcess(Node *node) {
  if (node) {
    printf("PID: %d\t | name: %-25s \t | state: %s\t | "
           "priority: %d\n",
           node->pid, node->name, displayState(node->state), node->priority);
  }
}

void showHashMapByState(HashMap *map, State state) {
  if (!map || !map->entries)
    return;
  for (int i = 0; i < map->capacity; i++) {
    if (((Node *)map->entries[i].value))
      if (((Node *)map->entries[i].value)->state == state)
        printProcess((Node *)map->entries[i].value);
  }
}

void showHashMap(HashMap *map, TypeEntry type) {
  switch (type) {
  case PROCESS:
    for (int i = 0; i < map->capacity; i++) {
      printProcess((Node *)map->entries[i].value);
    }
    break;
  case FUNCTION:
    // for (int i = 0; i < map->capacity; i++) {
    //     printNode((Node *)map->entries[i].value);
    // }
    break;
  }
}

void diagnosticHashMap(HashMap *map, TypeEntry type) {
  if (!map)
    return;

  printf("Map address: %p\n", map);
  printf("Map size: %d\n", map->length);
  printf("Map capacity: %d\n", map->capacity);

  showHashMap(map, type);
}
