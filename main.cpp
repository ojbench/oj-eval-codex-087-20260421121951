#include <bits/stdc++.h>
using namespace std;

// Compute final position for the k-th ball efficiently
static inline long long final_position(int D, long long k) {
    long long pos = 1;
    for (int i = 0; i < D - 1; ++i) {
        if (k & 1LL) { // odd -> go left; toggle closed to open
            pos = pos * 2;
            k = (k + 1) >> 1;
        } else {       // even -> go right; toggle open to closed
            pos = pos * 2 + 1;
            k >>= 1;
        }
    }
    return pos;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D; long long n;
    if (!(cin >> D >> n)) return 0;

    long long last_pos = final_position(D, n);
    cout << last_pos << '\n';

    // Leaves occupy indices [2^{D-1}, 2^D - 1]
    long long P = 1LL << (D - 1);
    long long full = n / P;   // full cycles where each leaf gets one ball
    long long rem  = n % P;

    // After each full cycle, every leaf toggles once => parity full%2
    vector<int> state((size_t)P, (int)(full & 1LL));

    // Distribute the remainder balls; the k-th ball hits leaf at final_position(D, k)
    for (long long k = 1; k <= rem; ++k) {
        long long leaf = final_position(D, k);
        long long idx = leaf - P; // zero-based index left-to-right
        state[(size_t)idx] ^= 1;
    }

    for (long long i = 0; i < P; ++i) {
        if (i) cout << ' ';
        cout << state[(size_t)i];
    }
    cout << '\n';
    return 0;
}
