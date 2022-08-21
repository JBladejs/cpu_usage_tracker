//
// Created by Alan Ćwiek on 8/19/22.
//

#ifndef CPU_USAGE_TRACKER_PRINTER_H
#define CPU_USAGE_TRACKER_PRINTER_H

#include "../common.h"

void printer_init();
struct Thread *printer_get_thread();
void printer_add_data(f32 *value);
void printer_set_core_count(u16 value);
void printer_stop();

#endif //CPU_USAGE_TRACKER_PRINTER_H
