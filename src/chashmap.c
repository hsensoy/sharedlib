//
// Created by husnu sensoy on 04/06/15.
//

#include "chashmap.h"

hashmap_t newStringHashMap() {

    hashmap_t hm = (hashmap_t) malloc(sizeof(struct hashmap_st));


    check(hm != NULL, "Error in memory allocation");

    hm->chain = (kv_t *) malloc(sizeof(kv_t) * DEFAULT_HASH_BUCKET_SIZE);
    check(hm->chain != NULL, "Error in memory allocation:hm->bucket");

    hm->nbucket = DEFAULT_HASH_BUCKET_SIZE;
    hm->nelements = 0L;

    for (int i = 0; i < hm->nbucket; ++i) {
        (hm->chain)[i] = NULL;
    }

    return hm;
    error:
    exit(EXIT_FAILURE);
}

void deleteStringHashMap(hashmap_t hm) {
    free(hm->chain);
    free(hm);
}


inline static kv_t newKV(const char *key, int value) {


    kv_t kv = (kv_t) malloc(sizeof(struct kv_st));
    check(kv != NULL, "Memory Allocation error: newKV");

    kv->next = NULL;
    kv->key = strdup(key);
    kv->value = value;

    return kv;


    error:
    exit(EXIT_FAILURE);
}

void putHashmap(hashmap_t hm, const char *key, int value) {

//todo: Does not prevent from duplication
    int chain_id = (murmurhash(key, strlen(key), MURMUR_SEED)) % (hm->nbucket);

    debug("Chain#: %d", chain_id);

    if ((hm->chain)[chain_id] == NULL) {

        debug("%s:%d is the first element in chain", key, value);
        (hm->chain)[chain_id] = newKV(key, value);

    } else {
        kv_t kv = NULL;
        for (kv = (hm->chain)[chain_id]; kv->next != NULL; kv = kv->next);

        kv->next = newKV(key, value);
    }

    (hm->nelements)++;

}

errorHashMap getHashmap(hashmap_t hm, const char *key, int *value) {

    int chain_id = (murmurhash(key, strlen(key), MURMUR_SEED)) % (hm->nbucket);

    debug("Chain#: %d", chain_id);

    for (kv_t kv = (hm->chain)[chain_id]; kv != NULL; kv = kv->next) {

        debug("Check for %s:%d", kv->key, kv->value);

        if (strcmp(kv->key, key) == 0) {
            *value = kv->value;

            return hashMapSucces;
        }


    }

    return hashMapKeyNotFound;
}