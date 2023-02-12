#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,X;
long long z;
int gcd(int q,int p){
    if (q < p) swap(q, p);
    if (p == 0) return q;
    return gcd(p, q % p);
}
signed main(){
    scanf("%lld", &T);
    while(T--){
        scanf("%lld%lld", &X, &z);
        if (z % X)
            printf("-1\n");
        else{
            int k = z / X;
            int d = gcd(X * X, k);
            double dd = sqrt(d);
            d = dd;
            if (d * 1.0 != dd)
                printf("-1\n");
            else
                printf("%lld\n", k / d);
        }
    }
    return 0;
}