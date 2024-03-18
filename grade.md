# lab 10 mmap

> main idea:  
>   `void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)`<br>
>   1. `mmap()` returns that address, or 0xffff_ffff_ffff_ffff if it fails.
>   2. ***addr*** will always be zero, meaning that the kernel should decide the virtual address at which to map the file.
>   3. ***length*** is # bytes to map; it might not be the same as the file's length.
>   4. ***prot*** indicates whether the memory should be mapped readable, writeable, and/or executable
>   5. ***flags*** will be either MAP_SHARED(modifications to the mapped memory should be written back to the file) or MAP_PRIVATE(meaning that they should not).
>   6. ***fd*** is the open file descriptor of the file to map.
>   7. ***offset*** is zero (it's the starting point in the file at which to map)  
>
>   `munmap(addr, length)`<br>
>   1. remove mmap mappings in the indicated address range.

<br>

TODO:  
* [x] add _mmaptest to `UPROGS`, and mmap and munmap system calls
* [x] Fill in the page table lazily(lazy allocation) in `usertrap()`
* [x] Define a structure corresponding to the VMA recording the address, length, permissions, file, etc, which is a array of size 16.
* [] the rest of this lab just let it go...I am tired.