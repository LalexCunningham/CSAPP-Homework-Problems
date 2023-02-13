#include <unistd.h>
#include <stdio.h>

int waitAndFlush();

int main(int argc, char const *argv[])
{
    printf("First, %d, %d, Second\n", fflush(stdout), waitAndFlush());
    return 0;
}

int waitAndFlush() {
    fflush(stdout);
    sleep(5);
    return 1;
}

/* Output buffer is empty both times fflush is called */