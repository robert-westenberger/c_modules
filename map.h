/** 
 * Copied from "The C Programming Language" section 6.6 (slightly edited
 * function names / struct names)
 */

#ifndef MAP_H
#define MAP_H
#include <string.h>
#define HASHSIZE 101

typedef struct MapNode {
  struct MapNode *next;
  char *key;
  int value;
} MapNode;


extern MapNode* get_HashMap(MapNode* hashMap[HASHSIZE], char* s);
extern MapNode* set_HashMap(MapNode* hashMap[HASHSIZE], char* key, int value);
#endif