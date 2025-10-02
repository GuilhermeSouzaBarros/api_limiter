#ifndef BUCKET
#define BUCKET

#define OFF 0
#define STRICT 1
#define BURSTY 2

void initBucket(int mode, int request_rate_milsec, int request_max);
int checkRequest();

#endif