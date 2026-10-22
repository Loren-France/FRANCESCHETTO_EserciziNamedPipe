#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>       /* per open() e O_WRONLY */
#include <sys/stat.h>    /* per mkfifo() */
#include <unistd.h>      /* per write() e close() */
#include <string.h>      /* per strlen() */
#include <errno.h>       /* per errno e EEXIST */

#define FIFO_WEB "/tmp/fifo_web"
#define BUF_SIZE 256

int main(void) {

    int fd = open(FIFO_WEB, O_RDONLY);
    if (fd == -1) {
        perror("Errore open reader");
        exit(EXIT_FAILURE);
    }
    printf("[Server] Writer connesso. In attesa di messaggi...\n");

    char buf[BUF_SIZE];

    while (strcmp(buf, "QUIT\n") != 0) {
        read(fd, buf, BUF_SIZE);
        printf("Messaggio ricevuto: %s\n", buf);
    }

    printf("Ricevuto messaggio QUIT. Uscita...\n");

    close(fd);

    unlink(FIFO_WEB);

    return 0;
}
