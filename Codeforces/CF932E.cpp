#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=5e3+10;
bool mem1;
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
ll n,k,s[N][N],fac[N],inv[N];
void init() {
    s[0][0]=1;
    for(int i=1;i<N;i++)
        for(int j=1;j<=i;j++) s[i][j]=(1ll*s[i-1][j]*j+s[i-1][j-1])%Mod;
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>k;
    ll ans=0,c=n;
    for(int i=1;i<=min(k,n);i++) 
        ans=(ans+s[k][i]*fac[i]%Mod*c%Mod*Pow(2,n-i))%Mod,
        c=c*(n-i)%Mod*Pow(i+1,Mod-2)%Mod;
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}