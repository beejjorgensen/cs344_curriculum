
### Algorithm to Deallocate a Page

You just have to mark it as unused in zero page.

```
DeallocatePage(page_number):
    addr = GetAddress(0, page_number);
    mem[addr] = 0
```
