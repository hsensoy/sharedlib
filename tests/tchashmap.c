//
// Created by husnu sensoy on 04/06/15.
//

#include "chashmap.h"

static hashmap_t test_hm;
static hashmap_t feature_dict;
static DArray *features;

const char *feat1 = "child(0)=NN";
const char *feat2 = "child(-1)=NN";
const char *feat3 = "child(1)=NN";

void load_test();

void test_loaded();

void test_not_loaded();

void test_create() {
    test_hm = newStringHashMap();

    return;

    check(test_hm != NULL, "Hash Map creation error");
    error:
    exit(EXIT_FAILURE);
}

void test_getHashmap_set() {
    int v = -1;
    putHashmap(test_hm, feat1, 0);


    errorHashMap rc = getHashmap(test_hm, feat1, &v);

    check(rc == hashMapSucces && v == 0, "Error in finding key(%s):value pair.rc=%d and v=%d", feat1, rc, v);


    putHashmap(test_hm, feat2, 1);
    rc = getHashmap(test_hm, feat2, &v);

    check(rc == hashMapSucces && v == 1, "Error in finding key(%s):value pair", feat2);

    putHashmap(test_hm, feat3, 2);
    rc = getHashmap(test_hm, feat3, &v);

    check(rc == hashMapSucces && v == 2, "Error in finding key(%s):value pair", feat3);


    rc = getHashmap(test_hm, "Mahmut Tuncer!!!", &v);

    check(rc == hashMapKeyNotFound, "Able to find a non existing element: %s", "Mahmut Tuncer!!!");

    return;
    error:
    exit(EXIT_FAILURE);
}

void test_delete() {
    deleteStringHashMap(test_hm);
}


int main() {

    test_create();
    test_getHashmap_set();
    test_delete();

    log_info("Loading features into feature dictionary");
    load_test();
    log_info("Testing for feature indicies");
    test_loaded();
    test_not_loaded();

    return 0;
}

void test_not_loaded() {

    int idx;
    errorHashMap rc = getHashmap(feature_dict, "between:NN_NN_NN", &idx);

    check(rc == hashMapKeyNotFound, "Unexpected key %s is found in hash map", "between:NN_NN_NN");



    return;
    error:
    exit(EXIT_FAILURE);

}

void test_loaded() {

    for (int i = 0; i < DArray_count(features); ++i) {
        char *feature = (char *) DArray_get(features, i);

        int idx;
        errorHashMap rc = getHashmap(feature_dict, feature, &idx);

        check(rc == hashMapSucces, "Expected key %s not found in hash map", feature);

        log_info("%s:%d", feature, idx);
    }


    log_info("There are %ld elements in feature dictionary", lenHashmap(feature_dict));

    return;

    error:
    exit(EXIT_FAILURE);

}

void load_test() {
    const char *feature_file = "/Users/husnusensoy/code/hackrepo33/features.txt";

    FILE *fp = fopen(feature_file, "r");
    check(fp != NULL, "%s could not opened", feature_file);

    ssize_t read;
    char *line = NULL;
    size_t len = 0;
    feature_dict = newStringHashMap();
    features = DArray_create(sizeof(char *), 3);
    check(features != NULL, "Darray allocatino error");

    while ((read = getline(&line, &len, fp)) != -1) {

        if (strcmp(line, "\n") != 0) {

            DArray *tokens = split(line, "\t");

            check(DArray_count(tokens) == 3, "%s does not have 3 tokens", line);

            int feature_idx = atoi((char *) DArray_get(tokens, 0));
            char *feature = (char *) DArray_get(tokens, 1);

            DArray_push(features, strdup(feature));

            log_info("%s:%d", feature, feature_idx);

            putHashmap(feature_dict, feature, feature_idx);


            //DArray_clear(tokens);

        }

    }

    return;

    error:
    exit(EXIT_FAILURE);

}

