#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pid = fork();
    int p1[2], p2[2];

    // parent send and child receive
    pipe(p1);
    // parent receive and child send
    pipe(p2);

    char *buf = (char*)' ';

    if (pid < 0) {
        printf("fork failed!\n");
        exit(1);
    } else if (pid == 0) {
        close(p1[1]); // child read
        close(p2[0]); // child write

        read(p1[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p2[1], (char*)'c', 1);

        close(p1[0]);
        close(p2[1]);
    } else {
        close(p1[0]); // parent write
        close(p2[1]); // parent read

        write(p1[1], (char*)'p', 1);
        wait(0); // wait child to print to prevent parallel
        printf("%d: received pong\n", getpid());
        read(p2[0], buf, 1);

        close(p1[1]);
        close(p2[0]);
    }

    exit(0);
}