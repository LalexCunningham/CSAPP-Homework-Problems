#include "csapp.h"
#define MAXARGS 128
#define MAXPATH 1024

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
int getPathVector(char *pathVector);

int main(int argc, char const *argv[])
{
    char cmdline[MAXLINE]; /* Commandline buffer */

    while(1) {
        /* Read */
        printf("> ");
        Fgets(cmdline, MAXLINE, stdin);
        if(feof(stdin)) {
            exit(0);
        }

        /* Evaluate */
        eval(cmdline);
    }
    return 0;
}

/* Example Code */
/* Evaluate a Command Line */
void eval(char *cmdline) {
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE]; /* Hold modified command line */
    int bg; /* Background job or not */
    pid_t pid; /* Process id */

    strcpy(buf, cmdline); /* Copy cmdline to new buffer */
    bg = parseline(buf, argv); /* parse buff, fill argv, and return whether bg or not */
    if (argv[0]== NULL) {
        return; /* Ignore Empty Lines */
    }

    if (!builtin_command(argv)) {
        /* Not a builtin command, run argv as a file */
        if ((pid = Fork()) == 0) {
            /* Child Process */
            char *path[20];
            getPathVector(path);
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        if (!bg) {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                unix_error("waitfg: waitpid error");
            }
        } else {
            printf("%d %s", pid, cmdline);
        }
    }
    return;
}

/* Parse the command line and build the argv array */
int parseline(char *buf, char **argv) {
    char *delim; /* Points to first space delimiter */
    int argc; /* Argument Count */
    int bg; /* Background Job or not */

    buf[strlen(buf)-1] = ' '; /* Last 2 chars are '\n','\0'. Replace \n with ' ' */
    while (*buf && (*buf == ' ')) {
        buf++;
    }

    /* Build argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) { /* Get a pointer to the first occurence of ' ' (weve already removed training spaces */
        argv[argc++] = buf; /* buf points to the next word, that ends with a space. Delim points to that space */
        *delim = '\0'; /* Make word pointed to by buf and argv[argc] a NULL terminated string */
        buf = delim + 1; /* Point buf to the next character after '\0' */
        
        while (*buf && (*buf == ' ')) { /* Ignore Spaces, eventually buf will point to a character */
            buf++;
        }
    }

    argv[argc] = NULL; /* Null terminate argv */

    if (argc == 0) {
        return 1;
    }

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0) {
        argv[--argc] = NULL; /* Get rid of '&' once we know whether to run in bg or not */
    }

    return bg;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) {
    if (!strcmp(argv[0], "quit")) { /* Quit, terminate program */
        exit(0);
    }
    if (!strcmp(argv[0], "&")) {    /* Ignore Singleton */
        return 1;
    }
    return 0;   /* Not a builtin command */
}

int getPathVector(char **pathVector) {
    char pathString[MAXPATH] = "";
    char *pathTemp;
    if ((pathTemp = getenv("PATH")) != NULL) {
        strncpy(pathString, pathTemp);
    } else {
        return -1;
    }

    printf("%s\n", pathString);
    return 0;
}