#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 200005
#define maxlgn 40

int a[maxn], cnt[maxlgn];

bool solve(void) {
    int n;
    cin >> n;
    int64_t v = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], v += a[i];
    memset(cnt, 0, sizeof(cnt));
    if (v % n) return false;
    v /= n;
    for (int i = 1; i <= n; i++) {
        int64_t p = v - a[i], q = 0;
        if (p == 0) continue;
        while (p + (1LL << q) <= 0) q++;
        while ((1LL << q) < p && __builtin_popcount(p + (1LL << q)) != 1) q++;
        p += 1 << q;
        if (__builtin_popcount(p) != 1) return false;  
        cnt[q]++, cnt[(int)round(log2(p))]--;
    }
    for (int i = 0; i < maxlgn; i++)
        if (cnt[i]) return false;
    return true;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "Yes" : "No") << endl;

    return 0;
}