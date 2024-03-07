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
// and the command after "xargs" will receive the stdin from the return value of command before "|"

void split_buffer(char *buf, char *argv[]) {
    int idx = 0;
    argv[idx ++] = buf;

    for (char *p = buf; *p; p ++) {
        if (*p == '\n') {
            *p = '\0';
            if (*(p + 1)) {
                argv[idx ++] = p + 1;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char *stdinput[MAXARG];
    char buf[1024];
    char *p = buf;

    while (read(0, p, 1)) {
        p ++;
    }

    split_buffer(buf, stdinput);

    for (int i = 0; i < MAXARG; i ++) {
        if (stdinput[i]) {
            if (fork() == 0) {
                char *clcmd = argv[1];
                int idx = 2;
                char *clarg[MAXARG] = {"0"};

                while (argv[idx]) {
                    clarg[idx - 1] = argv[idx];
                    idx ++;
                }
                clarg[idx - 1] = stdinput[i];

                exec(clcmd, clarg);
            } else {
                wait(0);
            }
        }
    }

    exit(0);
}