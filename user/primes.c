#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void stage_loop(int p1[2]) {
    int p = 0;

    close(p1[1]); // we only need to read from last stage, so close last pipe's write end
    read(p1[0], &p, 4);

    if (p == 0) {
        exit(0);
    }

    printf("prime %d\n", p);

    int p2[2];
    pipe(p2);
    
    if (fork() == 0) {
        close(p2[0]); // need to write to next stage, so close p2's read end
        int n;

        while (read(p1[0], &n, 4)) {
            if (n % p) {
                write(p2[1], &n, 4);
            }
        }

        exit(0);
    } else {
        wait(0);

        close(p2[1]);
        close(p1[0]);

        stage_loop(p2);

        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int p1[2], p2[2];
    
    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        int p = 0; 
        int n;

        close(p1[1]);
        close(p2[0]);
        read(p1[0], &p, 4);

        if (p == 0) {
            exit(0);
        }

        printf("prime %d\n", p);

        while (read(p1[0], &n, 4)) {
            if (n % p) {
                write(p2[1], &n, 4);
            }
        }

        exit(0);
    } else {
        close(p1[0]);

        for (int i = 2; i < 36; i ++) {
            write(p1[1], &i, 4);
        }

        close(p1[1]);

        wait(0);
        stage_loop(p2);

        close(p2[0]);
        close(p1[1]);
        
        exit(0);
    }
    
    exit(0);
}