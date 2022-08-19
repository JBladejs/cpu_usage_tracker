#include <pthread.h>
#include <stdio.h>
#include "analyzer.h"

int main() {
    pthread_t reader_thread;
    pthread_t analyzer_thread;
    u8 result = pthread_create(&reader_thread, NULL, reader_init, NULL);
    if (result != 0) {
        perror("Could not create a thread!");
        return 1;
    }
    result = pthread_create(&analyzer_thread, NULL, analyzer_init, NULL);
    if (result != 0) {
        perror("Could not create a thread!");
        return 1;
    }
    pthread_join(reader_thread, NULL);
    pthread_join(analyzer_thread, NULL);
    return 0;
}
