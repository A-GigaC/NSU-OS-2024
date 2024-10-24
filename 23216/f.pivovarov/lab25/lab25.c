#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void closePipe(const int pipeFDs[2]);

int main() {
    // Opens pipe
    printf("Opens pipe");
    int pipeFDs[2];
    if (pipe(pipeFDs) == -1) {
        perror("Troubles with pipe");
        exit(EXIT_FAILURE);
    }
    
    // Forks the current process
    printf("Try to fork()\n");
    pid_t process_id = fork();

    switch (process_id) {
        case -1:
            perror("Can't fork()");
            closePipe(pipeFDs);
            exit(EXIT_FAILURE);
        case 0:
            // Forked process code
            printf("Inside forked\n");
            char *text = "aBoba123";
            if (write(pipeFDs[1], text, 8) != 8) {
                perror("Cannot write text correctly");
                closePipe(pipeFDs);
                exit(EXIT_FAILURE);
            }
            closePipe(pipeFDs);
            exit(EXIT_SUCCESS);
        default:
            // Parent process code
            char buffer[255];
            int readedBytes;
            if ((readedBytes = read(pipeFDs[0], buffer, 255)) == -1) {
                perror("Troubles in read");
                closePipe(pipeFDs);
                exit(EXIT_FAILURE);
            }
            
            for (int i = 0; i < readedBytes; i++) {
                buffer[i] = (char)toupper(buffer[i]);
            }
            printf("from child: %s", buffer);

            closePipe(pipeFDs);
            exit(EXIT_SUCCESS);
        }
}

void closePipe(const int pipeFDs[2]) {
    close(pipeFDs[0]);
    close(pipeFDs[1]);
}