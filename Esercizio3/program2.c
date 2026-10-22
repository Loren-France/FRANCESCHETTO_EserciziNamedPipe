#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>       /* per open() e O_WRONLY */
#include <sys/stat.h>    /* per mkfifo() */
#include <unistd.h>      /* per write() e close() */
#include <string.h>      /* per strlen() */
#include <errno.h>       /* per errno e EEXIST */
#include <sys/types.h>

#define FIFO_A_TO_B "/tmp/fifo_a_to_b"
#define FIFO_B_TO_A "/tmp/fifo_b_to_a"

int main(void) {

    int fd_read = open(FIFO_A_TO_B, O_RDONLY);
    int fd_write = open(FIFO_B_TO_A, O_WRONLY);

    if (fd_write == -1 || fd_read == -1) {
        perror("Errore open writer");
        exit(EXIT_FAILURE);
    }

    printf("[B] Reader e writer connessi.\n");

    char msg[100];

    do
    {
        int n = read(fd_read, msg, sizeof(msg) - 1);

        if(n > 0) {
            msg[n] = '\0';
        }

        if(strcmp(msg,"EXIT\n")==0)
            break;

        printf("%s",msg);

        fgets(msg,100,stdin);
        write(fd_write,msg,strlen(msg));

        if(strcmp(msg,"EXIT\n")==0)
            break;

    } while(1);

    printf("[B] Uscita...\n");

    close(fd_write);
    close(fd_read);

    unlink(FIFO_A_TO_B);
    unlink(FIFO_B_TO_A);

    return 0;
}
