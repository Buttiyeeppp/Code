#include <bits/stdc++.h>
#include <cwchar>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=52;
bool mem1;
ll n,c;
__int128 f[N],fac[N];
int a[N],vis[N],up[N],dw[N];
void init() {
    fac[0]=1;
    for(int i=1;i<=19;i++) fac[i]=fac[i-1]*i;
    f[0]=f[1]=1;
    for(int i=2;i<=21;i++)
        for(int j=0;j<i;j++) f[i]+=f[j]*((i-j-2<0)? 1:fac[i-j-2]);
}
__int128 F(int x) { return (x<=21)? f[x]:1000000000000000001; }
__int128 Fac(int x) { return (x<=19)? fac[x]:1000000000000000001; }
void con(int x,int y) { dw[up[x]]=dw[y], up[dw[y]]=up[x]; }
void solve() {
    cin>>n>>c;
    if(F(n)<c) return cout<<-1<<endl, void();
    for(int i=1;i<=n;i++) vis[i]=a[i]=0, up[i]=dw[i]=i;
    for(int i=1,j,r;i<=n;i++) {
        ll tot;
        __int128 now;
        for(j=1,r=i;r<=n;j++,r++) {
            now=((j-2<0)? 1:Fac(j-2))*F(n-(r));
            if(c>now) c-=now;
            else break;
        }
        tot=j-1, a[i]=r, vis[r]=1, con(i,r);
        for(int k=i+1;k<=r;k++) {
            tot--, now=((tot-1<0)? 1:Fac(tot-1))*F(n-(r));
            for(int v=i;v<=r;v++) if(!vis[v]&&v!=up[k]) {
                if(c>now) c-=now;
                else { a[k]=v, vis[v]=1, con(k,v); break; }
            }
        }
        for(int k=i+1;k<=r;k++) if(!a[k]) a[k]=up[k];
        i=r;
    }
    if(c!=1) return cout<<-1<<endl, void();
    for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    cout<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}