#include "csapp.h"
#include <unistd.h>

#define MAXARGS 128
#define MAXPATH 1024
#define MAXJOBS 5

#define RUNNING 1
#define STOPPED 0

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
int getPathVector(char **pathVector, char *pathBuffer);
void printJobs();
int getFinishedJob(int printOutPut);
void updateJobs();
void handleSignal(int signum);
void restartJob(int id, int foreGround);

int totalJobs;
int jobc;
int jobIDs[MAXJOBS];
int jobPGIDs[MAXJOBS];
int jobStatuses[MAXJOBS];

int main(int argc, char const *argv[])
{
    char cmdline[MAXLINE]; /* Commandline buffer */
    totalJobs = 0;
    jobc = 0;

    while(1) {
        /* Register Signals */
        Signal(SIGINT, handleSignal);
        Signal(SIGTSTP, handleSignal);

        /* Check For Finished Jobs */
        getFinishedJob(1);

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

        /* Check the number of jobs first */
        if (jobc >= MAXJOBS) {
            printf("Maximum number of jobs reached\n");
            return;
        }

        if ((pid = Fork()) == 0) {
            /* Child Process */
            char pathBuffer[MAXPATH];
            char *pathVector[20];
            int i = 0;
            
            execve(argv[0], argv, environ); /* Check current directory */

            getPathVector(pathVector, pathBuffer); /* Get PATH env if not in current directory*/

            while(1) {
                if (pathVector[i] == NULL) {
                    break;
                }
                char fullPath[MAXPATH] = "\0"; 
                strcat(fullPath, pathVector[i++]);
                strcat(fullPath, "/");
                strcat(fullPath, argv[0]);
                //printf("Checking in path: %s\n", fullPath);
                int isValidCOmmand = (execve(fullPath, argv, environ) < 0);
            }
            
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }

        /* Job Management */
        setpgid(pid, pid);

        jobStatuses[jobc] = RUNNING;
        jobIDs[jobc] = ++totalJobs;
        jobPGIDs[jobc++] = pid;

        if (!bg) {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                unix_error("waitfg: waitpid error");
            }

            jobc--;
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
    if (!strcmp(argv[0], "jobs")) { /* List all jobs */
        updateJobs();
        printJobs();
        return 1;
    }
    if (!strcmp(argv[0], "bg")) {
        if(argv[1] == NULL) {
            printf("Invalid argument to bg\n");
        } else {
            restartJob(atoi(argv[1]), 0);
        }
        return 1;
    }
    if (!strcmp(argv[0], "fg")) {
        if(argv[1] == NULL) {
            printf("Invalid argument to fg\n");
        } else {
            restartJob(atoi(argv[1]), 1);
        }
        return 1;
    }
    if (!strcmp(argv[0], "&")) {    /* Ignore Singleton */
        return 1;
    }
    return 0;   /* Not a builtin command */
}

int getPathVector(char **pathVector, char *pathBuffer) {
    char *pathTemp, *delim;
    int pathc = 0;
    
    if ((pathTemp = getenv("PATH")) != NULL) {
        strcpy(pathBuffer, pathTemp);
    } else {
        return -1;
    }

    //printf("%s\n", pathBuffer);

    while((delim = strchr(pathBuffer, ':'))) {
        pathVector[pathc++] = pathBuffer;
        *delim = '\0';
        pathBuffer = delim + 1;
    }

    pathVector[pathc] = NULL;

    return 0;
}

void printJobs() {
    if (jobc == 0) {
        printf("No Active Jobs\n");
        return;
    }
    printf("####### Active Jobs #######\n");
    for(int i = 0; i < jobc; i++) {
        if (jobStatuses[i] == STOPPED) {
            printf("Job ID: %d, Job Group: %d [Stopped]\n", jobIDs[i], jobPGIDs[i]);
        } else if (jobStatuses[i] == RUNNING) {
            printf("Job ID: %d, Job Group: %d [Running]\n", jobIDs[i], jobPGIDs[i]);
        }
        
    }
    printf("###########################\n");
}

int getFinishedJob(int printOutPut) {
    int status;
    pid_t terminatedPID = waitpid(-1, &status, WNOHANG | WUNTRACED);

    if (terminatedPID > 0) {
        /* PID Found; Clean Up Job */
        for(int i = 0; i < jobc; i++) {
            if (terminatedPID == jobPGIDs[i]) {
                /* Output Job Information */
                if (WIFEXITED(status)) {
                    if(printOutPut)
                        printf("Job %d exited: status %d\n", jobIDs[i], WEXITSTATUS(status));
                }  else if (WIFSIGNALED(status)) {
                    if(printOutPut)
                        printf("Job %d terminated by signal: [%d] %s\n", jobIDs[i], WTERMSIG(status), strsignal(WTERMSIG(status)));
                } else if (WIFSTOPPED(status)) {
                    if(printOutPut)
                        printf("Job %d was stopped by signal: [%d] %s\n", jobIDs[i], WSTOPSIG(status), strsignal(WSTOPSIG(status)));
                    jobStatuses[i] = STOPPED;
                    /* Job may be restarted, no need to Remove */
                    return 1;
                }

                /* Remove Job From List */
                for (int j = i+1; j < jobc; j++) {
                    jobPGIDs[j-1] = jobPGIDs[j];
                    jobIDs[j-1] = jobIDs[j];
                    jobStatuses[j-1] = jobStatuses[j];
                }

                jobc--;

                return 1;
            }
        }
        return -1;
    } 

    if (errno == 10 || terminatedPID == 0) {
        /* No Finished Child Processes */
        return 0;
    }

    unix_error("waitfg: waitpid error");

    return -1;
}

void updateJobs() {
    while (getFinishedJob(0) > 0){}
}

void handleSignal(int signum) {
    switch(signum) {
        case SIGINT:
        case SIGTSTP:
            for(int i = 0; i < jobc; i++) {
                //printf("Sending %s to child %d\n", strsignal(signum), jobPGIDs[i]);
                Kill(jobPGIDs[i], signum);
            }
            break;
        default:
            return;
    }
    return;
}

void restartJob(int id, int foreGround) {
    pid_t pid = -1;
    int jobIndex = -1;

    //printf("Finding %d and restarting\n", id);

    /* Check PIDs */
    for (int i = 0; i < jobc; i++) {
        if(jobPGIDs[i] == id) {
            pid = jobPGIDs[i];
            jobIndex = i;
        }
    }
    /* Check Job IDs */
    for (int i = 0; i < jobc; i++) {
        if(jobIDs[i] == id) {
            pid = jobPGIDs[i];
            jobIndex = i;
        }
    }

    if (pid == -1) {
        printf("Job ID or Process ID is invalid\n");
        return;
    }

    Kill(pid, SIGCONT);
    jobStatuses[jobIndex] = RUNNING;

    if(foreGround) {
        printf("waiting\n");
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            unix_error("waitfg: waitpid error");
        }

        printf("Job Completed in Foreground\n");

        jobc--;
    } 
}