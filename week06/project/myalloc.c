#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "myalloc.h"

struct block {
    struct block *next;
    int size;        // bytes
    int in_use;      // bool
};

static struct block *head = NULL;
static enum strategy strategy = STRATEGY_FIRST_FIT;

#define MEM_SIZE 1024

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - ((x - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PADDED_SIZEOF(x) (sizeof(x) + GET_PAD(sizeof (x)))

#define HEADER_SIZE (PADDED_SIZEOF(struct block))

#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        fflush(stdout);

        b = b->next;
    }

    printf("\n");
}

static int get_break_size(int size)
{
    long page_size = sysconf(_SC_PAGESIZE);

    page_size = 1024;

    // Assumes page_size is a power of 2

    // Round up to the nearest multiple of page_size bytes
    int bytes_needed = size + ((page_size - 1) - (size - 1) & (page_size - 1));
    
    return bytes_needed;
}

static struct block *break_new(int size)   // Including header and all padding
{
    struct block *b;

    int break_incr = get_break_size(size);

    if ((b = sbrk(break_incr)) == (void*)(-1)) {
        perror("sbrk");
        return NULL;
    }
    
    b->next = NULL;
    b->size = break_incr - HEADER_SIZE;
    b->in_use = 0;

    return b;
}

static struct block *find_space_first_fit(int size, struct block **tail)
{
    struct block *cur = head;

    *tail = NULL;

    while(cur != NULL) {
        if (!cur->in_use && cur->size >= size) {
            return cur;
        }
        *tail = cur;
        cur = cur->next;
    }

    return NULL;
}

static struct block *find_space_best_fit(int size, struct block **tail)
{
    struct block *cur = head;
    int best_size;
    struct block *best_block = NULL;

    while(cur != NULL) {
        if (!cur->in_use && cur->size >= size) {
            if (best_block == NULL || cur->size < best_size) {
                best_size = cur->size;
                best_block = cur;
            }
        }
        *tail = cur;
        cur = cur->next;
    }

    return best_block;
}

static struct block *find_space_worst_fit(int size, struct block **tail)
{
    struct block *cur = head;
    int worst_size;
    struct block *worst_block = NULL;

    while(cur != NULL) {
        if (!cur->in_use && cur->size >= size) {
            if (worst_block == NULL || cur->size > worst_size) {
                worst_size = cur->size;
                worst_block = cur;
            }
        }
        *tail = cur;
        cur = cur->next;
    }

    return worst_block;
}

static void split_space(struct block *b, int size)
{
    struct block *old_next = b->next;

    size_t old_block_size = HEADER_SIZE + b->size;
    size_t min_split_size = (HEADER_SIZE + 16) * 2;

    if (old_block_size >= min_split_size) {
        size_t new_padded_size = PADDED_SIZE(size);
        struct block *new_free_block = PTR_OFFSET(b, HEADER_SIZE + new_padded_size);

        new_free_block->next = old_next;
        new_free_block->size = b->size - (HEADER_SIZE + new_padded_size);
        new_free_block->in_use = 0;

        b->next = new_free_block;
        b->size = new_padded_size;
    }
}

static struct block *find_space(int size)
{
    struct block *tail, *b;

    struct block *(*find_space_func)(int, struct block **) = NULL;

    switch (strategy) {
        case STRATEGY_FIRST_FIT:
            find_space_func = find_space_first_fit;
            break;
        case STRATEGY_BEST_FIT:
            find_space_func = find_space_best_fit;
            break;
        case STRATEGY_WORST_FIT:
            find_space_func = find_space_worst_fit;
            break;
        default:
            assert(find_space_func != NULL);
    }

    if ((b = find_space_func(size, &tail)) != NULL) {
        split_space(b, size);
        return b;
    }

    if ((b = break_new(size + HEADER_SIZE)) != NULL) {
        if (tail == NULL)
            head = b;
        else
            tail->next = b;

        split_space(b, size);
        return b;
    }

    return NULL;
}

void *myalloc(int size)
{
    // Find a big enough space
    struct block *b;

    if ((b = find_space(PADDED_SIZE(size))) != NULL) {
        // Found a space
        b->in_use = 1;
        return PTR_OFFSET(b, HEADER_SIZE);
    }

    // No memory found or allocated
    return NULL;
}

static void consolidate(void)
{
    struct block *cur = head;

    assert(cur != NULL);

    while (cur->next != NULL) {
        if (!cur->in_use && !cur->next->in_use) {
            cur->size += HEADER_SIZE + cur->next->size;
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
}

void myfree(void *p)
{
    struct block *b = PTR_OFFSET(p, -HEADER_SIZE);
    b->in_use = 0;

    consolidate();
}

void mystrategy(enum strategy s)
{
    strategy = s;
}

int main(void)
{
#if 0
    void *p, *q;

    p = myalloc(512);
    print_data();

    myfree(p);
    print_data();

    p = myalloc(16);
    print_data();

    q = myalloc(128);
    print_data();

    myfree(p);
    print_data();

    char *r = myalloc(10000);
    print_data();

    myfree(q);
    print_data();

    myfree(r);
    print_data();
#endif

    void *p;

    myalloc(10);     print_data();
    p = myalloc(20); print_data();
    myalloc(30);     print_data();
    myfree(p);       print_data();
    myalloc(40);     print_data();
    myalloc(10);     print_data();
}