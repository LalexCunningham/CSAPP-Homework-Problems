#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    char *replace = "Jello world!\n";
    off_t fsize;

    int fd = open("hello.txt", O_RDWR);
    fsize = lseek(fd, 0, SEEK_END);

    char *segment = mmap(NULL, fsize, PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < fsize; i++) {
        if (i < 14) {
            segment[i] = replace[i];
        } else {
            segment[i] = 0;
        }
    }

    return 0;
}
