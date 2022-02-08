#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv) {
    long i, size, end;
    unsigned long squares[10];
    char input[20] = {0};

    // print intro
    printf("This binary contains two buffers: squares[10] and input[20]\n");
    printf("squares[10] contains %ld byte (unsigned long) square numbers from 0 to 9\n", sizeof(unsigned long));
    printf("input[20] (char) is used to take your input\n"); 
    printf("Both arrays are stored on the stack\n"); 
    printf("You will be allowed (once) to print out as much of squares[10] as you like\n");
    printf("If you print out more than 10, you will be able to read from the stack\n");
    printf("You will then be able to modify the contents of squares[10] as much as you like\n");
    printf("This will allow you to write to the stack\n");
    printf("Your task is to get a root shell\n");
    printf("As you can modfiy the stack, this should be easy?\n");
    printf("But this binary will have PIE, DEP, ASLR, a stack canary, and full RELRO enabled\n");
    printf("You should be able to find resources describing how to bypass all of these online\n");
    printf("It will be up to you to use the stack leak to bypass each layer of security\n");
    printf("Good luck!\n");

    // calculate squares up to 9 
    for (i = 0; i < 10; i++)
        squares[i] = i*i;

    // get size of stack to print
    while (1) {
        printf("\nHow much of squares[10] would you like to print? ");
        fflush(stdout);

        // read size
        end        = read(0, input, 19);
        input[end] = 0;
        size       = strtol(input, NULL, 10);

        // clean stdin
        if (end == 19) while (getchar() != '\n');

        // too much will give the wrong kind of segmentation fault
        if (size < 500) break;

        printf("Ok, that's too much (below 500 pls)\n");
    }

    // print num 'size' addresses from stack
    printf("\nStack up to squares[%ld]:\n", size-1);
    for (i = 0; i < size; ++i)
        printf("\tsquares[%ld] = 0x%016lx\n", i, squares[i]);    

    // modify stack 
    i = 0;
    puts("\nModify squares[10] (q to exit)");
    while (1) {
        printf("\tsquares[%ld] = 0x", i);
        fflush(stdout);

        // read from stdin 
        memset(input, 0, 19);
        end        = read(0, input, 19);
        input[end] = 0;

        // clean stdin
        if (end == 19) while (getchar() != '\n');

        // stop if q
        if (input[0] == 'q') break;

        // convert to address
        squares[i++] = strtoul(input, NULL, 16);
    }

    // print modified stack 
    int newsiz = i > size ? i : size;
    puts("\nStack now contains:");
    for (i = 0; i < newsiz ; i++)
        printf("\tsquares[%ld] = 0x%016lx\n", i, squares[i]);

    return 0;
}

