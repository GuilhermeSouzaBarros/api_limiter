#include "token_bucket.h"

#include <stdlib.h>
#include <time.h>
#include <resources.h>
#include <errno.h>

typedef unsigned int uint;

typedef struct Bucket {
    uint mode;
    uint token_cur;
    uint token_max;
    double token_request_sec;
    struct timeval last_time;
} Bucket;

Bucket* bucket = NULL;

void notInitializedError() {
    perror("Bucket not initialized\n");
    exit(EXIT_FAILURE);
}

void initBucket(uint mode, double request_rate, uint request_max) {
    if (bucket) {
        perror("Bucket already initialized\n");
        exit(EXIT_FAILURE);
    }
    if (mode > 2) {
        perror("Invalid bucket mode\n");
        exit(EXIT_FAILURE);
    }

    bucket = (Bucket*)malloc(sizeof(Bucket));
    bucket->mode = mode;
    bucket->token_cur = 0;
    bucket->token_max = request_max;
    bucket->token_request_sec = request_rate_milsec;
    gettimeofday(&bucket->last_time, NULL);
    return 1;
}

void updateTokens() {
    struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
    long delta_sec = cur_time.tv_sec - bucket->last_time.tv_sec;
    long delta_mil_sec = cur_time.tv_usec - bucket->last_time.tv_usec;
    if (delta_mil_sec < 0) {
        delta_sec -= 1;
        delta_mil_sec += 1000000;
    }


    bucket->last_time = cur_time;
}

int checkRequest() {
    if (!bucket) notInitializedError();


}

void freeBucket() {
    if (!bucket) notInitializedError();
    free(bucket);
    bucket = NULL;
}