#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e8+7;
const int N=1e6+10;
bool mem1;
int n,m;
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
ll f[N],fac[N],inv[N],A[N];
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>m;
    ll z=(Pow(2,n)-1+Mod)%Mod;
    f[0]=A[0]=1;
    for(int i=1;i<=m;i++) A[i]=A[i-1]*(z-i+1)%Mod;
    for(int i=2;i<=m;i++)
        f[i]=((A[i-1]-f[i-1]-f[i-2]*(i-1)%Mod*(z-i+2+Mod)%Mod)%Mod+Mod)%Mod;
    cout<<f[m]*inv[m]%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}