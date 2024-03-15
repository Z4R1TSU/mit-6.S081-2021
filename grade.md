# lab 8 lock

1. kalloctest
    * [x] maintain a free list per CPU to avoid a single lock and list for removing lock convention, each list with its own lock

    * [x] all of locks names must start with "*kmem*". That is, you should call `initlock` for each of your locks, and pass a name that starts with "kmem"
    
    * [] one CPU whose free list is empty must steal part of other CPU's free list which has free memory

    * [x] `NCPU` from kernel/param.hS

    * [x] `freerange` give all free memory to the CPU

    * [x] `cpuid()`

    * [x `push_off()` and `pop_off()` to turn interrupts off and on

    * [] `snprintf()` in kernel/sprintf.c for string formatting