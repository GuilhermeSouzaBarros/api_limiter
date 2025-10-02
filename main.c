#include "token_bucket.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef unsigned int uint;

int sendRequests(int amount, uint pause_ms){
    int qnt_allowed = 0; 
    for(int i = 0; i < amount; ++i){
        printf("Sending request... ");
        fflush(stdout);

        int allowed = checkRequest();
        if (allowed) printf("Accepted\n");
        else printf("Denied\n");
        qnt_allowed += allowed;

        usleep(pause_ms * 1000); // Converte ms para micro segundos
    } 
    return qnt_allowed;
}

int main(){
    uint request_rate_per_second = 5;
    uint request_rate_per_msecond = 1000 / request_rate_per_second;
    int request_num = 30;
    int request_delay = 100;


    // Testa o modo OFF
    initBucket(OFF, request_rate_per_msecond);
    usleep(2000000); // Espera por 2 segundo
    printf("Testando modo OFF...\n");

    // Faz requests
    int accepted_off = sendRequests(request_num, request_delay);
    freeBucket();


    // Testa o modo STRICT
    initBucket(STRICT, request_rate_per_msecond); 
    usleep(2000000); // Espera por 2 segundo
    printf("\nTestando modo STRICT...\n");

    // Faz requests
    int accepted_str = sendRequests(request_num, request_delay);
    freeBucket();


    // Testa o modo BURSTY
    initBucket(BURSTY, request_rate_per_msecond);
    usleep(2000000); // Espera por 2 segundo
    printf("\nTestando modo BURSTY...\n");

    // Faz requests sem pausa
    int accepted_bur = sendRequests(request_num, request_delay);
    freeBucket();
    

    // Resultados
    printf("\n\nRequisicoes aceitas OFF   : %d/%d.\n", accepted_off, request_num);
    printf("Requisicoes aceitas STRICT: %d/%d.\n", accepted_str, request_num);
    printf("Requisicoes aceitas BURSTY: %d/%d.\n", accepted_bur, request_num);
    return 0;
}