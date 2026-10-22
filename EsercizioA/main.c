#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/fifo_test"

int main(void) {
    /* Crea la FIFO. Se esiste gia', non e' un errore. */
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno != EEXIST) {
            perror("Errore mkfifo");
            exit(EXIT_FAILURE);
        }
        /* errno == EEXIST: la FIFO c'e' gia', va bene cosi' */
    }

    printf("FIFO creata con successo: %s\n", FIFO_PATH);

    sleep(10);

    unlink(FIFO_PATH);
    return 0;
}
