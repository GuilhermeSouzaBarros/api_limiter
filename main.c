#include "token_bucket.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef unsigned int uint;

int sendRequests(int amount, uint pause_ms){
    int qnt_allowed = 0; 
    for(int i = 0; i < amount; ++i){
        qnt_allowed += checkRequest();

        usleep(pause_ms * 1000); // Converte ms para nano segundos
    } 
    return qnt_allowed;
}

int main(){
    uint request_rate_per_second = 5;
    uint request_rate_per_msecond = 1000 / request_rate_per_second;

    // Testa o modo OFF
    printf("Testando modo OFF...\n\n");
    initBucket(OFF, request_rate_per_msecond);

    usleep(1000000); // Espera por 1 segundo

    // Faz 10 requests sem pausa
    int accepted = sendRequests(10, 0);

    if(accepted == 10)
        printf("Todas as %d requisicoes sem pausas foram processadas.\n", 10);
    else
        printf("Apenas %d das %d requisições foram aceitas.\n", accepted, 10);

    freeBucket();

    // Testa o modo STRICT
    printf("Testando modo STRICT...\n\n");
    initBucket(STRICT, request_rate_per_msecond, max_requests); 

    usleep(1000000); // Espera por 1 segundo

    // Faz 10 requests sem pausa
    int accepted = sendRequests(10, 0);

    if(accepted == 10)
        printf("Todas as %d requisicoes sem pausas foram processadas.\n", 10);
    else
        printf("Apenas %d das %d requisições foram aceitas.\n", accepted, 10);
    freeBucket();

    // Testa o modo BURSTY
    printf("Testando modo BURSTY...\n\n");
    initBucket(BURSTY, request_rate_per_msecond, max_requests);
    
    usleep(1000000); // Espera por 1 segundo

    // Faz 10 requests sem pausa
    int accepted = sendRequests(10, 0);

    if(accepted == 10)
        printf("Todas as %d requisicoes sem pausas foram processadas.\n", 10);
    else
        printf("Apenas %d das %d requisições foram aceitas.\n", accepted, 10);
    freeBucket();

    return 0;
}