#include "csapp.h"

#define RIO_BUFSIZE 8192
typedef struct {
	int rio_fd;					/* Descriptor for this internal buf */
	int rio_cnt;				/* Unread bytes in internal buf */
	char *rio_bufptr;			/* Next unread byte in internal buf */
	char rio_buf[RIO_BUFSIZE];	/* Internal buffer */
} rio_t;

ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

void rio_readinitb(rio_t *rp, int fd);

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, void usrbuf, size_t n);

ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
	size_t nleft = n;
	ssize_t nread = 0;
	char *bufp = userbuf;

	while (nleft > 0) {
		if ((nread = read(fd, bufp, nleft)) < 0) {
			if (errno == EINTR) { /* Interrupted by sig handler return */
				nread = 0;
			} else {
				return -1; /* errno set by read() */
			}
		} else if (nread == 0) {
			break;	/* EOF */
		}
		nleft -= nread;
		bufp += nread;
	}
	return (n - nleft); /* return >= 0 */
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n) {
	size_t nleft = n;
	ssize_t nwritten;
	char *bufp = usrbuf;

	while (nleft > 0) {
		if ((nwritten = write(fd, bufp, nleft)) <= 0) {
			if (errno == EINTR) {	/* Interrupted by sig handler return */
				nwritten = 0;
			} else {
				return -1;
			}
		}
		nleft -= nwritten;
		bufp += nwritten;
	}
	return n;
}

void rio_readinitb(rio_t *rp, int fd) {
	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n) {
	int cnt;

	while (rp->rio_cnt <= 0) { /* Refill if buf is empty */
		rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));	
		/*
			This read call effectively adds 'unread' bytes to the buffer
			by setting rio_cnt, and reading sizeof(rp->rio_buf) bytes from
			file fd to buffer rio_buf.

			Why sizeof(rp->rio_buf)?
				sizeof(arrayp) calculates the size of the array in bytes 
				(compiler generates a constant value for it at runtime)
				The call will write as many bytes to the buffer, if possible
				even the max amount of bytes ie size of the buffer
		*/

		if (rp->rio_cnt < 0) {
			if (errno != EINT) { /*  */
				return -1; /* Not interrupted by sig handler return, some kind of error condition */
			}
		} else if (rp->rio_cnt == 0) { /* EOF */
			return 0;
		} else { 
			rp->rio_bufptr = rp->rio_buf; /* Reset buffer ptr */	
		}
	}

	/* Copy min(n, rp->rio_cnt) bytes from internal buf to user buffer */
	/* Try to copy n bytes to user buffer, or if rio_cnt is smaller, copy that many */
	cnt = n;
	if (rp->rio_cnt < n) {
		cnt = rp->rio_cnt
	}
	memcpy(usrbuf, rp->rio_bufptr, cnt);
	rp->rio_bufptr += cnt;
	rp->rio_cnt -= cnt;
	return cnt;
}

ssize_t rio_readline(rio_t *rp, void *usrbuf, size_t maxlen) {
	int n, rc;
	char c, *bufp = usrbuf;

	for (n = 1; n < maxlen; n++) {
		if ((rc = rio_read(rp, &c, 1)) == 1) { /* Read 1 byte from internal buffer, if rc == 1, we were able to read the byte */
			*bufp++ = c;		/* Fill character into usrbuf, and incr out bufp pointer */
			if (c == '\n') {	/* Check if the character was a newline */
				n++;			/* Increment n, since it wont be done when we break */
				break;			
			}
		} else if (rc == 0) {	/* If rc == 0  read call wasn't able to read any byte */
			if (n == 1) {	
				return 0; /* EOF, no data was read */
			} else {
				break; /* EOF, some data was read (already gone through some iterations of the for loop */
			}
		} else {
			return -1 /* Error during read */
		}
	}

	*bufp = 0; /* Write '\0' to end of line */
	return n-1;
}

ssize_t rio_readnb(rio_t *rp, void usrbuf, size_t n) {
	size_t nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;

	while (nleft > 0) {
		if ((nread = rio_read(rip, bufp, nleft)) < 0) { 
			return -1;
		} else if (nread == 0) {
			break;
		}

		nleft -= nread;
		bufp += nread;
	}

	return (n - nleft);
}