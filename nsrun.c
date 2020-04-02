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

    //int userid = 1000;
    //int groupid = 100;

    int userid = getuid();
    int groupid = getgid();
    //fprintf(stderr, "%d", ruid);
    
    if (argc < 3) {
       fprintf(stderr, "%s /proc/PID/ns/FILE cmd args...\n", argv[0]);
       exit(EXIT_FAILURE);
    }

    if (setuid(0) == -1)     // Become root
        errExit("setuid");   // you can set it at run time also
    fd = open(argv[1], O_RDONLY); /* Get file descriptor for namespace */
    if (fd == -1)
        errExit("open");

    if (unshare(CLONE_NEWNET) == -1)
            errExit("unshare");

    if (setns(fd, CLONE_NEWNET) == -1)       /* Join that namespace */
               errExit("setns");




    if (getuid() == 0) {    
        /* process is running as root, drop privileges */
        if (setgid(groupid) != 0)
            errExit("setgid");
        if (setuid(userid) != 0)
            errExit("setuid");
    }
    execvp(argv[2], &argv[2]);    /* Execute a command in namespace */
    errExit("execvp");
}
