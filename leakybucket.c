#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NOF_PACKETS 10  // Number of packets

// Generates random packet sizes (multiples of 10)
int getRandomSize(int max) {
    int size = (rand() % max) + 1;  // Ensures size is never 0
    return size * 10;
}

int main() {
    int packet[NOF_PACKETS], i, bucketSize, outputRate, remaining = 0;

    // Generate and display packet sizes
    printf("Generated Packets:\n");
    for (i = 0; i < NOF_PACKETS; i++) {
        packet[i] = getRandomSize(5);  // Random sizes between 10-50 bytes
        printf("Packet[%d]: %d bytes\n", i + 1, packet[i]);
    }

    // User input: output rate and bucket size
    printf("\nEnter Output Rate: ");
    scanf("%d", &outputRate);
    printf("Enter Bucket Size: ");
    scanf("%d", &bucketSize);

    // Process packets
    for (i = 0; i < NOF_PACKETS; i++) {
        // Check if the packet is too large
        if (packet[i] > bucketSize) {
            printf("\nPacket[%d] (%d bytes) exceeds bucket size (%d) - REJECTED!", i + 1, packet[i], bucketSize);
            continue;
        }

        // Check if bucket overflows
        if (remaining + packet[i] > bucketSize) {
            printf("\nBucket full! Packet[%d] (%d bytes) - REJECTED!", i + 1, packet[i]);
            continue;
        }

        // Accept packet into the bucket
        remaining += packet[i];
        printf("\nPacket[%d]: %d bytes added to bucket. Remaining: %d bytes", i + 1, packet[i], remaining);

        // Simulate transmission
        while (remaining > 0) {
            sleep(1);  // Simulating delay
            
            int sent;
            if (remaining < outputRate) {
                sent = remaining;
            } else {
                sent = outputRate;
            }
            
            remaining -= sent;
            printf("\nTransmitted: %d bytes | Remaining: %d bytes", sent, remaining);
        }
    }

    printf("\n\nAll packets processed!\n");
    return 0;
}
