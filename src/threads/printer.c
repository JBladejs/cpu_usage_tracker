//
// Created by Alan Ćwiek on 8/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "printer.h"
#include "../queue.h"
#include "thread.h"

static struct Queue *queue = NULL;
static u16 core_count = 1;
static struct Thread *thread = NULL;

static void printer_destroy() {
    free(queue);
    queue = NULL;
}

static void *printer_thread_routine(void *arg) {
    queue = queue_create(255, core_count * sizeof (f32));
    while (thread_is_running(thread)) {
        system("clear");
        if (!queue_is_empty(queue)) {
            f32 *usage = queue_dequeue(queue);
            for (int i = 0; i < core_count; ++i) {
                if (i == 0) {
                    printf("Total CPU usage: %.2f%%\n", usage[0]);
                } else {
                    printf("Core %d usage: %.2f%%\n", i, usage[i]);
                }
            }
            free(usage);
        }
        sleep(1);
    }
    printer_destroy();
}

struct Thread *printer_get_thread() {
    return thread;
}

void printer_init() {
    thread = thread_create(printer_thread_routine);
}

void printer_add_data(f32 *values) {
    queue_enqueue(queue, values);
}

void printer_set_core_count(u16 value) {
    core_count = value;
}


