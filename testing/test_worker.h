#ifndef _NSTU_TEST_WORKER_H
#define _NSTU_TEST_WORKER_H

#include "../str/str.h"

struct PythonTestWorker {
    str _solution_path, _tests_path;
    unsigned int _task_id, _task_variant, _threads_amount;
};

typedef struct PythonTestWorker PythonTestWorker;

#endif