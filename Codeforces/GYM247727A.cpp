#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=2e3+10;
bool mem1;
ll fac[N],inv[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void init() {
    fac[0]=inv[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
ll A[3][3];
ll det() {
    ll res=1, f=1;
    for(int i=1;i<=2;i++) {
        int k=i;
        while(k<=2&&!A[k][i]) k++;
        if(k>2) return 0;
        if(k!=i) {
            f*=-1;
            for(int j=1;j<=2;j++) swap(A[i][j],A[k][j]);
        }
        ll invv=Pow(A[i][i],Mod-2);
        res=res*A[i][i]%Mod;
        for(int j=i+1;j<=2;j++) {
            ll val=A[j][i]*invv%Mod;
            for(int k=i;k<=2;k++) A[j][k]=(A[j][k]-A[i][k]*val%Mod+Mod)%Mod;
        }
    }
    return (res*f+Mod)%Mod;
}
int n,m;
void solve() {
    A[1][1]=A[2][2]=C(n+m,n);
    A[1][2]=C(n+m,n-1);
    A[2][1]=C(n+m,m-1);
    cout<<det()<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    while(cin>>n>>m) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}