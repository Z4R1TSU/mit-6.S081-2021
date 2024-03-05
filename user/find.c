#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// find the last token (last word after slash) in the path
// Q: why not use fmtname() instead?
// A: the string buf will cause store/AMO page fault.
char *get_last_token(char *path) {
    char *p;

    for (p = path + strlen(path); p >= path && *p != '/'; p --);

    // pointer p is at the index of the last slash, incre it to point to the first character of last token
    p ++;

    return p;
}

void find(char *direct, char* target) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(direct, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", direct);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", direct);
        close(fd);
        return;
    }

    switch (st.type) {
        case T_FILE:
            if (strcmp(get_last_token(direct), target) == 0) {
                printf("%s\n", direct);
            }
            break;

        case T_DIR:
            if (strlen(direct) + 1 + DIRSIZ + 1 > sizeof buf) {
                printf("find: path too long\n");
                break;
            }

            // buf = direct + '/'
            strcpy(buf, direct);
            p = buf + strlen(buf);
            *(p ++) = '/';

            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0) {
                    // if this directory's i number is invalid then skip
                    continue;
                }

                // buf += filename or directoryname
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;

                if (stat(buf, &st) < 0) {
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }

                if (strcmp(get_last_token(buf), ".") && strcmp(get_last_token(buf), "..")) {
                    find(buf, target);
                }
            }

            break;
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("invalid arguments!\n");
        exit(1);
    }

    char *direct = argv[1];
    char *target = argv[2];

    find(direct, target);

    exit(0);
}