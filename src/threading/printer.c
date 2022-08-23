//
// Created by Alan Ćwiek on 8/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "main_threads.h"
#include "thread.h"

static u16 core_count = 1;

static void *printer_thread_routine(struct Thread *thread) {
    f32 *usage = NULL;
    while (thread_is_running(thread)) {
        thread_time(thread, TRUE);
        usage = thread_read_from_buffer(thread);
        if (usage == NULL) break;
        system("clear");
        for (int i = 0; i < core_count; ++i) {
            if (i == 0) {
                printf("Total CPU usage: %.2f%%\n", (double) usage[0]);
            } else {
                printf("Core %d usage: %.2f%%\n", i, (double) usage[i]);
            }
        }
        printf("\n");
        free(usage);
        sleep(1);
    }
    return NULL;
}

void printer_init(u16 cores, struct Buffer *buffer) {
    core_count = cores;
    thread_create("printer", printer_thread_routine, buffer, NULL, true, NULL);
}


