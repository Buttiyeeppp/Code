#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=1.5e7+10;
bool mem1;
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
ll fac[N],inv[N],powk[N],inv3[N];
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%Mod;
    ll Inv=inv[3]*fac[2]%Mod;
    inv3[0]=1;
    for(int i=1;i<N;i++) inv3[i]=inv3[i-1]*Inv%Mod;
}
ll C(int x,int y) {
    if(x<y||x<0||y<0) return 0;
    return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
ll f[N];
ll calc(int a,int b,int c) {
    f[0]=1;
    for(int i=1;i<=a+b;i++) f[i]=((2*f[i-1]-C(i-1,a)-C(i-1,b))%Mod+Mod)%Mod;
    ll ans=0;
    for(int i=0;i<=a+b;i++) {
        ans=(ans+
        C(i+c,c)*powk[a+b-i]%Mod*inv3[i+c+1]%Mod*f[i]
        )%Mod;
        // C(i+c,c)*Pow(a+b-i,k)%Mod*Pow(Pow(3,i+c+1),Mod-2)%Mod*f[i]
    }
    return ans;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int a,b,c,k; cin>>a>>b>>c>>k;
    for(int i=1;i<=max({a+b,a+c,b+c});i++) powk[i]=Pow(i,k);
    ll ans=(calc(a,b,c)+calc(a,c,b)+calc(b,c,a))%Mod;
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}