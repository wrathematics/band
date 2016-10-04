#ifndef __COOP_UTILS_INTERNAL_TIMER_H__
#define __COOP_UTILS_INTERNAL_TIMER_H__

#include <time.h>
#include <stdio.h>
#include <math.h>

static clock_t _internal_timer_start, _internal_timer_stop;
static double _internal_time_x;
static double _internal_time_mean;
static double _internal_time_delta;
static double _internal_time_sd;
static double _internal_time_M2;

static int _internal_timer_first_print = 1;

#define TIMER(expression,nreps) \
  _internal_time_mean = 0.0; \
  _internal_time_M2 = 0.0; \
  if (_internal_timer_first_print){ \
    _internal_timer_first_print = 0; \
    printf("### Expression \t\t\t   reps   Total   Mean    Sd\n"); \
    for (int _internal_time_i=0; _internal_time_i<63; _internal_time_i++) putchar('-'); \
    putchar('\n'); \
  } \
  for (int _internal_time_i=0; _internal_time_i<nreps; _internal_time_i++){ \
    _internal_timer_start = clock(); \
    expression; \
    _internal_timer_stop = clock(); \
    _internal_time_x = (double) (_internal_timer_stop - _internal_timer_start)/CLOCKS_PER_SEC; \
    _internal_time_delta = _internal_time_x - _internal_time_mean; \
    _internal_time_mean += _internal_time_delta / (_internal_time_i+1); \
    _internal_time_M2 += _internal_time_delta * (_internal_time_x - _internal_time_mean); \
  } \
  _internal_time_sd = sqrt(_internal_time_M2 / ((double)nreps-1)); \
  printf("| %-28s    | %3d | %.3f | %.3f | %.3f\n", #expression, nreps, _internal_time_mean*nreps, _internal_time_mean, _internal_time_sd);

#endif
