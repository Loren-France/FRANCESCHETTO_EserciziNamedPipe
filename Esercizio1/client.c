#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>       /* per open() e O_WRONLY */
#include <sys/stat.h>    /* per mkfifo() */
#include <unistd.h>      /* per write() e close() */
#include <string.h>      /* per strlen() */
#include <errno.h>       /* per errno e EEXIST */

#define FIFO_WEB "/tmp/fifo_web"

int main(void) {

    mkfifo(FIFO_WEB, 0666);

    int fd = open(FIFO_WEB, O_WRONLY);
    if (fd == -1) {
        perror("Errore open writer");
        exit(EXIT_FAILURE);
    }

    printf("[Client] Reader connesso.\n");

    printf("[Client] Inserire il messaggio: \n");
    char msg[100];

    fgets(msg, 100, stdin);
    write(fd, msg, strlen(msg));

    close(fd);

    return 0;
}
