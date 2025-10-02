#include "token_bucket.h"

#include <stdio.h>
#include <time.h>

int main(){
    // Testa o modo OFF

    int request_rate_per_second = 120;
    int max_requests = 30;

    initBucket(OFF, request_rate_per_second, 30);

    for(int i = 0; i < 10; ++i){
        int result = checkRequest();

        if(result){
            
        }
    }


    return 0;
}