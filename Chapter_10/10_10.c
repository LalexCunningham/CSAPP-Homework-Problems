#include "./../csapp.h"

int main(int argc, char **argv) {
    int n;
    rio_t rio;
    char buf[MAXLINE];

    if (argc > 0) {
        int infile = open(argv[0], O_RDONLY);
        dup2(infile, STDIN_FILENO);
    }

    Rio_readinitb(&rio, STDIN_FILENO);
    
    while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
        Rio_writen(STDOUT_FILENO, buf, n);
}