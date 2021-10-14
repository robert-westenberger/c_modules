/** 
 * Copied from "The C Programming Language" section 6.6 (slightly edited
 * function names / struct names)
 */

#include <stdlib.h>
#include <string.h>
#include "map.h"


static unsigned hash_HashMap(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}



MapNode* get_HashMap(MapNode* hashMap[HASHSIZE], char *s) {
  MapNode *np;
  unsigned hash = hash_HashMap(s);

  for (np = *(hashMap + hash); np != NULL; np = np->next)
    if (strcmp(s, np->key) == 0)
      return np; /* found */
  return NULL; /* not found */
}

MapNode* set_HashMap(MapNode* hashMap[HASHSIZE], char* key, int value) {
  MapNode *np;
  unsigned hashval;
    if ((np = get_HashMap(hashMap, key)) == NULL) { /* not found */
        np = (struct MapNode *) malloc(sizeof(*np));
        if (np == NULL || (np->key = strdup(key)) == NULL)
          return NULL;
        hashval = hash_HashMap(key);
        np->next = *(hashMap + hashval);
        *(hashMap + hashval) = np;

    } else /* already there */
        free((void *) &(np->value)); /*free previous defn */
    if ((np->value = value) == 0) 
       return NULL;
    return np;
}