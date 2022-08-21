//
// Created by Alan Ćwiek on 8/19/22.
//

#ifndef CPU_USAGE_TRACKER_PRINTER_H
#define CPU_USAGE_TRACKER_PRINTER_H

#include "../common.h"

void printer_init(u16 cores);
struct Thread *printer_get_thread();
void printer_add_data(f32 *value);

#endif //CPU_USAGE_TRACKER_PRINTER_H
