#include <pthread.h>
#include <stdio.h>
#include "reader.h"

int main() {
    pthread_t reader_thread;
    u8 result = pthread_create(&reader_thread, NULL, reader_init, NULL);
    if (result != 0) {
        perror("Could not create a thread!");
        return 1;
    }
    pthread_join(reader_thread, NULL);
    return 0;
}
