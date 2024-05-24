#include "HashMap.h"

#define INITIAL_CAPACITY 16

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

uint64_t hash_key(const char *key) {
  uint64_t hash = FNV_OFFSET;
  for (const char *p = key; *p; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }
  return hash;
}

HashMap *newHashMap() {

  HashMap *map = malloc(sizeof(HashMap));
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

int *getHashMap(HashMap *map, char *key) {
  uint64_t hash = hash_key(key);
  int index = (hash & (map->capacity - 1));

  while (map->entries[index].key) {
    if (!strcmp(key, map->entries[index].key))
      return map->entries[index].value;

    index = (index + 1) % map->capacity;
  }

  return NULL;
}

void setEntryHashMap(HashMap *map, char *key, int *value) {
  uint64_t hash = hash_key(key);
  int index = (uint64_t)(hash & (map->capacity - 1));

  while (map->entries[index].key) {
    if (!strcmp(key, map->entries[index].key)) {
      map->entries[index].value = value;
      return;
    }

    index = (index + 1) % map->capacity;
  }

  key = strdup(key);
  if (!key)
    return;
  map->length++;

  map->entries[index].key = key;
  map->entries[index].value = value;
}

HashMap *expandHashMap(HashMap *map) {
  int newCapacity = map->capacity * 2;

  HashMap *newMap = calloc(1, sizeof(HashMap));

  Entry *newEntries = calloc(newCapacity, sizeof(Entry));
  if (!newEntries)
    return NULL;

  newMap->capacity = newCapacity;
  newMap->entries = newEntries;
  newMap->length = 0;

  for (int i = 0; i < map->capacity; i++) {
    Entry entry = map->entries[i];

    if (entry.key) {
      setEntryHashMap(newMap, entry.key, entry.value);
    }
  }

  deallocHashMap(map);

  return newMap;
}

bool setHashMap(HashMap *map, char *key, int *value) {
  if (!value)
    return false;

  if (map->length == map->capacity)
    if (!(map = expandHashMap(map)))
      return false;

  setEntryHashMap(map, key, value);
  return true;
}

void diagnosticHashMap(HashMap *map) {
  if (!map)
    return;

  printf("Map address: %p\n", map);
  printf("Map size: %d\n", map->length);
  printf("Map capacity: %d\n", map->capacity);

  for (int i = 0; i < map->capacity; i++) {
    if (map->entries[i].key) {
      printf("[%d] | %s -> %d\n", i, map->entries[i].key,
             (*map->entries[i].value));
    } else {
      printf("[%d] Nothing here\n", i);
    }
  }
}
