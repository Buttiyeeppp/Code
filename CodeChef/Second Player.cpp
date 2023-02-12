#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=1e9+7;
const int N=5e5+10;
int n,a[N];
ll dp[N],fac[N],inv[N];
bool cmp(int x,int y){return x>y;}
ll Mul(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod;
        y>>=1;
    }
    return sum;
}
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Mul(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    if(y==0||x==y) return 1;
    return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1,cmp);
    for(int i=2;i<=n;i++) {
        ll P=Mul(C(i,2),Mod-2);
        dp[i]=(P*a[i]%Mod+(1-P+Mod)*dp[i-1]%Mod)%Mod;
    }
    cout<<dp[n]<<endl;
}
int main() {
    init();
    int T; cin>>T;
    while(T--) solve();
    return 0;
}