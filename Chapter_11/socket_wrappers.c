#include "csapp.h"

int open_clientfd(char *hostname, char *port) {
    int clientfd;
    struct addrinfo hints, *listp, *p;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_flags |= AI_ADDRCONFIG;
    Getaddrinfo(hostname, port, &hints, &listp);

    for (p = listp; p; p = p->ai_next) {
        if((clientfd = socket(p->ai_family, p->ai_socktype)) < 0) {
            continue; // Error creating socket, move to next address in list
        }

        if(connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) {
            break; // connection succeeded, break loop and move to end of function
        }
        Close(clientfd); // -1 returned from connect call, error connecting with socket
    }
    
    // Cleanup
    Freeaddrinfo(listp);
    if(!p) {
        return -1; // p is NULL so we reached the end of lisp linked list
    } else {
        return clientfd;
    }
}

int open_listenfd(char *port) {
    struct addrinfo hints, *listp, *p;
    int listenfd, optval=1;

    /* Get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // Flags for server sockets & Optional IPv6 addresses if supported
    hints.ai_flags |= AI_NUMERICSERV; // Name service with a numeric port number
    Getaddrinfo(NULL, port, &hints, &listp); // Get available addresses (ports) and socket types

    for(p = listp; p; p = p->ai_next) {
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
            continue; // Socket creation failed, try the next one in list
        }

        // Setup Socket options
        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int)); 

        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
            break;
        }

        Close(listenfd);
    }

    Freeaddrinfo(listp);
    if(!p) {
        return -1;
    }

    if (listen(listenfd, LISTENQ) < 0) {
        Close(listenfd);
        return -1;
    }

    return listenfd;
}
