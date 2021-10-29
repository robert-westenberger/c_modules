/** 
 * Separate Chaining map using linked lists.
 * From https://www.andreinc.net/2021/10/02/implementing-hash-tables-in-c-part-1
 * This is a naive implementation, it is not cache friendly since it use a linked list.
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#ifndef MAP2_H
#define MAP2_H

#define HASH_CAPACITY_INIT 32
#define HASH_CAPACITY_MULT 2
#define HASH_GROWTH 1

typedef struct MapNode
{
  uint32_t hash;
  void *key;
  void *val;
  struct MapNode *next;
} MapNode;

/* MapNodeKeyOps and MapNodeValOps are traits that allow users to 
specify how the hash is computed, how its copied and how memory is managed. */
typedef struct MapNodeKeyOps
{
  uint32_t (*hash)(const void *data, void *arg);
  void *(*cp)(const void *data, void *arg);
  void (*free)(void *data, void *arg);
  bool (*eq)(const void *data1, const void *data2, void *arg);
  void *arg;
} MapNodeKeyOps;

typedef struct MapNodeValOps
{
  void *(*cp)(const void *data, void *arg);
  void (*free)(void *data, void *arg);
  bool (*eq)(const void *data1, const void *data2, void *arg);
  void *arg;
} MapNodeValOps;

typedef struct MapHashTable {
  size_t capacity; /* total number of available buckets */
  size_t size; /* The total number of elements */
  MapNode** buckets;
  MapNodeKeyOps key_ops;
  MapNodeValOps val_ops;
} MapHashTable;


extern MapHashTable* create_MapHashTable(MapNodeKeyOps key_ops, MapNodeValOps val_ops);
extern void free_MapHashTable(MapHashTable* hashtable);
extern void* get_MapHashTable(MapHashTable* hashtable, const void* key);
extern bool contains_MapHashTable(MapHashTable* hashtable, const void* key);
extern void put_MapHashTable(MapHashTable* hashtable, const void* key, const void* val);
extern void print_MapHashTable(MapHashTable* hashtable, void (*print_key)(const void* key), void (*print_val)(const void* val));
extern uint32_t numCol_MapHashTable(MapHashTable* hashtable);

/* String Operations */


uint32_t string_hash(const void *data, void *arg);
void* string_cp(const void *data, void *arg);
bool string_eq(const void *data1, const void *data2, void *arg);
void string_free(void *data, void *arg);
void string_print(const void *data);

extern MapNodeKeyOps key_ops_string;
extern MapNodeValOps val_ops_string;
#endif