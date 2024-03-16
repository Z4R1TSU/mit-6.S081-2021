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

-----

2. symbolic link

    > main idea:  
    Symbolic links (or soft links) refer to a linked file by pathname.  
    `symlink(char *target, char *path)` system call creates a new symbolic link at path that points to file named by target.

    TODO: 
    
    * [x]  create a new system call number for `symlink`, add an entry to `user/usys.pl`, `user/user.h`, and implement an empty `sys_symlink` in `kernel/sysfile.c`.

    * [x] Add a new file type (`T_SYMLINK`) to `kernel/stat.h` to represent a symbolic link

    * [x] Add a new flag to `kernel/fcntl.h`, (`O_NOFOLLOW = 0x004`) to open system call. Note that flags passed to open are combined using a bitwise OR operator, so your new flag should not overlap with any existing flags. This will let you compile user/symlinktest.c once you add it to the Makefile.

    * [x] store the target path of a symbolic link in the inode's ***data blocks***.

    * [x] `symlink` should return an integer representing success (0) or failure (-1) similar to link and unlink.

    * [x] Modify the `open` system call where the path refers to a symbolic link.  
    Case 1: If the file does not exist, open must fail.  
    Case 2: When a process specifies O_NOFOLLOW in the flags to open, open should open the symlink (and not follow the symbolic link)

    * [x] recursively call `symlink()` when the linked file is also a symbolic link. If revursive depth reach threshold (10) return -1

    * [x] You do not have to handle symbolic links to directories.
