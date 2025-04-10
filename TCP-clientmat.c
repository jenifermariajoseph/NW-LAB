#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int client;
    struct sockaddr_in servaddr;
    socklen_t slen = sizeof(servaddr);

    int row, col;
    int matrix1[10][10], matrix2[10][10], result[10][10];

    // Create socket
    client = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Connect
    connect(client, (struct sockaddr*)&servaddr, slen);
    printf("✅ Connected to server.\n");

    // Input matrices
    printf("🔢 Enter number of rows and columns: ");
    scanf("%d %d", &row, &col);

    printf("📝 Enter elements of Matrix 1:\n");
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            scanf("%d", &matrix1[i][j]);

    printf("📝 Enter elements of Matrix 2:\n");
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            scanf("%d", &matrix2[i][j]);

    // Send row and col
    send(client, &row, sizeof(int), 0);
    send(client, &col, sizeof(int), 0);

    // Send both matrices
    send(client, matrix1, sizeof(int) * row * col, 0);
    send(client, matrix2, sizeof(int) * row * col, 0);

    // Receive result matrix
    recv(client, result, sizeof(int) * row * col, 0);

    // Display result
    printf("\n📥 Result (Matrix1 + Matrix2):\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            printf("%d ", result[i][j]);
        printf("\n");
    }

    close(client);
    return 0;
}
