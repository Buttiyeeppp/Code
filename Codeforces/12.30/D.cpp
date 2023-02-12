#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
int n,q,t;
ll v[N];
int main() {
    scanf("%d",&n);
    ll s=0;
    for(int i=1;i<=n;i++) {
        scanf("%lld",&v[i]);
        v[i]+=v[i-1];
        s=max(s,(v[i]+i-1)/i);
    }
    scanf("%d",&q);
    while(q--) {
        scanf("%d",&t);
        ll ans=(v[n]+t-1)/t;
        printf("%lld\n",(t<s|ans>n)?-1:ans);
    }
    return 0;
}