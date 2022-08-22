//
// Created by Alan Ćwiek on 8/19/22.
//

#ifndef CPU_USAGE_TRACKER_ANALYZER_H
#define CPU_USAGE_TRACKER_ANALYZER_H

#include "reader.h"
#include "buffer.h"

void analyzer_init(u16 cores, struct Buffer *read_buffer, struct Buffer *write_buffer);
struct Thread *analyzer_get_thread(void);

#endif //CPU_USAGE_TRACKER_ANALYZER_H
