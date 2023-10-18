#include <bits/stdc++.h>
using namespace std;
int n = 1000000;
vector<int> sieve(n + 1, 1);

void create() {
    for (int i = 2; i * i <= n; i++) {
        if (sieve[i] == 1) {
            for (int j = i * i; j <= n; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

vector<int> generate(int n) {
    vector<int> ds;
    for (int i = 2; i <= n; i++) {
        if (sieve[i] == 1) {
            ds.push_back(i);
        }
    }
    return ds;
}

int main() {
    create();
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        vector<int> primes = generate((int)sqrt(r));
        vector<int> dummt(r - l + 1, 1); // Use vector instead of an array

        for (auto pr : primes) {
            int firstm = (l / pr) * pr;
            if (firstm < l) {
                firstm += pr;
            }
            for (int j = max(firstm, pr * pr); j <= r; j += pr) {
                dummt[j - l] = 0;
            }
        }

        for (int i = l; i <= r; i++) {
            if (dummt[i - l] == 1) {
                cout << i << " ";
            }
        }
    }

    return 0;
}
