//
// Created by Alan Ćwiek on 8/19/22.
//

#ifndef CPU_USAGE_TRACKER_PRINTER_H
#define CPU_USAGE_TRACKER_PRINTER_H

#include "../common.h"
#include "buffer.h"

void printer_init(u16 cores, struct Buffer *buffer);
struct Thread *printer_get_thread();

#endif //CPU_USAGE_TRACKER_PRINTER_H
