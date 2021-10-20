/** 
 * Separate Chaining map using linked lists.
 * From https://www.andreinc.net/2021/10/02/implementing-hash-tables-in-c-part-1
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "map2.h"

MapHashTable* create_MapHashTable(MapNodeKeyOps key_ops, MapNodeValOps val_ops) {
  MapHashTable* hashtable; 
  hashtable = malloc(sizeof(*hashtable));
  if(NULL == hashtable) {
    fprintf(stderr,"malloc() failed in file %s at line # %d", __FILE__,__LINE__);
    exit(EXIT_FAILURE);
  }
  hashtable->size = 0;
  hashtable->capacity = HASH_CAPACITY_INIT;
  hashtable->key_ops = key_ops;
  hashtable->val_ops = val_ops;
  hashtable->buckets = malloc(hashtable->capacity * sizeof(*(hashtable->buckets)));
  if(NULL == hashtable->buckets) {
    fprintf(stderr,"malloc() failed in file %s at line # %d", __FILE__,__LINE__);
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < hashtable->capacity; i++) {
    // Initially all the buckets are NULL
    // Memory will be allocated for them when needed
    hashtable->buckets[i] = NULL;
  }
  return hashtable;
}
void free_MapHashTable(MapHashTable* hashtable) {
  MapNode* crt;
  MapNode* next;
  for(int i = 0; i < hashtable->capacity; ++i) {
    // Free memory for each bucket
    crt = hashtable->buckets[i];
    while(NULL!=crt) {
      next = crt->next;
      // Free memory for key and value
      hashtable->key_ops.free(crt->key, hashtable->key_ops.arg);
      hashtable->val_ops.free(crt->val, hashtable->val_ops.arg);
      // Free the node
      free(crt);
      crt = next;
    }
  }
  // Free the buckets and the hash structure itself
  free(hashtable->buckets);
  free(hashtable);
}
static void* getNode(MapHashTable *hashtable, const void *key) {
  MapNode* result = NULL;
  MapNode* crt = NULL;
  uint32_t h;
  size_t bucket_idx;
    
  // We compute the hash of the key to check for it's existence
  h = hashtable->key_ops.hash(key, hashtable->key_ops.arg);
  // We use simple division hashing for determining the bucket
  bucket_idx = h % hashtable->capacity;
  crt = hashtable->buckets[bucket_idx];

  while(NULL!=crt) {
    // Iterated through the linked list found at the bucket 
    // to determine if the element is present or not
    if (crt->hash == h && hashtable->key_ops.eq(crt->key, key, hashtable->val_ops.arg)) {
      result = crt;
      break;
    }
    crt = crt->next;
  }

  // If the while search performed in the while loop was successful,
  // `result` contains the node
  // otherwise it's NULL
  return result;
}

static void hashGrow(MapHashTable* hashtable) {
  MapNode** new_buckets;
  MapNode* crt;
  size_t new_capacity;
  size_t new_idx;

  new_capacity = hashtable->capacity * HASH_CAPACITY_MULT;
  new_buckets = malloc(sizeof(*new_buckets) * new_capacity);
  if (NULL == new_buckets) {
    fprintf(stderr, "Cannot resize buckets array. Hash table won't be resized.\n");
    return;
  }
  for (int i = 0; i < new_capacity; ++i) {
    new_buckets[i] = NULL;
  }

  // Rehash
  // For each bucket
  for (int i = 0; i < hashtable->capacity; i++) {
    // For each linked list
    crt = hashtable->buckets[i];
    while (NULL != crt)
    {
      // Finding the new bucket
      new_idx = crt->hash % new_capacity;
      MapNode *cur = crt;
      crt = crt->next;
      cur->next = new_buckets[new_idx];
      new_buckets[new_idx] = cur;
    }
  }

  hashtable->capacity = new_capacity;

  // Free the old buckets
  free(hashtable->buckets);

  // Update with the new buckets
  hashtable->buckets = new_buckets;
}

static uint32_t nodeNumCols(MapNode* node)
{
  uint32_t result = 0;
  if (node)
  {
    while (node->next != NULL)
    {
      result++;
      node = node->next;
    }
  }
  return result;
}

void* get_MapHashTable(MapHashTable* hashtable, const void* key) {
  MapNode* result = NULL;
  if (NULL!=(result=getNode(hashtable, key))) {
    return result->val;
  }
  return NULL;
}
void put_MapHashTable(MapHashTable* hashtable, const void *key, const void *val) { 
  MapNode* crt;
  size_t bucket_idx;
  crt = getNode(hashtable, key);
  if (crt) {
    // Key already exists
    // We need to update the value
    hashtable->val_ops.free(crt->val, hashtable->val_ops.arg);
    crt->val = val ? hashtable->val_ops.cp(val, hashtable->val_ops.arg) : 0;
  }
  else {
    // Key doesn't exist
    // - We create a node
    // - We add a node to the corresponding bucket
    crt = malloc(sizeof(*crt));
    if (NULL == crt) {
      fprintf(stderr,"malloc() failed in file %s at line # %d", __FILE__,__LINE__);
      exit(EXIT_FAILURE);
    }   
    crt->hash = hashtable->key_ops.hash(key, hashtable->key_ops.arg);
    crt->key = hashtable->key_ops.cp(key, hashtable->key_ops.arg);
    crt->val = hashtable->val_ops.cp(val, hashtable->val_ops.arg);

    // Simple division hashing to determine the bucket
    bucket_idx = crt->hash % hashtable->capacity;
    crt->next = hashtable->buckets[bucket_idx];
    hashtable->buckets[bucket_idx] = crt;
        
    // Element has been added successfully
    hashtable->size++;

    // Grow if needed
    if (hashtable->size > hashtable->capacity * HASH_GROWTH) {
      hashGrow(hashtable);
    }
  }
}
void print_MapHashTable(MapHashTable *hash, void (*print_key)(const void *key), void (*print_val)(const void *val)) {
  MapNode *crt;

  printf("Hash Capacity: %lu\n", hash->capacity);
  printf("Hash Size: %lu\n", hash->size);

  printf("Hash Buckets:\n");
  for (int i = 0; i < hash->capacity; i++)
  {
    crt = hash->buckets[i];
    printf("\tbucket[%d]:\n", i);
    while (NULL != crt)
    {
      printf("\t\thash=%" PRIu32 ", key=", crt->hash);
      print_key(crt->key);
      printf(", value=");
      print_val(crt->val);
      printf("\n");
      crt = crt->next;
    }
  }
}
bool contains_MapHashTable(MapHashTable *hash, const void* key) {
  return getNode(hash, key) ? true : false;
}

/* Gets number of collisions from the hash table*/
uint32_t numCol_MapHashTable(MapHashTable* hashtable) {
  uint32_t result = 0;
  for (int i = 0; i < hashtable->capacity; ++i)
  {
    result += nodeNumCols(hashtable->buckets[i]);
  }
  return result;
}

/* String operations*/
static uint32_t ch_hash_fmix32(uint32_t h)
{
  h ^= h >> 16;
  h *= 0x3243f6a9U;
  h ^= h >> 16;
  return h;
}
uint32_t string_hash(const void *data, void *arg) {
  //djb2
  uint32_t hash = (const uint32_t)5381;
  const char *str = (const char *)data;
  char c;
  while ((c = *str++))
  {
    hash = ((hash << 5) + hash) + c;
  }

  return ch_hash_fmix32(hash);
}
void *string_cp(const void *data, void *arg) {
  const char *input = (const char *)data;
  size_t input_length = strlen(input) + 1;
  char *result;
  result = malloc(sizeof(*result) * input_length);
  if (NULL == result)
  {
    fprintf(stderr, "malloc() failed in file %s at line # %d", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  strcpy(result, input);
  return result;
}
bool string_eq(const void *data1, const void *data2, void *arg) {
  const char *str1 = (const char *)data1;
  const char *str2 = (const char *)data2;
  return !(strcmp(str1, str2)) ? true : false;
}
void string_free(void *data, void *arg) {
  free(data);
}
void string_print(const void *data) {
  printf("%s", (const char *)data);
}

MapNodeKeyOps key_ops_string = { string_hash, string_cp, string_free, string_eq, NULL};
MapNodeValOps val_ops_string = { string_cp, string_free, string_eq, NULL};