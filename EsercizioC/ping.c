#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*  Architettura con due FIFO per comunicazione bidirezionale:  */
/*                                                               */
/*   Processo A                          Processo B             */
/*   write -> /tmp/fifo_a_to_b -> read                          */
/*   read  <- /tmp/fifo_b_to_a <- write                         */

#define FIFO_PING "/tmp/fifo_ping"
#define FIFO_PONG "/tmp/fifo_pong"
#define BUF_SIZE 256

int main(void) {
    /* Processo A: crea entrambe le FIFO, poi le apre */
    mkfifo(FIFO_PING, 0666);
    mkfifo(FIFO_PONG, 0666);

    int fd_write = open(FIFO_PING, O_WRONLY);  /* per inviare */
    int fd_read  = open(FIFO_PONG, O_RDONLY);  /* per ricevere */

    const char *msg = "PING";
    write(fd_write, msg, strlen(msg));

    char buffer[BUF_SIZE];
    ssize_t n = read(fd_read, buffer, sizeof(buffer));

    if (n > 0)
        printf("[Reader] %s\n", buffer);
    else if (n == 0)
        printf("[Reader] Il writer ha chiuso senza inviare dati.\n");
    else
        perror("Errore read");

    close(fd_write);
    close(fd_read);

    if (unlink(FIFO_PING) == -1 && unlink(FIFO_PONG) == -1) {
        perror("Errore unlink");
    } else {
        printf("[Reader] FIFO rimossa dal filesystem.\n");
    }
    return 0;
}
