#ifndef __util_h__
#define __util_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"
#include "darray.h"
#include "stringalgo.h"
#include <sys/time.h>
#include <time.h>

#define MIN_REQ_TICK_PER_REPORT 25

#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

enum Error_t {
    errSucess,
    errUnknown,
    errMemoryAllocationError
};

typedef enum Error_t Error_t;

char* getErrorString(Error_t status);

#define CHECK_RETURN(v) {                                            \
        Error_t stat = v;                                     \
        if (stat != errSucess) {                                     \
            log_err( "%s", getErrorString(stat) );                  \
            exit(1);                                                            \
} }\

struct Progress_st {
    char *unit;
    int total;
    int current;
    int req_tick_per_report;

    struct timeval last_report_epoch;
    int last_tick_count;
};

typedef struct Progress_st* Progress_t;

/**
*
* @param p Reference to an Progress_t
* @param unit Name of the unit
* @param total Total number of ticks to be reached
* @param report_rate Reporting rate. If reporting rate if 0.05, for every 5% progress over total ticks will be reported.
* @return eparseSucess if creating Progress_t is succeed.
*/
Error_t newProgress(Progress_t *p, const char *unit, int total, double report_rate);

Error_t deleteProgress(Progress_t p);

/**
*
* @param p Progress tracking object
* @return Reporting indicator. true if tickProgress reached reporting threshold. Otherwise false.
*/
bool tickProgress(Progress_t p);


/**
 * @brief Returns a DArray containing integer sequence [start, end )
 * @param start
 * @param end
 * @return DArray containing all integers [start, end )
 */
DArray* range(int start, int end);
DArray* parse_range(const char *rangestr);

void print_range(const char *promt, DArray* range);
char* join_range(DArray *range);


#endif
