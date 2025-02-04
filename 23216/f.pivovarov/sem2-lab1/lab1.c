#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *printTenStrings();

int main() {
    int code;
    pthread_t thread;
    if ((code = pthread_create(&thread, NULL, printTenStrings, NULL)) != 0) {
        char buf[256];
        strerror_r(code, buf, sizeof(buf));
        fprintf(stderr, "At creating thread: %s\n", buf);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i <= 10; i++) {
        printf("Print's number at source thread %d\n", i);
    }

    exit(EXIT_SUCCESS);
}

void *printTenStrings() {
    for (int i = 1; i <= 10; i++) {
        printf("Print's number %d\n", i);
    }

    return NULL;
}
