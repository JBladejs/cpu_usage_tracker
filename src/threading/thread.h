//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_THREAD_H
#define CPU_USAGE_TRACKER_THREAD_H

#include "../common.h"
#include "pthread.h"
#include "buffer.h"
#include "../file_io/statfile.h"
#include <signal.h>

typedef union ThreadArg {
    u32 core_count;
    Statfile *statfile;
} ThreadArg;

typedef struct Thread {
    pthread_mutex_t mutex;
    pthread_t thread_id;
    char *name;
    Buffer *read_buffer;
    Buffer *write_buffer;

    void *(*start_routine)(struct Thread *thread);

    ThreadArg arg;

    volatile sig_atomic_t running;
    u8 timer;

    //padding
    u32 : 24;
} Thread;

Thread *thread_init(char *name, void *(*start)(Thread *), Buffer *read_buffer,
                    Buffer *write_buffer, u8 tracked, ThreadArg arg);

u8 thread_time(Thread *thread, u8 reset);

void thread_write_to_buffer(Thread *thread, void *data);

void *thread_read_from_buffer(Thread *thread);

ThreadArg thread_get_arg(Thread *thread);

sig_atomic_t thread_is_running(Thread *thread);

void thread_join(Thread *thread);

void thread_stop(Thread *thread);

#endif //CPU_USAGE_TRACKER_THREAD_H
