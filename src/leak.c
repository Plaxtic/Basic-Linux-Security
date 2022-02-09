#include <stdio.h>
#include <string.h>
#include <unistd.h>

void vuln(void) {
    char vbuf[100];

    int len;
    while (strcmp(vbuf, "q")) {

        printf("enter msg: ");
        fflush(stdout);

        // clear buffer
        memset(vbuf, 0, 100);

        // user input
        len = read(0, vbuf, 200)-1;
        printf("msg: %s", vbuf);

        // reverse
        printf("reversed: ");
        while (len--) putchar(vbuf[len]);
        puts("");
    }
}

int main(void) {

    // start reverser 
    vuln();
}
