#include <bits/stdc++.h>
using namespace std;

vector<int> seg;

void build(int ind, int low, int high, int arr[]) {
    if (low == high) {
        seg[ind] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, arr);
    build(2 * ind + 2, mid + 1, high, arr);
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
}

void update(int ind, int low, int high, int i, int val) {
    if (high == low) {
        seg[ind] += val;
        return;
    }
    int mid = (low + high) / 2;
    if (i <= mid) {
        update(2 * ind + 1, low, mid, i, val);
    } else {
        update(2 * ind + 2, mid + 1, high, i, val); // Change 2*ind+1 to 2*ind+2 here
    }
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
}

int query(int ind, int low, int high, int l, int r) {
    if (r < low || l > high) {
        return 0;
    }
    if (low >= l && r >= high) {
        return seg[ind];
    }
    int mid = (low + high) / 2;
    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);
    return left + right;
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    int mx = -1;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }
    mx += 1;

    seg.resize(4 * mx);
    build(0, 0, mx - 1, arr);
    int count = 0;

    for (int i = 0; i < n; i++) {
        freq[arr[i]]--;
        update(0, 0, mx - 1, arr[i], -1);
        count += query(0, 0, mx - 1, 0, arr[i] - 1);
    }
    cout << count << "\n";

    return 0;
}
