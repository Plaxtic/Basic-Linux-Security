#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int echo_server(int client) {
    char buf[40];

    // send all output to client
    dup2(client, 0);
    dup2(client, 1);
    dup2(client, 2);

    // get client input
    int i, c;
    do { 
        for (i = c = 0; (c = getchar()) != '\n' && c != EOF; i++) {
            buf[i] = c;
        }

        // echo input
        write(1,  buf, i);

    } while (strncmp(buf, "exit", 4));

    return 0;
}

int main(int argc, char **argv) {
    struct sockaddr_in servfo;
    struct sockaddr clinfo;
    int client;


    // fetch arguments
    if (argc < 2) {
        printf("Usage: %s [ip] [port:3356]\n", argv[0]);
        return 1;
    }

    // open socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    // fill in socket details
    servfo.sin_family      = AF_INET;
    servfo.sin_addr.s_addr = inet_addr(argv[1]);
    servfo.sin_port        = argc < 3 ?  htons(3356) : htons(atoi(argv[2]));

    // bind to socket
    if (bind(sock, (struct sockaddr *)&servfo, sizeof servfo) < 0) {
        perror("bind");
        return 1;
    }

    // set option to allow reuse of port number
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt SO_REUSEADDR");
        return 1;
    }

    // set socket to listening state 
    if (listen(sock, 1) < 0) {
        perror("Listening failed");
        return 1;
    }

    // server forking loop
    socklen_t addr_size = sizeof clinfo;
    while (1) {

        // wait for client to connect
        client = accept(sock, &clinfo, &addr_size);
        if (client < 0) {
            perror("Client Rejected");
            break;
        }

        // print client ip address
        printf("Incoming connection %s\n", inet_ntoa(((struct sockaddr_in *)&clinfo)->sin_addr));

        // fork!
        int pid = fork();
        if (!pid) {

            // start echo server
            echo_server(client); 

            close(client);
            return 0;
        }
        else {
            printf("handle client in child %d\n", pid);
            int sig = wait(NULL);
            printf("client child exited with status %d\n", sig); 
            close(client);
        }
    }
    puts("server error!\n");

    // close socket and exit
    close(sock);
    return 0;
}

