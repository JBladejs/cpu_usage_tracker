//
// Created by Alan Ćwiek on 8/22/22.
//

#include <malloc.h>
#include <math.h>
#include <assert.h>
#include "../../src/file_io/statfile.h"
#include "../../src/helper/usage_calculator.h"

static void usage_test(void) {
    struct CpuStats *stats1 = calloc(1, sizeof(struct CpuStats));
    struct CpuStats *stats2 = calloc(1, sizeof(struct CpuStats));
    f64 usage;

    stats2->user = 50;
    stats2->nice = 50;
    stats2->system = 50;
    stats2->idle = 50;
    stats2->iowait = 50;
    stats2->irq = 50;
    stats2->softirq = 50;

    usage = (f64) usage_calculator_get_usage(stats1, stats2);
    assert(fabs(usage - 71.4) < 0.1);

    free(stats1);
    free(stats2);
}

int main(void) {
    usage_test();
    return 0;
}
