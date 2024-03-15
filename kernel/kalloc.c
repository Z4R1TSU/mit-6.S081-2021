// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

// maintain a free list per CPU (NCPU = 8)
struct {
  struct spinlock lock;
  struct run *freelist;
} kmem[NCPU];

// all of locks names must start with "kmem"
char *lockname[NCPU] = {
  "kmem0", "kmem1", "kmem2", "kmem3", "kmem4", "kmem5", "kmem6", "kmem7"
};

void
kinit()
{
  for (int i = 0; i < NCPU; i ++) {
    initlock(&kmem[i].lock, "kmem");
  }
  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // take on/off interruption to avoid deadlock
  push_off();

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  int idx = cpuid();

  acquire(&kmem[idx].lock);
  r->next = kmem[idx].freelist;
  kmem[idx].freelist = r;
  release(&kmem[idx].lock);

  pop_off();
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  push_off();

  struct run *r;
  int idx = cpuid();

  acquire(&kmem[idx].lock);

  if (!kmem[idx].freelist) {
    int cnt = 0;
    
    for (int i = 0; i < NCPU; i ++) {
      if (i == idx) {
        continue;
      }

      acquire(&kmem[i].lock);

      struct run *steal = kmem[i].freelist;

      while (steal && cnt < NPROC) {
        kmem[i].freelist = steal->next;
        steal->next = kmem[idx].freelist;
        kmem[idx].freelist = steal;
        steal = kmem[idx].freelist;

        cnt ++;
      }

      release(&kmem[i].lock);
    }
  }

  r = kmem[idx].freelist;
  if(r)
    kmem[idx].freelist = r->next;
  
  release(&kmem[idx].lock);

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk

  pop_off();

  return (void*)r;
}
