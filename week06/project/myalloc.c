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

#define MEM_SIZE 1024

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (x - 1) & (ALIGNMENT - 1))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PADDED_SIZEOF(x) (sizeof(x) + GET_PAD(sizeof (x)))

#define HEADER_SIZE (PADDED_SIZEOF(struct block))

#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

//#define STRATEGY_FIRST_FIT
#define STRATEGY_BEST_FIT

void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        fflush(stdout);

        b = b->next;
    }

    printf("\n");
}

static void init_space(void) {
    // If we haven't allocated memory yet, let's do it
    if ((head = sbrk(MEM_SIZE)) == (void*)(-1)) {
        head = NULL;
        perror("sbrk");
        return;
    }
    
    head->next = NULL;
    head->size = MEM_SIZE - HEADER_SIZE;
    head->in_use = 0;
}

#ifdef STRATEGY_FIRST_FIT
static struct block *find_space(int size)
{
    struct block *cur = head;

    while(cur != NULL) {
        if (!cur->in_use && cur->size >= size) {
            return cur;
        }
        cur = cur->next;
    }

    return NULL;

}
#endif

#ifdef STRATEGY_BEST_FIT
static struct block *find_space(int size)
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
        cur = cur->next;
    }

    return best_block;
}
#endif

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

void *myalloc(int size)
{
    // Do the initial allocation
    if (head == NULL)
        init_space();

    // Find a big enough space
    struct block *b;

    if ((b = find_space(size)) != NULL) {
        split_space(b, size);
        b->in_use = 1;
        return PTR_OFFSET(b, HEADER_SIZE);
    }

    // Unable to find a big enough space
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

int main(void)
{
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

    myfree(q);
    print_data();
}
