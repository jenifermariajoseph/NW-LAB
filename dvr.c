#include <stdio.h>

#define MAX 20

int costMatrix[MAX][MAX], n;

struct Router {
    int distance[MAX];
    int nextHop[MAX];
} node[MAX];

void readCostMatrix() {
    printf("\nEnter cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &costMatrix[i][j]);
            node[i].distance[j] = costMatrix[i][j];  // Initialize distance
            node[i].nextHop[j] = j;  // Initially, direct connection
        }
        costMatrix[i][i] = 0; // Self-distance is always 0
    }
}

void calcRoutingTable() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                int newDist = costMatrix[i][k] + node[k].distance[j];
                if (node[i].distance[j] > newDist) {
                    node[i].distance[j] = newDist;
                    node[i].nextHop[j] = k;
                }
            }
        }
    }
}

void displayRoutes() {
    for (int i = 0; i < n; i++) {
        printf("\nRouter %d:\n", i + 1);
        for (int j = 0; j < n; j++) {
            printf("To Node %d via %d - Distance: %d\n", j + 1, node[i].nextHop[j] + 1, node[i].distance[j]);
        }
    }
}

int main() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    readCostMatrix();
    calcRoutingTable();
    displayRoutes();

    return 0;
}
