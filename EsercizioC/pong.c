#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PING "/tmp/fifo_ping"
#define FIFO_PONG "/tmp/fifo_pong"
#define BUF_SIZE 256

int main(void) {

    int fd_read = open(FIFO_PING, O_RDONLY);  /* per inviare */
    int fd_write  = open(FIFO_PONG, O_WRONLY);  /* per ricevere */

    if (fd_write == -1 || fd_read == -1) {
        perror("Errore open");
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE];
    ssize_t n = read(fd_read, buffer, sizeof(buffer));

    if (n > 0)
        printf("[Reader] %s\n", buffer);
    else if (n == 0)
        printf("[Reader] Il writer ha chiuso senza inviare dati.\n");
    else
        perror("Errore read");

    const char *msg = "PONG";
    write(fd_write, msg, strlen(msg));

    return 0;
}
