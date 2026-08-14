#include <stdio.h>
#include <stdint.h>

int main() {
    unsigned int a, b, c, d;
    uint32_t ip, mask, network, broadcast;
    unsigned int first, last, hosts;
    int hostBits;

    // Input IP Address
    printf("Enter IP Address (e.g. 192.168.1.10): ");
    scanf("%u.%u.%u.%u", &a, &b, &c, &d);

    // Validate IP
    if (a > 255 || b > 255 || c > 255 || d > 255) {
        printf("Invalid IP Address!\n");
        return 0;
    }

    // Convert dotted decimal to 32-bit integer
    ip = (a << 24) | (b << 16) | (c << 8) | d;

    // Determine IP Class and Default Mask
    if (a >= 1 && a <= 126) {
        printf("\nIP Class      : A\n");
        mask = 0xFF000000;      // 255.0.0.0
        hostBits = 24;
    }
    else if (a == 127) {
        printf("\n127.x.x.x is reserved for Loopback.\n");
        return 0;
    }
    else if (a >= 128 && a <= 191) {
        printf("\nIP Class      : B\n");
        mask = 0xFFFF0000;      // 255.255.0.0
        hostBits = 16;
    }
    else if (a >= 192 && a <= 223) {
        printf("\nIP Class      : C\n");
        mask = 0xFFFFFF00;      // 255.255.255.0
        hostBits = 8;
    }
    else {
    printf("\nInvalid or reserved IP address.\n");
    return 0;
    }

    // Calculate addresses
    network = ip & mask;
    broadcast = network | (~mask);

    first = network + 1;
    last = broadcast - 1;
    hosts = (1U << hostBits) - 2;

    // Display Results
    printf("\nSubnet Mask      : %u.%u.%u.%u",
           (mask >> 24) & 255,
           (mask >> 16) & 255,
           (mask >> 8) & 255,
           mask & 255);

    printf("\nNetwork Address  : %u.%u.%u.%u",
           (network >> 24) & 255,
           (network >> 16) & 255,
           (network >> 8) & 255,
           network & 255);

    printf("\nBroadcast Address: %u.%u.%u.%u",
           (broadcast >> 24) & 255,
           (broadcast >> 16) & 255,
           (broadcast >> 8) & 255,
           broadcast & 255);

    printf("\nFirst Host       : %u.%u.%u.%u",
           (first >> 24) & 255,
           (first >> 16) & 255,
           (first >> 8) & 255,
           first & 255);

    printf("\nLast Host        : %u.%u.%u.%u",
           (last >> 24) & 255,
           (last >> 16) & 255,
           (last >> 8) & 255,
           last & 255);

    printf("\nUsable Hosts     : %u\n", hosts);

    printf("\n========== DEFINITIONS ==========\n");
   
    printf("\n\nSubnetting");
    printf("\nSubnetting is the process of dividing a large network into smaller");
    printf("\nlogical networks called subnets.");
    printf("\nIt improves network organization, reduces broadcast traffic,");
    printf("\nand makes IP address allocation more efficient.");
   
    printf("\n\nClassful Addressing");
    printf("\nClassful addressing is an IPv4 addressing method that divides");
    printf("\nIP addresses into fixed classes (A, B, C, D, and E).");
    printf("\nEach class has a predefined default subnet mask.");
    printf("\nThe IP class is determined by the first octet of the address.");

    printf("\nIP Class");
    printf("\nDetermines the default subnet mask based on the first octet.");

    printf("\n\nSubnet Mask");
    printf("\nSeparates the Network ID from the Host ID.");
    printf("\nBits with 1 represent the network portion.");
    printf("\nBits with 0 represent the host portion.");

    printf("\n\nNetwork Address");
    printf("\nThe first address in the network.");
    printf("\nIt identifies the entire network and cannot be assigned to a device.");

    printf("\n\nBroadcast Address");
    printf("\nThe last address in the network.");
    printf("\nPackets sent to this address are received by every device in the network.");
    printf("\nIt cannot be assigned to a device.");

    printf("\n\nFirst Host");
    printf("\nThe first usable IP address for a device.");
    printf("\nIt is the Network Address + 1.");

    printf("\n\nLast Host");
    printf("\nThe last usable IP address for a device.");
    printf("\nIt is the Broadcast Address - 1.");

    printf("\n\nUsable Hosts");
    printf("\nCalculated as 2^(Host Bits) - 2.");
    printf("\nWe subtract 2 because:");
    printf("\n1. The first address is reserved as the Network Address.");
    printf("\n2. The last address is reserved as the Broadcast Address.");
    printf("\nNeither of these can be assigned to hosts.");
   
    printf("\n\nLoopback Address");
    printf("\nThe 127.0.0.0/8 address range is reserved for loopback.");
    printf("\nIt is used by a computer to communicate with itself for testing and diagnostics.");
    printf("\nThe most common loopback address is 127.0.0.1, also known as 'localhost'.");
    printf("\nPackets sent to a loopback address never leave the computer.");

    printf("\n");
   
    printf("\n================ CLASSFUL ADDRESSING TABLE ================\n");
   
    printf("+-------+------------------+--------------------+--------------+-----------+\n");
    printf("| Class | First Octet      | Default Mask       | Network Bits | Host Bits |\n");
    printf("+-------+------------------+--------------------+--------------+-----------+\n");
    printf("| A     | 1 - 126          | 255.0.0.0 (/8)     | 8            | 24        |\n");
    printf("| B     | 128 - 191        | 255.255.0.0 (/16) | 16           | 16        |\n");
    printf("| C     | 192 - 223        | 255.255.255.0     | 24           | 8         |\n");
    printf("|       |                  | (/24)             |              |           |\n");
    printf("+-------+------------------+--------------------+--------------+-----------+\n");

    return 0;
}