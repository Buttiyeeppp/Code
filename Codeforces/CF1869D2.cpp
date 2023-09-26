#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 200005
#define maxlgn 40

int a[maxn], cnt1[maxlgn], cnt2[maxlgn], cnt3[maxlgn];

bool solve(void) {
    int n;
    cin >> n;
    int64_t v = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], v += a[i];
    memset(cnt1, 0, sizeof(cnt1)), memset(cnt2, 0, sizeof(cnt2)), memset(cnt3, 0, sizeof(cnt3));
    if (v % n) return false;
    v /= n;
    for (int i = 1; i <= n; i++) {
        int64_t p = v - a[i], q = 0;
        if (p == 0) continue;
        if (__builtin_popcount(p) == 1) {
            cnt3[(int)round(log2(p))]++;
            continue;
        }
        while (p + (1LL << q) < 0) q++;
        if (p + (1LL << q) == 0) {
            cnt2[q]++;
            continue;
        }
        while ((1LL << q) < p && __builtin_popcount(p + (1LL << q)) != 1) q++;
        p += 1 << q;
        if (__builtin_popcount(p) != 1) return false;
        cnt1[q]++, cnt1[(int)round(log2(p))]--;
    }
    for (int i = 0; i < maxlgn; i++) {
        while ((cnt1[i] + cnt2[i] - cnt3[i] > 0) && cnt2[i]) cnt2[i]--, cnt1[i]--, cnt1[i + 1]++;
        while ((cnt1[i] + cnt2[i] - cnt3[i] < 0) && cnt3[i]) cnt3[i]--, cnt1[i]++, cnt1[i + 1]--;
        if (cnt1[i] + cnt2[i] - cnt3[i]) return false;
    }
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