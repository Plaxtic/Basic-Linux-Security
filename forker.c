#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void no() {
    printf(">:(\n");
}

void echo() {
    char buf[16];
    char c;
    for (int i = 0;(c = getchar()) != '\n'; ++i)
        buf[i] = c, putchar(buf[i]);

    putchar('\n');
}

int main (int argc, char **argv) {

    // always up!
    int pid;
    while (1) {
        if (!(pid = fork()))
            while (1) 
                echo();
        else {
            wait(NULL);
            printf("child %d is gone! :(\n", pid);
        }
    }
}

