#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define Mod 1000000007
#define N 1000010
struct Mat {
    ll a[5][5];
    Mat() { memset(a, 0, sizeof(a)); }
    Mat operator*(const Mat& b) const {
        Mat res;
        for (int i = 1; i <= 2; i++)
            for (int j = 1; j <= 2; j++)
                for (int k = 1; k <= 2; k++) res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j] % Mod) % Mod;
        return res;
    }
} A, B, ans;
Mat mul(Mat P, ll x) {
    Mat res;
    // res.a[1][1] = res.a[2][1] = res.a[2][2] = 1;
    res.a[1][1] = res.a[2][2] = 1;
    while (x) {
        if (x & 1) res = res * P;
        P = P * P;
        x >>= 1;
    }
    return res;
}
int main() {
    ll n = 0, m = 0, a, b, c, d;
    char q[N], p[N];
    scanf("%s%s", q + 1, p + 1);
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    int l1 = strlen(q + 1), l2 = strlen(p + 1);
    for (int i = 1; i <= l2; i++) m = (m * 10 + p[i] - '0') % (a == 1 ? Mod : Mod - 1);
    ans.a[1][1] = ans.a[1][2] = 1;
    A.a[1][1] = a, A.a[2][1] = b, A.a[2][2] = 1;
    B.a[1][1] = c, B.a[2][1] = d, B.a[2][2] = 1;
    Mat C;
    C = mul(A, m - 1);
    C = C * B;
    for (int i = 1; i <= l1; i++) n = (n * 10 + q[i] - '0') % (C.a[1][1] == 1 ? Mod : Mod - 1);
    C = mul(C, n - 1);
    C = C * mul(A, m - 1);
    ans = ans * C;
    printf("%lld", ans.a[1][1]);
    return 0;
}