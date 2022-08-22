//
// Created by Alan Ćwiek on 8/18/22.
//

#ifndef CPU_USAGE_TRACKER_READER_H
#define CPU_USAGE_TRACKER_READER_H

#include "../common.h"
#include "../file_io/statfile.h"
#include "buffer.h"

void reader_init(struct Statfile *statfile, struct Buffer *buffer);
struct Thread *reader_get_thread();

#endif //CPU_USAGE_TRACKER_READER_H
