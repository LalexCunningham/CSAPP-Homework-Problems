/*
    linux> fstatcheck 3 < foo.txt

    Fails: "bad file descriptor".

    Fill in the code that the shell must be executing between the Fork and Execve calls
*/

#include "./../csapp.h"

int main(int argc, char const *argv[], char const *envp[])
{
    if (Fork() == 0) {
        /* What code is the shell executing right here? */
        int fd = open(argv[2], O_RDONLY, 0);

        Dup2(3, fd);
        Execve("fstatcheck", argv, envp);
    }
    return 0;
}
