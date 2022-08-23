//
// Created by Alan Ćwiek on 8/23/22.
//

#ifndef CPU_USAGE_TRACKER_MAIN_THREADS_H
#define CPU_USAGE_TRACKER_MAIN_THREADS_H

#include "../common.h"
#include "../file_io/statfile.h"
#include "buffer.h"

void reader_init(struct Statfile *statfile, struct Buffer *buffer);

void printer_init(u16 cores, struct Buffer *buffer);

void analyzer_init(u16 cores, struct Buffer *read_buffer, struct Buffer *write_buffer);

#endif //CPU_USAGE_TRACKER_MAIN_THREADS_H
