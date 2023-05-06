#include "../csapp.h"

int main(int argc, char **argv) {
    struct addrinfo *p, *listp, hints;
    struct protoent *protocol;
    char hostbuf[MAXLINE], servbuf[MAXLINE]; 
    int rc, flags;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <domain name> <service name>\n", argv[0]);
        exit(0);
    }

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 only */
    //hints.ai_socktype = SOCK_STREAM; /* TCP Connections only */
    if ((rc = getaddrinfo(argv[1], argv[2], &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }
    
    /* Walk the list and display each IP address */
    flags = NI_NUMERICHOST | NI_NUMERICSERV; /* Display address string instead of domain name */
    for (p = listp; p; p = p->ai_next) {
        Getnameinfo(p->ai_addr, p->ai_addrlen, hostbuf, MAXLINE, servbuf, MAXLINE, flags);
        protocol = getprotobynumber(p->ai_protocol);
        printf("%s:%s; Protocol: %s; Socket type: %d\n", hostbuf, servbuf, protocol->p_name, p->ai_socktype);
    }
    
    /* Clean Up */
    Freeaddrinfo(listp);
    exit(0);
}