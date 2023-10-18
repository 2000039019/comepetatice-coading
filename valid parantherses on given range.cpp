#include <bits/stdc++.h>
using namespace std;

struct info {
    int open, close, full;

    info(int x, int y, int z) : open(x), close(y), full(z) {}
};

vector<info*> seg;

info* merge(info* left, info* right) {
    int open = left->open + right->open - min(left->open, right->close);
    int close = left->close + right->close - min(left->open, right->close);
    int full = left->full + right->full + min(left->open, right->close);
    return new info(open, close, full);
}

void build(int ind, int low, int high, const string& s) {
    if (low == high) {
        seg[ind] = new info(s[low] == '(', s[low] == ')', 0);
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, s);
    build(2 * ind + 2, mid + 1, high, s);
    seg[ind]= merge(seg[2 * ind + 1], seg[2 * ind + 2]);
   
}

info* query(int ind, int low, int high, int l, int r) {
    if (r < low || l > high) {
        return new info(0, 0, 0); // No valid information for this range
    }
    if (low >= l && r >= high) {
        return seg[ind];
    }
    int mid = (low + high) / 2;
    info* left = query(2 * ind + 1, low, mid, l, r);
    info* right = query(2 * ind + 2, mid + 1, high, l, r);
    // if (!left) return right;
    // if (!right) return left;
    return merge(left, right);
}

int main() {
    string s;
    cin >> s;
    int n = s.size();
    seg.resize(4 * n);
    build(0, 0, n - 1, s);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--; // Adjust for zero-based indexing
        info* ans = query(0, 0, n - 1, l, r);
        cout << ans->full *2 << "\n";
    }
    return 0;
}
