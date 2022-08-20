//
// Created by Alan Ćwiek on 8/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/types/sig_atomic_t.h>
#include "printer.h"

volatile static sig_atomic_t running = FALSE;
static f32 *usage = NULL;
static u16 core_count = 1;

void *printer_init(void *arg) {
    running = TRUE;
    while (running) {
        system("clear");
        if (usage != NULL) {
            for (int i = 0; i < core_count; ++i) {
                printf("Core %d: %.2f%%\n", i, usage[i]);
            }
            //TODO: free memory
        }
        sleep(1);
    }
    printer_destroy();
}

void printer_add_data(f32 *values) {
    usage = values;
}

void printer_set_core_count(u16 value) {
    core_count = value;
}

void printer_destroy() {
    running = FALSE;
}


