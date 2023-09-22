// Set the Week to 1, 2, or 3 for that part of the project. This enables
// additional functionality.

#define WEEK 3  // 1, 2, 3, 4 (extensions)

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <assert.h>
#include "myalloc.h"

struct block {
    struct block *next;
    int size;        // bytes
    int in_use;      // bool
    long padding;
};

static struct block *head = NULL;
static enum strategy strategy = STRATEGY_FIRST_FIT;

#define ENABLE_SPLIT (WEEK >= 2)
#define ENABLE_CONSOLIDATE (WEEK >= 3)
#define ENABLE_MMAP_CHAIN (WEEK > 3)

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

static int get_total_pages_size(int size)
{
    //long page_size = sysconf(_SC_PAGESIZE);

    long page_size = 1024;

    // Assumes page_size is a power of 2

    // Round up to the nearest multiple of page_size bytes
    int bytes_needed = size + (((page_size - 1) - (size - 1)) & (page_size - 1));
    
    return bytes_needed;
}

static struct block *mmap_new(int padded_size)
{
    struct block *b;

    int memory_size = get_total_pages_size(padded_size);

    b = mmap(NULL, memory_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);

    if (b == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    b->next = NULL;
    b->size = memory_size - HEADER_SIZE;
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
#if ENABLE_SPLIT
    struct block *old_next = b->next;
    int old_size = b->size;
    size_t new_padded_size = PADDED_SIZE(size);

    int have_room = new_padded_size + HEADER_SIZE + 16 <= (size_t)b->size;

    if (have_room) {
        struct block *new_free_block = PTR_OFFSET(b, HEADER_SIZE + new_padded_size);

        new_free_block->next = old_next;
        new_free_block->size = old_size - new_padded_size - HEADER_SIZE;
        new_free_block->in_use = 0;

        b->next = new_free_block;
        b->size = new_padded_size;
    }
#else
    (void)b;
    (void)size;
#endif
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

#if !ENABLE_MMAP_CHAIN
    // This only allows mmap_new() to run one time
    if (head != NULL) return NULL;
#endif

    if ((b = mmap_new(size + HEADER_SIZE)) != NULL) {
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
    // This is a total hack to make the tests work like the student
    // tests.
    if ((size_t)PADDED_SIZE(size) > 1024 - PADDED_SIZE(sizeof(struct block)))
        return NULL;

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
#if ENABLE_CONSOLIDATE
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
#endif
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

// This part to include in student submission

#include <stdlib.h>

void beej_print_data(void)
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

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "usage: %s mode\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);

    switch (mode) {

#if WEEK >= 1

        case 0: {  // WEEK 1+
            beej_print_data();
            myalloc(64);
            beej_print_data();
        }
        break;

        case 1: {  // WEEK 1+
            void *p;

            beej_print_data();
            p = myalloc(16);
            printf("%p\n", p);
            beej_print_data();
            p = myalloc(16);
            printf("%p\n", p);
            beej_print_data();
        }
        break;
#endif
#if WEEK >= 2

        case 2: {  // WEEK 2+
            void *p;

            myalloc(10);     beej_print_data();
            p = myalloc(20); beej_print_data();
            myalloc(30);     beej_print_data();
            myfree(p);       beej_print_data();
            myalloc(40);     beej_print_data();
            myalloc(10);     beej_print_data();
        }
        break;

        case 3: {
            void *p;

            p = myalloc(512);
            beej_print_data();

            myfree(p);
            beej_print_data();
        }
        break;

        case 4: {
            myalloc(10); beej_print_data();
            myalloc(20); beej_print_data();
            myalloc(30); beej_print_data();
            myalloc(40); beej_print_data();
            myalloc(50); beej_print_data();
        }
        break;

        case 5: {
            int bs = PADDED_SIZE(sizeof(struct block));

            myalloc((1024-bs)); beej_print_data();
        }
        break;

        case 6: {
            int bs = PADDED_SIZE(sizeof(struct block));

            myalloc((1024-bs)-bs); beej_print_data();
        }
        break;

        case 7: {
            int bs = PADDED_SIZE(sizeof(struct block));

            myalloc(((1024-bs)-bs)-16); beej_print_data();
        }
        break;

        case 8: {
            int bs = PADDED_SIZE(sizeof(struct block));

            myalloc(((1024-bs)-bs)-32); beej_print_data();
        }
        break;

        case 9: {
            void *p = myalloc(99999);
            int bs = PADDED_SIZE(sizeof(struct block));
            printf("NULL check 1: %s\n", p == NULL? "PASS": "FAIL");
            p = myalloc(1024);
            printf("NULL check 2: %s\n", p == NULL? "PASS": "FAIL");
            p = myalloc(1024-bs+1);
            printf("NULL check 3: %s\n", p == NULL? "PASS": "FAIL");
        }
        break;
#endif
#if WEEK >= 3
        case 10: { // WEEK 3+
            void *p;

            p = myalloc(10); print_data();

            myfree(p); print_data();
        }
        break;

        case 11: {
            void *p, *q;

            p = myalloc(10); print_data();
            q = myalloc(20); print_data();

            myfree(p); print_data();
            myfree(q); print_data();
        }
        break;

        case 12: {
            void *p, *q;

            p = myalloc(10); print_data();
            q = myalloc(20); print_data();

            myfree(q); print_data();
            myfree(p); print_data();
        }
        break;

        case 13: {
            void *p, *q, *r, *s;

            p = myalloc(10); print_data();
            q = myalloc(20); print_data();
            r = myalloc(30); print_data();
            s = myalloc(40); print_data();

            myfree(q); print_data();
            myfree(p); print_data();
            myfree(s); print_data();
            myfree(r); print_data();
        }
        break;

        case 14: { // WEEK 3+
            void *p, *q;

            p = myalloc(512);
            beej_print_data();

            myfree(p);
            beej_print_data();

            p = myalloc(16);
            beej_print_data();

            q = myalloc(128);
            beej_print_data();

            myfree(p);
            beej_print_data();

            char *r = myalloc(100);
            beej_print_data();

            myfree(q);
            beej_print_data();

            myfree(r);
            beej_print_data();
        }
        break;

        case 15: {
            void *p, *q;

            p = myalloc(600);
            beej_print_data();
            q = myalloc(512);
            beej_print_data();
            printf("NULL check 1: %s\n", p != NULL? "PASS": "FAIL");
            printf("NULL check 2: %s\n", q == NULL? "PASS": "FAIL");
            myfree(p);
            beej_print_data();
            p = myalloc(600);
            beej_print_data();
            myfree(p);
            beej_print_data();
        }
        break;
#endif
        default:
            fprintf(stderr, "%s: unknown mode\n", argv[0]);
            return 2;
    }
}
