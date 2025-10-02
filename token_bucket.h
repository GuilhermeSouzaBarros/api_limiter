#ifndef BUCKET
#define BUCKET

#define OFF 0    // Retorna verdadeiro sempre
#define STRICT 1 // Capacidade do balde igual ao número máximo de requests num segundo
#define BURSTY 2 // Capacidade do balde 1,5 vezes maior que STRICT

typedef unsigned int uint;

void initBucket(uint mode, uint request_time); // request_time sao os millisegundos aceito entre requests
int checkRequest(); // retorna se um novo request sera aceito
void freeBucket(); // desaloca o balde e o permite criar um balde com outras configuracoes

#endif