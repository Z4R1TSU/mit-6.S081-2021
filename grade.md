# lab 5 COW

* [x] Modify ***uvmcopy()*** to map the parent's physical pages into the child, instead of allocating new pages. Clear PTE_W in the PTEs of both child and parent.
* [x] Modify ***usertrap()*** to recognize page faults. When a page-fault occurs on a COW page, allocate a new page with ***kalloc()***, copy the old page to the new page, and install the new page in the PTE with PTE_W set.
* [x] ***kfree()*** should only place a page back on the free list if its reference count is zero. Set a page's reference count to one when ***kalloc()*** allocates it. Increment a page's reference count when fork causes a child to share the page, and decrement a page's count each time any process drops the page from its page table.
* [] Modify ***copyout()*** to use the same scheme as page faults when it encounters a COW page.