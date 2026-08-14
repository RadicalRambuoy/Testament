#include <iostream>
#include <vector>
using namespace std;

bool isPowerOfTwo(int x) {
    return x && ((x & (x - 1)) == 0);
}

int main() {
    int m;
    cout << "Enter number of data bits: ";
    if (!(cin >> m) || m <= 0) {
        cerr << "Invalid number of data bits.\n";
        return 1;
    }

    vector<int> data(m);
    cout << "Enter " << m << " data bits (0 or 1) separated by spaces: ";
    for (int i = 0; i < m; ++i) {
        cin >> data[i];
        data[i] = data[i] & 1; // ensure binary (mod 2)
    }

    // Calculate number of parity bits r such that 2^r >= m + r + 1
    int r = 0;
    while ((1 << r) < (m + r + 1)) ++r;
    int total = m + r;

    cout << "\nParity bits required: " << r << " (total code length " << total << ")\n";

    // 1-based indexing for positions
    vector<int> code(total + 1, 0);

    // Place data bits into non-parity positions
    int dataIndex = 0;
    for (int pos = 1; pos <= total; ++pos) {
        if (!isPowerOfTwo(pos)) {
            code[pos] = data[dataIndex++];
        }
    }

    // Calculate parity bits and show which positions contribute
    for (int i = 0; i < r; ++i) {
        int p = 1 << i; // parity position
        int sum = 0;
        cout << "\nParity bit at position " << p << " covers positions: ";
        bool first = true;
        for (int pos = 1; pos <= total; ++pos) {
            if (pos & p) {
                if (!first) cout << ", ";
                cout << pos << "(" << code[pos] << ")";
                first = false;
                sum += code[pos];
            }
        }
        int parity = sum % 2;
        code[p] = parity; // set parity bit
        cout << " -> parity = " << parity << '\n';
    }

    // Output final Hamming code (positions and bits)
    cout << "\nHamming Code (position:bit):\n";
    for (int pos = 1; pos <= total; ++pos) {
        cout << pos << ":" << code[pos];
        if (pos < total) cout << " ";
    }
    cout << "\n\nHamming Code sequence: ";
    for (int pos = 1; pos <= total; ++pos) cout << code[pos] << " ";
    cout << "\n";

    return 0;
}