#include "token_bucket.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

typedef struct Bucket {
    uint mode;
    uint token_cur;
    uint token_max;
    uint token_request_time;
    uint time_rest;
    struct timeval time_last;
} Bucket;

Bucket* bucket = NULL;

void notInitializedError() {
    printf("Bucket not initialized\n");
    exit(EXIT_FAILURE);
}

void initBucket(uint mode, uint request_time) {
    if (bucket) {
        printf("Bucket already initialized\n");
        exit(EXIT_FAILURE);
    }
    if (mode > 2) {
        printf("Invalid bucket mode\n");
        exit(EXIT_FAILURE);
    }

    bucket = (Bucket*)malloc(sizeof(Bucket));
    bucket->mode = mode;
    bucket->token_cur = 0;

    // Calcula o maximo de requesicoes possiveis num segundo, arrendodado para cima
    double limit = ceil(1000 / (double)request_time);
    bucket->token_max = limit;
    if (mode == 2) bucket->token_max *= 1.5;
    
    // Muda o request_time para microsegundos
    bucket->token_request_time = request_time * 1000;
    gettimeofday(&bucket->time_last, NULL);
}

void updateTokens() {
    struct timeval cur_time;
    gettimeofday(&cur_time, NULL);

    // Diferenca do tempo atual e do ultimo tempo usado pelo balde
    long delta_sec = cur_time.tv_sec - bucket->time_last.tv_sec;
    long delta_mil_sec = cur_time.tv_usec - bucket->time_last.tv_usec;
    if (delta_mil_sec < 0) {
        delta_sec -= 1;
        delta_mil_sec += 1000000;
    }
    delta_mil_sec += bucket->time_rest;

    // Adicionar os microsegundos que sobraram da ultima vez
    bucket->time_rest = 0;
    
    // Enquanto o tempo for maior que o tempo do request aumenta um token
    while (delta_sec > 0 || delta_mil_sec > bucket->token_request_time) {
        if (delta_mil_sec < bucket->token_request_time) {
            delta_sec--;
            delta_mil_sec += 1000000;
        }
        bucket->token_cur++;
        delta_mil_sec -= bucket->token_request_time;
    }

    // Limitar o numero de token
    if (bucket->token_cur > bucket->token_max) {
        bucket->token_cur = bucket->token_max;
    } 
    
    // Salva o que sobrou dos microsegundos no balde
    bucket->time_rest += delta_mil_sec;

    // Atualiza o ultimo tempo que o balde foi atualizado
    bucket->time_last = cur_time;
}

int checkRequest() {
    if (!bucket) notInitializedError();
    if (bucket->mode == 0) return 1;
    updateTokens();
    if (bucket->token_cur) {
        bucket->token_cur--;
        return 1;
    }
    return 0;
}

void freeBucket() {
    if (!bucket) notInitializedError();
    free(bucket);
    bucket = NULL;
}