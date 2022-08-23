//
// Created by Alan Ćwiek on 8/21/22.
//

#ifndef CPU_USAGE_TRACKER_LOGGER_H
#define CPU_USAGE_TRACKER_LOGGER_H

#include "buffer.h"

void logger_init(void);

void logger_log(char *message);

void logger_destroy(void);

#endif //CPU_USAGE_TRACKER_LOGGER_H
