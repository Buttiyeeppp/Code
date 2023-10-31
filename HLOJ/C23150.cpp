#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
ll x,y,n,Mod,B;
ll f[2][N],g[N],s[N];
void Add(ll &x,ll y) {
    return x=(x+y>=Mod? x+y-Mod:x+y), void();
}
ll calc(ll lim) {
    memset(g,0,sizeof(g)); g[0]=1;
    for(int i=lim;i<=B;i++) 
        for(int j=i;j<=n;j++) g[j]=(g[j]+g[j-i])%Mod;
    memset(f,0,sizeof(f)); f[0][0]=1;
    memset(s,0,sizeof(s)); s[0]=1;
    for(int i=1;i*max(B+1,lim)<=n;i++) {
        memset(f[i&1],0,sizeof(f[i&1]));
        for(int j=0;j<=n;j++) {
            if(j-i>=0) Add(f[i&1][j],f[i&1][j-i]);
            if(j-max(B+1,lim)>=0) Add(f[i&1][j],f[(i&1)^1][j-max(B+1,lim)]);
            Add(s[j],f[i&1][j]);
        }
    }
    ll res=0;
    for(int i=0;i<=n;i++) Add(res,s[i]*g[n-i]%Mod);
    return res;
}
bool mem2;
int main() {
    freopen("fans.in","r",stdin);
    freopen("fans.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>x>>y>>n>>Mod;
    B=sqrt(n)+1;
    cout<<(calc(x)-calc(y+1)+Mod)%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}