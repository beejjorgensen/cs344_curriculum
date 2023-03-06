#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
Memory map:

zero page:

0-63: free page map
64-255: process page table pointer

ptsim np 1 256 pv 1 
*/

#define MEM_SIZE 16384  // MUST equal PAGE_SIZE * PAGE_COUNT
#define PAGE_SIZE 256  // MUST equal 2^PAGE_SHIFT
#define PAGE_COUNT 64
#define PAGE_SHIFT 8  // Shift page number this much

#define PTP_OFFSET 64 // How far offset in page 0 is the page table pointer table

// Simulated RAM
unsigned char mem[MEM_SIZE];

//
// Convert a page,offset into an address
//
int get_address(int page, int offset)
{
    return (page << PAGE_SHIFT) | offset;
}

//
// Initialize RAM
//
void initialize_mem(void)
{
    memset(mem, 0, MEM_SIZE);

    int zpfree_addr = get_address(0, 0);
    mem[zpfree_addr] = 1;  // Mark zero page as allocated
}

//
// Allocate a physical page
//
// Returns the number of the page, or 0xff if no more pages available
//
unsigned char get_page(void)
{
    int free_table_base = get_address(0, 0);

    // Search for the first free
    for (int offset = 0; offset < PAGE_COUNT; offset++) {
        if (mem[free_table_base + offset] == 0) { // if free?
            mem[free_table_base + offset] = 1; // now used
            return offset;
        }
    }

    return 0xff;
}

//
// Mark a physical page as free
//
void free_page(unsigned char page)
{
    int free_table_base = get_address(0, 0);

    mem[free_table_base + page] = 0;
}

//
// Get the page table page for a given process
//
unsigned char get_page_table(int proc_num)
{
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    return mem[ptp_addr];
}

//
// Free all pages associated with a process
//
void free_all_process_pages(int proc_num)
{
    // Get the process page table
    int page_table = get_page_table(proc_num);

    // Free process pages
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);

        int page = mem[addr];

        if (page != 0)
            free_page(page);
        else
            break;
    }

    // Free page table
    free_page(page_table);
}

//
// Allocate pages for a new process
//
// This includes the new process page table and page_count data pages.
//
void new_process(int proc_num, int page_count)
{
    // Get a page table page for this process
    unsigned char page_table = get_page();

    if (page_table == 0xff) {
        printf("OOM: proc %d: page table\n", proc_num);
        return;
    }

    // Set the page table pointer for this process
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    mem[ptp_addr] = page_table;

    // Initialize the page table

    // Zero the whole page table
    for (int i = 0; i < PAGE_SIZE; i++) {
        int addr = get_address(page_table, i);
        mem[addr] = 0;
    }

    // Allocate blocks
    for (int i = 0; i < page_count; i++) {
        int addr = get_address(page_table, i);

        int page_num = get_page();

        if (page_num == 0xff) {
            printf("OOM: proc %d: data page\n", proc_num);
            return;
        }

        mem[addr] = page_num;
    }
}

//
// Deallocate all resources for a process
//
void kill_process(int proc_num)
{
    free_all_process_pages(proc_num);
}


//
// Add pages to an existing process
//
void add_pages(int proc_num, int page_count)
{
    // Get the process page table
    int page_table = get_page_table(proc_num);

    // Find the highest used entry in the table
    int next_free_entry = -1;
    
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);

        unsigned char page = mem[addr];

        if (page == 0) {
            next_free_entry = i;
            break;
        }
    }

    if (next_free_entry == -1) {
        printf("NO FREE PAGE TABLE ENTRIES: proc %d\n", proc_num);
        return;
    }

    // If we have more entries
    for (int i = next_free_entry; i < next_free_entry + page_count; i++) {
        int addr = get_address(page_table, i);

        mem[addr] = get_page();
        if (mem[addr] == 0xff) {
            printf("OOM: proc %d, add_pages\n", proc_num);
            break;
        }
    }
}


//
// Convert a virtual address to a physical address
//
int vaddr_to_addr(int proc_num, int vaddr)
{
    // Get the process page table
    int page_table = get_page_table(proc_num);

    // Figure out the virtual page number
    int vpage = vaddr >> PAGE_SHIFT;
    
    // Figure out the offset
    int offset = vaddr & (PAGE_SIZE - 1);

    // Look in the page table with the virtual page
    // number as the index to get the physical page
    int addr = get_address(page_table, vpage);
    int page = mem[addr];

    if (page == 0) {
        return -1;
    }

    return get_address(page, offset);
}

//
// Store a value in memory at a virtual address
//
void store_byte(int proc_num, int vaddr, unsigned char val)
{
    int addr = vaddr_to_addr(proc_num, vaddr);

    if (addr == -1) {
        printf("PAGE FAULT: proc %d, store, vaddr %d\n", proc_num, vaddr);
        return;
    }

    printf("Store proc %d: %d => %d, value=%d\n",
        proc_num, vaddr, addr, val);

    mem[addr] = val;
}

//
// Load a value in memory at a virtual address
//
void load_byte(int proc_num, int vaddr)
{
    int addr = vaddr_to_addr(proc_num, vaddr);

    if (addr == -1) {
        printf("PAGE FAULT: proc %d, load, vaddr %d\n", proc_num, vaddr);
        return;
    }

    int val = mem[addr];

    printf("Load proc %d: %d => %d, value=%d\n",
        proc_num, vaddr, addr, val);
}

//
// Print the free page map
//
void print_page_free_map(void)
{
    printf("--- PAGE FREE MAP ---\n");

    for (int i = 0; i < 64; i++) {
        int addr = get_address(0, i);

        printf("%c", mem[addr] == 0? '.': '#');

        if ((i + 1) % 16 == 0)
            putchar('\n');
    }
}

//
// Print the address map from virtual pages to physical
//
void print_page_table(int proc_num)
{
    printf("--- PROCESS %d PAGE TABLE ---\n", proc_num);

    // Get the page table for this process
    int page_table = get_page_table(proc_num);

    // Loop through, printing out used pointers
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);

        int page = mem[addr];

        if (page != 0) {
            printf("%02x -> %02x\n", i, page);
        }
    }
}

//
// Main -- process command line
//
int main(int argc, char *argv[])
{
    assert(PAGE_COUNT * PAGE_SIZE == MEM_SIZE);

    if (argc == 1) {
        fprintf(stderr, "usage: ptsim commands\n");
        return 1;
    }
    
    initialize_mem();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "np") == 0) {
            int proc_num = atoi(argv[++i]);
            int pages = atoi(argv[++i]);
            new_process(proc_num, pages);
        }
        else if (strcmp(argv[i], "kp") == 0) {
            int proc_num = atoi(argv[++i]);
            kill_process(proc_num);
        }
        else if (strcmp(argv[i], "pfm") == 0) {
            print_page_free_map();
        }
        else if (strcmp(argv[i], "ppt") == 0) {
            int proc_num = atoi(argv[++i]);
            print_page_table(proc_num);
        }
        else if (strcmp(argv[i], "sb") == 0) {
            int proc_num = atoi(argv[++i]);
            int address = atoi(argv[++i]);
            int byte = atoi(argv[++i]);
            store_byte(proc_num, address, byte);
        }
        else if (strcmp(argv[i], "lb") == 0) {
            int proc_num = atoi(argv[++i]);
            int address = atoi(argv[++i]);
            load_byte(proc_num, address);
        }
        else if (strcmp(argv[i], "ap") == 0) {
            int proc_num = atoi(argv[++i]);
            int pages = atoi(argv[++i]);
            add_pages(proc_num, pages);
        }
    }
}
