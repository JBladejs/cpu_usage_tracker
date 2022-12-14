//
// Created by Alan Ćwiek on 8/23/22.
//

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "thread_manager.h"
#include "thread.h"
#include "logger.h"
#include "../program.h"

ThreadManager *thread_manager_instance(void) {
    static ThreadManager manager;
    static u8 is_initialized = FALSE;

    if (!is_initialized) {
        manager.index = 0;
        manager.running = FALSE;
        manager.watchdog_thread = 10;
        is_initialized = TRUE;
        for (int i = 0; i < 10; ++i) {
            manager.threads[i] = NULL;
        }
    }

    return &manager;
}

s32 thread_manager_get_next_id(void) {
    return thread_manager_instance()->index++;
}

static void *watchdog_thread_routine(void *arg) {
    ThreadManager *manager = (ThreadManager *) arg;
    char message[255];
    while (manager->running) {
        for (u32 i = 0; i < manager->active_threads; ++i) {
            if (manager->threads[i] == NULL) continue;
            if (thread_time(manager->threads[i], FALSE) > 2) {
                snprintf(message, 255,
                         "Watchdog: thread %s is not responding. Terminating program...",
                         manager->threads[i]->name);
                logger_log(message);
                program_terminate();
                return NULL;
            }
        }
        sleep(1);
    }
    return NULL;
}

void thread_manager_add_thread(Thread *thread, s32 id) {
    ThreadManager *manager = thread_manager_instance();
    if (id > 9) return;
    manager->threads[id] = thread;
    if (manager->active_threads++ == 0) {
        manager->running = TRUE;
        pthread_create(&manager->watchdog_thread, NULL, watchdog_thread_routine, manager);
    }
}

void thread_manager_destroy_all(void) {
    ThreadManager *manager = thread_manager_instance();
    u32 index = manager->active_threads - 1;
    thread_manager_instance()->running = FALSE;
    if (index > 9) index = 9;
    for (u32 i = 0; i < index; ++i) {
        if (manager->threads[i] != NULL) thread_stop(manager->threads[i]);
    }
}

void thread_manager_join(void) {
    pthread_join(thread_manager_instance()->watchdog_thread, NULL);
}
