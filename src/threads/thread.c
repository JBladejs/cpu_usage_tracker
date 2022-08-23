//
// Created by Alan Ćwiek on 8/20/22.
//

#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include "thread.h"
#include "buffer.h"

struct ThreadManager {
    struct Thread *threads[10];
    s32 index;

    //padding
    u32 : 32;
};

static struct ThreadManager *thread_manager_instance(void) {
    static struct ThreadManager manager;
    static u8 is_initialized = FALSE;

    if (!is_initialized) {
        manager.index = 0;
        is_initialized = TRUE;
    }

    return &manager;
}

static s32 thread_manager_get_next_id(void) {
    return thread_manager_instance()->index++;
}

static void thread_manager_add_thread(struct Thread *thread, s32 id) {
    if (id > 9) return;
    thread_manager_instance()->threads[id] = thread;
}

static void thread_manager_destroy_all(void) {
    struct ThreadManager *manager = thread_manager_instance();
    s32 index = manager->index - 1;
    if (index > 9) index = 9;
    for (s32 i = 0; i < index; ++i) {
        thread_stop(manager->threads[i]);
    }
}

static void *thread_routine(void *arg) {
    struct Thread *thread = (struct Thread *) arg;
    return thread->start_routine(arg);
}

struct Thread *thread_create(char *name, void *(*start)(struct Thread *), struct Buffer *read_buffer, struct Buffer *write_buffer) {
    struct Thread *thread = malloc(sizeof(struct Thread));
    u8 result;
    s32 initial_id = thread_manager_get_next_id();
    thread->thread_id = (pthread_t) initial_id;
    thread->name = name;
    thread->timer = 0;
    thread->start_routine = start;
    thread->read_buffer = read_buffer;
    thread->write_buffer = write_buffer;

    thread->running = TRUE;
    result = (u8) pthread_create(&(thread->thread_id), NULL, thread_routine, thread);
    if (result != 0) {
        perror("Could not create a Thread!");
        exit(1);
    }

    thread_manager_add_thread(thread, initial_id);
    return thread;
}

void thread_join(struct Thread *thread) {
    pthread_join(thread->thread_id, NULL);
}

void thread_stop(struct Thread *thread) {
    thread->running = FALSE;
    if (thread->read_buffer != NULL) buffer_end(thread->read_buffer);
    if (thread->write_buffer != NULL) buffer_end(thread->write_buffer);
    thread_join(thread);
    free(thread);
}

sig_atomic_t thread_is_running(struct Thread *thread) {
    return thread->running;
}

u8 thread_get_timer(struct Thread *thread) {
    return thread->timer;
}

void thread_time(struct Thread *thread, u8 reset) {
    if (reset) {
        thread->timer = 0;
    } else {
        thread->timer++;
    }
}

void thread_write_to_buffer(struct Thread *thread, void *data) {
    if (thread->write_buffer != NULL) buffer_push(thread->write_buffer, data);
}

void *thread_read_from_buffer(struct Thread *thread) {
    if (thread->read_buffer != NULL) return buffer_pop(thread->read_buffer);
    else return NULL;
}

void thread_stop_all(void) {
    thread_manager_destroy_all();
}
