#include <pthread.h>

void* threadRoutine(void *arg);

void* consumidor(void* arg);

void* produtor(void* arg);

pthread_t* getAddressThread(pthread_t *thread ,int position);

pthread_t getThread(pthread_t *thread ,int position);