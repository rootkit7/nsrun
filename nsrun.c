#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                       } while (0)

int main(int argc, char *argv[])
{
    int fd;

    int userid = getuid();
    int groupid = getgid();
    
    if (argc < 3) {
       fprintf(stderr, "%s /proc/PID/ns/net cmd args...\n", argv[0]);
       exit(EXIT_FAILURE);
    }

    if (setuid(0) == -1)            /* Become root */
        errExit("setuid");
    fd = open(argv[1], O_RDONLY);   /* Get file descriptor for namespace */
    if (fd == -1)
        errExit("open");

    if (unshare(CLONE_NEWNET) == -1)    /* Leave parents namespace */
        errExit("unshare");

    if (setns(fd, CLONE_NEWNET) == -1)  /* Join new namespace */
       errExit("setns");

    if (getuid() == 0) {
        /* process is running as root, drop privileges
          It does not change secondary groups! We assume it was executed as a setuid
          binary so we fall back to the callers uid.
          We check for the gid as a security measure.
         */
        if (setgid(groupid) != 0)
            errExit("setgid");
        if (setuid(userid) != 0)
            errExit("setuid");
    }
    execvp(argv[2], &argv[2]);    /* Execute a command in namespace */
    errExit("execvp");
}
