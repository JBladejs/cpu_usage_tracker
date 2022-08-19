//
// Created by Alan Ćwiek on 8/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/types/sig_atomic_t.h>
#include "printer.h"

volatile static sig_atomic_t running = FALSE;
static f32 usage;

void *printer_init(void *arg) {
    running = TRUE;
    while (running) {
        system("clear");
        printf("CPU: %.2f%%\n", usage);
        sleep(1);
    }
    printer_destroy();
}

void printer_add_data(f32 value) {
    usage = value;
}

void printer_destroy() {
    running = FALSE;
}
