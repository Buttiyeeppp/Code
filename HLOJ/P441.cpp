#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
ll n,Mod,nfac[N];
ll Pow(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return sum;
}
int main() {
    cin>>n>>Mod;
    nfac[n-1]=n-1;
    for(ll i=n-2;i>=1;i--) nfac[i]=nfac[i+1]*i%Mod;
    ll ans=0;
    for(ll l=2;l<=n;l++) ans=(ans+nfac[n-l+1]*((l*(l-1)/2)%Mod)%Mod*Pow(n,n-l)%Mod)%Mod;
    printf("%lld",ans*n%Mod);
    return 0;
}