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

struct ThreadManager *thread_manager_instance(void) {
    static struct ThreadManager manager;
    static u8 is_initialized = FALSE;

    if (!is_initialized) {
        manager.index = 0;
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
    struct ThreadManager *manager = (struct ThreadManager*) arg;
    char message[255];
    while (1) {
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
}

void thread_manager_add_thread(struct Thread *thread, s32 id) {
    struct ThreadManager *manager = thread_manager_instance();
    if (id > 9) return;
    manager->threads[id] = thread;
    if (manager->active_threads++ == 0)
        pthread_create(&manager->watchdog_thread, NULL, watchdog_thread_routine, manager);
}

void thread_manager_destroy_all(void) {
    struct ThreadManager *manager = thread_manager_instance();
    s32 index = manager->index - 1;
    if (index > 9) index = 9;
    for (s32 i = 0; i < index; ++i) {
        if (manager->threads[i] != NULL) thread_stop(manager->threads[i]);
    }
}

void thread_manager_join(void) {
    pthread_join(thread_manager_instance()->watchdog_thread, NULL);
}
