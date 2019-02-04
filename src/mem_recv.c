#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

 int main(int argc, char **argv)
 {
        int  memid;
        char *adr;

        if((memid = shmget(IPC_PRIVATE, 512, IPC_CREAT|0666)) == -1){
                perror("shmget");
                exit(-1);
        }

        printf("Share Memory ID = %d\n",memid);

        if(( adr = (char *)shmat(memid, NULL, 0)) == (void *)-1){
                perror("shmat");
        } else {
                strcpy(adr,"Initial");
                while(1){
                        printf("%s\n",adr);

                        if (strcmp(adr, "end") == 0) {
                                break;
                        }
                        sleep(5);
                }

                if(shmdt(adr) == -1) {
                        perror("shmdt");
                }
        }

        if(shmctl(memid, IPC_RMID, 0) == -1){
                perror("shmctl");
                exit(EXIT_FAILURE);
        }

        return 0;
}
