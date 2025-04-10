#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server, new_socket;
    struct sockaddr_in servaddr, clientaddr;
    socklen_t clen = sizeof(clientaddr);

    int row, col;
    int matrix1[10][10], matrix2[10][10], result[10][10];

    // Create socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(server, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(server, 5);
    printf("🔌 Server listening on port %d...\n", PORT);

    new_socket = accept(server, (struct sockaddr*)&clientaddr, &clen);
    printf("📡 Client connected!\n");

    // Receive row, col
    recv(new_socket, &row, sizeof(int), 0);
    recv(new_socket, &col, sizeof(int), 0);

    // Receive both matrices
    recv(new_socket, matrix1, sizeof(int) * row * col, 0);
    recv(new_socket, matrix2, sizeof(int) * row * col, 0);

    // Add matrices
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            result[i][j] = matrix1[i][j] + matrix2[i][j];

    // Send result
    send(new_socket, result, sizeof(int) * row * col, 0);
    printf("✅ Result sent to client.\n");

    close(new_socket);
    close(server);
    return 0;
}
