#include <stdio.h>
#include <stdint.h>

int main() {
    unsigned int a, b, c, d;
    int prefix;
    uint32_t ip, mask, network, broadcast;
    uint32_t first, last;
    uint64_t hosts;
    int hostBits;

    // Input IP Address
    printf("Enter IP Address (e.g. 192.168.1.10): ");
    scanf("%u.%u.%u.%u", &a, &b, &c, &d);

    // Validate IP
    if (a > 255 || b > 255 || c > 255 || d > 255) {
        printf("Invalid IP Address!\n");
        return 0;
    }

    // Input Prefix Length
    printf("Enter Prefix Length (e.g. 24 for /24): ");
    scanf("%d", &prefix);

    // Validate Prefix
    if (prefix < 0 || prefix > 32) {
        printf("Invalid Prefix Length!\n");
        return 0;
    }

    // Convert dotted decimal to 32-bit integer
    ip = ((uint32_t)a << 24) |
         ((uint32_t)b << 16) |
         ((uint32_t)c << 8) |
         (uint32_t)d;

    // Calculate subnet mask from prefix
    if (prefix == 0)
        mask = 0;
    else
        mask = 0xFFFFFFFFU << (32 - prefix);

    // Calculate host bits
    hostBits = 32 - prefix;

    printf("\nAddress Type   : Classless (CIDR)\n");
    printf("Prefix Length  : /%d\n", prefix);

    // Calculate addresses
    network = ip & mask;
    broadcast = network | (~mask);

    // Calculate first and last host
    if (prefix == 31) {
        first = network;
        last = broadcast;
    }
    else if (prefix == 32) {
        first = network;
        last = network;
    }
    else {
        first = network + 1;
        last = broadcast - 1;
    }

    // Calculate usable hosts
    if (prefix >= 31)
        hosts = 0;
    else
        hosts = ((uint64_t)1 << hostBits) - 2;

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

    printf("\nHost Bits        : %d", hostBits);
    printf("\nUsable Hosts     : %llu\n",
           (unsigned long long)hosts);

    printf("\n========== DEFINITIONS ==========\n");

    printf("\n\nClassless Addressing");
    printf("\nClassless addressing is an IPv4 addressing method that does");
    printf("\nnot use fixed Class A, B, or C network boundaries.");
    printf("\nInstead, it uses a prefix length to determine the network");
    printf("\nand host portions of an IP address.");

    printf("\n\nCIDR");
    printf("\nCIDR stands for Classless Inter-Domain Routing.");
    printf("\nIt represents an IP address followed by a prefix length,");
    printf("\nsuch as 192.168.1.10/24.");
    printf("\nThe number after '/' represents the number of network bits.");

    printf("\n\nPrefix Length");
    printf("\nThe prefix length specifies how many bits belong to the network.");
    printf("\nFor example, /24 means 24 network bits and 8 host bits.");

    printf("\n\nSubnet Mask");
    printf("\nThe subnet mask is generated from the prefix length.");
    printf("\nBits with 1 represent the network portion.");
    printf("\nBits with 0 represent the host portion.");

    printf("\n\nNetwork Address");
    printf("\nThe first address in the subnet.");
    printf("\nIt is obtained by performing a bitwise AND between");
    printf("\nthe IP address and the subnet mask.");
    printf("\nIt identifies the entire network.");

    printf("\n\nBroadcast Address");
    printf("\nThe last address in the subnet.");
    printf("\nIt is obtained by setting all host bits to 1.");
    printf("\nPackets sent to this address are received by all devices");
    printf("\nin the subnet.");

    printf("\n\nFirst Host");
    printf("\nThe first usable IP address in the subnet.");
    printf("\nNormally, it is the Network Address + 1.");

    printf("\n\nLast Host");
    printf("\nThe last usable IP address in the subnet.");
    printf("\nNormally, it is the Broadcast Address - 1.");

    printf("\n\nHost Bits");
    printf("\nThe number of bits available for identifying hosts.");
    printf("\nIt is calculated as:");
    printf("\nHost Bits = 32 - Prefix Length");

    printf("\n\nUsable Hosts");
    printf("\nFor a normal IPv4 subnet, usable hosts are calculated as:");
    printf("\n2^(Host Bits) - 2");
    printf("\nWe subtract 2 because the first address is the Network");
    printf("\nAddress and the last address is the Broadcast Address.");

    printf("\n\nCIDR Example");
    printf("\nFor 192.168.1.10/26:");
    printf("\nPrefix Length = 26");
    printf("\nNetwork Bits  = 26");
    printf("\nHost Bits     = 6");
    printf("\nTotal Addresses = 2^6 = 64");
    printf("\nUsable Hosts    = 64 - 2 = 62");

    printf("\n");
    
    printf("\n================ CLASSLESS ADDRESSING TABLE ================\n");

    printf("+---------+--------------+-------------+----------------+\n");
    printf("| Prefix  | Network Bits | Host Bits   | Total Addresses|\n");
    printf("+---------+--------------+-------------+----------------+\n");
    printf("| /8      | 8            | 24          | 16,777,216     |\n");
    printf("| /16     | 16           | 16          | 65,536         |\n");
    printf("| /24     | 24           | 8           | 256            |\n");
    printf("| /25     | 25           | 7           | 128            |\n");
    printf("| /26     | 26           | 6           | 64             |\n");
    printf("| /27     | 27           | 5           | 32             |\n");
    printf("| /28     | 28           | 4           | 16             |\n");
    printf("| /29     | 29           | 3           | 8              |\n");
    printf("| /30     | 30           | 2           | 4              |\n");
    printf("+---------+--------------+-------------+----------------+\n");

    return 0;
}
