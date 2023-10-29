#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+2;
const ll Mod=998244353;
bool mem1;
int n,a[N],b[N],fa[N];
int f[N],sz[N];
int find(int x) {
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}
int head[N],tot=1;
struct Edge {
    int to,nxt;
}eg[N<<2];
void Addedge(int x,int y) {
    eg[++tot]={y,head[x]};
    head[x]=tot;
}
void dfs(int x,int from) {
    fa[x]=from;
    for(int i=head[x];i;i=eg[i].nxt)
        if(eg[i].to!=from) dfs(eg[i].to,x);
}
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
    freopen("todokanai.in","r",stdin);
    freopen("todokanai.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<n;i++) cin>>a[i]>>b[i];
    for(int i=1,a,b;i<n;i++) {
        cin>>a>>b;
        Addedge(a,b), Addedge(b,a);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) f[i]=i, sz[i]=1;
    ll res=1;
    for(int i=1;i<n;i++) {
        int x=find(a[i]), y=find(b[i]);
        if(find(fa[x])==y) swap(x,y);
        if(find(fa[y])!=x) return cout<<0<<endl, 0;
        res=res*sz[x]%Mod*sz[y]%Mod;
        f[y]=x, sz[x]+=sz[y];
    }
    cout<<Pow(res,Mod-2)<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}