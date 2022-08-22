//
// Created by Alan Ćwiek on 8/21/22.
//

#include <unistd.h>
#include "watchdog.h"
#include "logger.h"
#include "../program.h"

static struct Thread *thread = NULL;
static struct Thread **watched_threads = NULL;
static size_t thread_num = 0;

static void *watchdog_thread_routine(struct Thread *used_thread) {
    while (thread_is_running(used_thread)) {
        for (int i = 0; i < thread_num; ++i) {
            thread_time(watched_threads[i], FALSE);
            if (thread_get_timer(watched_threads[i]) > 2) {
                logger_log("Watchdog: thread is not responding. Terminating program...");
                program_terminate();
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
