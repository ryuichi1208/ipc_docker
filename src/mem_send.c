#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv)
{
        int   memid;
        char  *adr;

        if( argc <= 2) {
                fprintf(stderr, "Usage: memid string\n");
                exit(EXIT_FAILURE);
        }

        memid = atoi(argv[1]);

        if(( adr = (char *)shmat(memid, 0, 0)) == (void *)-1) {
                perror("shmat");
        } else {
                strcpy(adr, argv[2]);
                fprintf(stdout, "Operation completion.\n");
                if( shmdt(adr) == -1) {
                        perror("shmdt");
                }
        }
}
