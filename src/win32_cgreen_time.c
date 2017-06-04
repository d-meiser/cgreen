#include "cgreen/internal/cgreen_time.h"
#include <stdint.h>
#include <stdio.h>
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#include <unistd.h>
#endif
#include <windows.h>

static LARGE_INTEGER qry_freq;
static int qry_freq_initialized = 0;

uint32_t cgreen_time_get_current_milliseconds() {
    if (!qry_freq_initialized) {
        QueryPerformanceFrequency(&qry_freq);
        qry_freq_initialized = 1;
    }

    LARGE_INTEGER current_count;
    QueryPerformanceCounter(&current_count);

    current_count.QuadPart = current_count.QuadPart * 1000000 / qry_freq.QuadPart;

    return trunc(current_count.QuadPart / 1000);
}

/* vim: set ts=4 sw=4 et cindent: */
