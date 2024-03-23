#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=42;
const int K=6;
bool mem1;
int n,k;
ll p[K],f[N][N*K],g[N][N*K],c[N][N],suf[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void init() {
    for(int i=0;i<N;i++) c[i][0]=1;
    for(int i=1;i<N;i++)
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%Mod;
}
bool mem2;
int main() {
    freopen("mst.in","r",stdin);
    freopen("mst.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>k;
    ll inv=Pow(100,Mod-2);
    for(int i=0;i<=k;i++) cin>>p[i], p[i]=p[i]*inv%Mod;
    for(int i=k;i>=0;i--) suf[i]=(suf[i+1]+p[i])%Mod;
    f[1][0]=g[1][0]=1;
    for(int t=1;t<=k;t++) {
        ll v=(suf[t]+p[0])%Mod;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=n*k;j++) {
                g[i][j]=f[i][j];
                for(int i1=1;i1<=i;i1++) {
                    ll val=Pow(v,i1*(i-i1)%Mod);
                    for(int j1=0;j1+t<=j;j1++) {
                        g[i][j]=(g[i][j]+f[i1][j1]*g[i-i1][j-j1-t]%Mod*c[i-1][i1-1]%Mod*val%Mod)%Mod;
                    }
                }
            }
        v=(suf[t+1]+p[0])%Mod;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=n*k;j++) {
                f[i][j]=g[i][j];   
                for(int i1=1;i1<=i;i1++) {
                    ll val=Pow(v,i1*(i-i1)%Mod);
                    for(int j1=0;j1+t<=j;j1++) {
                        f[i][j]=(f[i][j]-f[i1][j1]*g[i-i1][j-j1-t]%Mod*c[i-1][i1-1]%Mod*val%Mod+Mod)%Mod;
                    }
                }
            }
    }
    for(int i=n-1;i<=k*(n-1);i++) cout<<f[n][i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}