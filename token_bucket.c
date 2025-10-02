#include <token_bucket.h>

#include <stdlib.h>
#include <time.h>
#include <resources.h>

typedef unsigned int uint;

typedef struct Bucket {
    uint mode;
    uint token_cur;
    uint token_max;
    uint token_rate;
    struct timeval last_time;
} Bucket;

Bucket* bucket = NULL;

int initBucket(uint mode, uint request_rate_milsec, uint request_max) {
    if (!bucket) return 0;
    if (mode > 2) return 0;
    bucket = (Bucket*)malloc(sizeof(Bucket));
    bucket->mode = mode;
    bucket->token_cur = 0;
    bucket->token_max = request_max;
    bucket->token_rate = request_rate_milsec;

    return 1;
}

int checkRequest();