#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e3+10;
const ll Mod=1e9+7;
bool mem1;
int n,q,a[N],x[N],y[N];
ll g[N][N],g[N][N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=q;i++) cin>>x[i]>>y[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) if(a[i]>a[j]) g[i][j]=1;
    ll inv=Pow(2,Mod-2);
    for(int i=1;i<=q;i++) {
        for(int j=1;j<=n;j++) {
            g[x[i]][j]=(g[y[i]][j]+g[x[i]][j])*inv%Mod;
            g[j][x[i]]=(g[j][y[i]]+g[j][x[i]])*inv%Mod;
            g[y[i]][j]=(g[x[i]][j]+g[y[i]][j])*inv%Mod;
            g[j][y[i]]=(g[j][x[i]]+g[j][y[i]])*inv%Mod;
        }
        g[x[i]][y[i]]=g[y[i]][x[i]]=(g[x[i]][y[i]]+g[y[i]][x[i]])*inv%Mod;
        for(int j=1;j<=n;j++) {
            g[x[i]][j]=g[x[i]][j], g[j][x[i]]=g[j][x[i]];
            g[y[i]][j]=g[y[i]][j], g[j][y[i]]=g[j][y[i]];
        }
        for(int j=1;j<=n;j++) {
            g[x[i]][j]=g[j][x[i]]=g[y[i]][j]=g[j][y[i]]=0;
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++) ans=(ans+g[i][j])%Mod;
    cout<<ans*Pow(2,q)%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}