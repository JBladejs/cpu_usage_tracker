//
// Created by Alan Ćwiek on 8/21/22.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "watchdog.h"

static struct Thread *thread = NULL;
static struct Thread **watched_threads = NULL;
static size_t thread_num = 0;

static void *watchdog_thread_routine(void *arg) {
    while (thread_is_running(thread)) {
        for (int i = 0; i < thread_num; ++i) {
            thread_time(watched_threads[i], FALSE);
            if (thread_get_timer(watched_threads[i]) > 2) {
                fprintf(stderr, "Watchdog: Thread is not responding!\n");
                //TODO: properly terminate the program
                exit(2);
            }
        }
        sleep(1);
    }
}

void watchdog_init(struct Thread **threads, size_t thread_count) {
    watched_threads = threads;
    thread = thread_create(watchdog_thread_routine);
    thread_run(thread, NULL);
    thread_num = thread_count;
}

struct Thread *watchdog_get_thread() {
    return thread;
}
