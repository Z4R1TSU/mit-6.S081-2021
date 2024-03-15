# lab 9 file system

1. large file
    
    > main idea:  
    doubly-indirect block: 256*256+256+11 blocks, sacrifice one of the direct block numbers for the double-indirect block.    
    
    TODO:

    * [x] Make sure you understand `bmap()`.

    * [x] change the definition of `NDIRECT` and the declaration of `addrs[]` in `struct inode` in `file.h`. Make sure that `struct inode` and `struct dinode` have the same number of elements in their `addrs[]` arrays.

    * [x] `brelse()` each block that you `bread()`.
    
    * [x] Make sure `itrunc` frees all blocks of a file, including double-indirect blocks

    > grade:  
    $ bigfile
..................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
wrote 65803 blocks
bigfile done; ok

