#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void shelly(void) {
    fprintf(stderr, "oh no!\n");
    system("/bin/sh");
    exit(1);
}

int leaker(long long addr) {
    printf("read %#llx bytes\n", addr);
    return 0;
}

int vuln(void) {
    char vbuf[100];

    printf("enter msg: ");
    fflush(stdout);

    int len = read(0, vbuf, 200);

    printf("msg: %s\n", vbuf);

    return len;
}

int main(void) {
    int len = vuln();
    leaker(len);
}
