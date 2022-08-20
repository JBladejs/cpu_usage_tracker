//
// Created by Alan Ćwiek on 8/20/22.
//

#include <bits/pthreadtypes.h>
#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include "thread.h"
#include "common.h"

struct Thread {
    pthread_t thread;
    u8 running;
    void *(*start_routine)(void *arg);
    void (*destroy_routine)();
};

struct Thread *thread_create(void *(*start)(void * arg), void (*destroy)()) {
    struct Thread *thread = malloc(sizeof(struct Thread));
    thread->start_routine = start;
    thread->destroy_routine = destroy;
    return thread;
}

void thread_run(struct Thread *thread, void *arg) {
    u8 result = pthread_create(&(thread->thread), NULL, thread->start_routine, NULL);
    if (result != 0) {
        perror("Could not create a thread!");
        exit(1);
    }
}

void thread_join(struct Thread *thread) {
    pthread_join(thread->thread, NULL);
}
