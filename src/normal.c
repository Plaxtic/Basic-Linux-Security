#include <stdio.h>
#include <unistd.h>

int leaker(long long nbytes, long long number) {
    printf("read %#llx bytes %lld ;)\n", nbytes, number);
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
    leaker(len, 1337);
}
