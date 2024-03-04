#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char *t = argv[1];
    int time = atoi(t);

    sleep(time);

    exit(0);
}