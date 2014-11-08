#include "util.h"


char* getErrorString(Error_t status) {
	/*
		TODO Complete implementation.
	*/
    return "";
}


Error_t newProgress(Progress_t *p, const char *unit, int total, double report_rate) {

    *p = malloc(sizeof (struct Progress_st));

    if (*p == NULL)
        return errMemoryAllocationError;

    (*p)->current = 0;
    (*p)->req_tick_per_report = MAX(MIN(MAX(report_rate, 0.001), 1.) * total, MIN_REQ_TICK_PER_REPORT);

    (*p)->unit = strdup(unit);

    log_info ("Report for every %d %s\n", (*p)->req_tick_per_report, (*p)->unit);
    (*p)->total = total;

    gettimeofday(&((*p)->last_report_epoch), NULL);
    (*p)->last_tick_count = 0;

    return errSucess;

}

Error_t deleteProgress(Progress_t p){
    free(p->unit);
    free(p);


    return errSucess;
}

bool tickProgress(Progress_t p) {

    if (p->current < p->total) {
        (p->current)++;
    	struct timeval current_epoch, timerElapsed;

        gettimeofday(&current_epoch, NULL);
        timersub(&current_epoch, &( p->last_report_epoch), &timerElapsed);

        double elapsed_sec = timerElapsed.tv_sec +timerElapsed.tv_usec/1000000.0;
        if (p->current == p->total) {

            log_info("100.00%% of %d %s are done", p->current, p->unit);

            log_info( "%d more %s in %lf sec.", p->current - p->last_tick_count, p->unit, elapsed_sec);

            gettimeofday(&(p->last_report_epoch), NULL);

            p->last_tick_count = p->current;

            return true;
        }
        else if (p->current % p->req_tick_per_report == 0) {

            log_info( "%.2f%%(%d) of %s are done", ((p->current * 1.) * 100.) / (p->total), p->current,p->unit);

            log_info( "%d more %s in %lf sec.", p->current - p->last_tick_count, p->unit, elapsed_sec);

            gettimeofday(&(p->last_report_epoch), NULL);

            p->last_tick_count = p->current;

            return true;
        }
    }

    return false;

}

DArray* range(int start, int end){
    DArray *result = DArray_create(sizeof(int), end - start);
    check_mem(result);
    
    for (int v=start; v < end; v++) {
        int* i = (int*)malloc(sizeof(int));
        check_mem(i);
        
        *i = v;
        
        DArray_push(result, i);
    }
    
    return result;
error:
    exit(1);
}

DArray* parse_range(const char *rangestr){
    DArray *result = DArray_create(sizeof(int), 1);
    check_mem(result);
    
    if (strchr(rangestr, '-') != NULL){
        DArray *tokens = split(rangestr, "-");
        
        check(DArray_count(tokens) == 2, "Invalid range string %s %d", rangestr, DArray_count(tokens) == 2);
        
        int start = atoi((char*)DArray_get(tokens, 0));
        int end = atoi((char*)DArray_get(tokens, 1));
        
        DArray_clear_destroy(tokens);
        
        return range(start, end);
        
    }else if (strchr(rangestr, ',') != NULL){
        DArray *tokens = split(rangestr, ",");
        
        for(int i = 0;i < DArray_count(tokens);i++){
            int *iptr = (int*)malloc(sizeof(int));
            check_mem(iptr);
            
            *iptr = atoi((char*)DArray_get(tokens, i));
            
            DArray_push(result, iptr);
        }
        
        DArray_clear_destroy(tokens);
    }else{
        int *iptr = (int*)malloc(sizeof(int));
        check_mem(iptr);
        
        *iptr = atoi(rangestr);
        
        DArray_push(result, iptr);
    }
    
    
    return result;
error:
    exit(1);
}

char* join_range(DArray *range){
    char* buffer = (char*)malloc(sizeof(char) * 1024);
    check_mem(buffer);
    
    buffer[0] = '\0';
    
    for (int i = 0 ; i < DArray_count(range); i++) {
        
        if (i == 0 ){
            sprintf(buffer, "%d", *((int*)DArray_get(range, i)));
        }else{
            sprintf(buffer, "%s, %d", buffer, *((int*)DArray_get(range, i)));
        }
    }
    
    return buffer;
error:
    exit(1);
}
