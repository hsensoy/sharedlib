//
// Created by husnu sensoy on 04/06/15.
//

#ifndef SHARED_CHASHMAP_H
#define SHARED_CHASHMAP_H


#include "murmurhash.h"
#include "string.h"
#include "debug.h"
#include "stdlib.h"
#include "stringalgo.h"

#define MURMUR_SEED 0
#define DEFAULT_HASH_BUCKET_SIZE 1000

enum errorHashMap {
    hashMapSucces = 0,
    hashMapKeyNotFound

};

typedef enum errorHashMap errorHashMap;

struct kv_st {
    char *key;
    int value;

    struct kv_st *next;

};

typedef struct kv_st *kv_t;


struct hashmap_st {
    long nelements;
    int nbucket;
    kv_t *chain;

};

typedef struct hashmap_st *hashmap_t;


hashmap_t newStringHashMap();

void deleteStringHashMap(hashmap_t hm);

void putHashmap(hashmap_t hm, const char *key, int value);

errorHashMap getHashmap(hashmap_t hm, const char *key, int *value);

inline long lenHashmap(hashmap_t hm) {
    return hm->nelements;
}


#endif //SHARED_CHASHMAP_H
