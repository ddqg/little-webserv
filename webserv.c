#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failed to create socket :(");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to bind socket :(");
        return 1;
    }

    // wakm is so sexy omagad

    if (listen(server_socket, 5) == -1) {
        perror("Failed to listen on sockettt :(");
        return 1;
    }

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            perror("Failed to accept connection xd");
            continue;
        }

        char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 34\r\n\r\nSalut a tous c'est LaSalle";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
    }

    return 0;
}
