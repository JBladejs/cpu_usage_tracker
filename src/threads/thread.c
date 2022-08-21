//
// Created by Alan Ćwiek on 8/20/22.
//

#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include "thread.h"
#include "../common.h"

struct Thread {
    pthread_t thread;
    volatile sig_atomic_t running;
    void *(*start_routine)(void *arg);
};

struct Thread *thread_create(void *(*start)(void * arg)) {
    struct Thread *thread = malloc(sizeof(struct Thread));
    thread->start_routine = start;
    return thread;
}

void thread_run(struct Thread *thread, void *arg) {
    thread->running = TRUE;
    u8 result = pthread_create(&(thread->thread), NULL, thread->start_routine, NULL);
    if (result != 0) {
        perror("Could not create a thread!");
        exit(1);
    }
}

void thread_join(struct Thread *thread) {
    pthread_join(thread->thread, NULL);
}

void thread_stop(struct Thread *thread) {
    thread->running = FALSE;
}

sig_atomic_t thread_is_running(struct Thread *thread) {
    return thread->running;
}
