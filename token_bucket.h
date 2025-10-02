#ifndef BUCKET
#define BUCKET

#define OFF 0
#define STRICT 1
#define BURSTY 2

void initBucket(int mode, double request_rate, int request_max);
int checkRequest();
void freeBucket();

#endif