#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"

// see Chapter 1 Section 3 in Page 16 pipes
// the input before the pipe '|' will be regarded as standard input

int main(int argc, char *argv[]) {
    char *stdin[MAXARG];
    char buf[1024];
    char *p = buf;

    while (read(0, p, 1)) {

    }

    for (i = 0; i < MAXARG; i ++) {
        if (stdin[i]) {
            if (fork() == 0) {
                char *clcmd = argv[1];
            } else {
                wait(0);
            }
        }
    }

    exit(0);
}