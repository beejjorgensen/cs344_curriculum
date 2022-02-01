#ifndef MYALLOC_H
#define MYALLOC_H

enum strategy {
    STRATEGY_FIRST_FIT,
    STRATEGY_BEST_FIT,
    STRATEGY_WORST_FIT
};

void *myalloc(int size);
void myfree(void *p);
void mystrategy(enum strategy s);

#endif