#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=1e9+7;
bool mem1;
int n,q,dfn[N],tim;
int dep[N],fa[N],top[N],sz[N],son[N];
vector<int> eg[N],g[N];
void dfs(int x,int from) {
    dep[x]=dep[from]+1, fa[x]=from, sz[x]=1;
    for(int y:eg[x]) if(y!=from) {
        dfs(y,x);
        if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
        sz[x]+=sz[y];
    }
}
void dfs1(int x,int from) {
    dfn[x]=++tim;
    if(son[x]) top[son[x]]=top[x], dfs1(son[x],x);
    for(int y:eg[x]) if(y!=from&&y!=son[x])
        top[y]=y, dfs1(y,x);
}
int lca(int x,int y) {
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    return x;
}
vector<int> nd,node;
int yep[N],sp[N];
void Addedge(int x,int y) {
    g[x].push_back(y), g[y].push_back(x);
    if(!yep[x]) yep[x]=1, node.push_back(x);
    if(!yep[y]) yep[y]=1, node.push_back(y);
}
int st[N],Top;
ll cnt[N],f[2][310],k,m,r,p;
void buildt() {
    sort(nd.begin(),nd.end(),[](const int &x,const int &y) { return dfn[x]<dfn[y]; });
    st[Top=1]=1;
    for(int i:nd) if(i!=1) {
        int l=lca(i,st[Top]);
        if(st[Top]!=l) {
            while(Top>1&&dep[st[Top-1]]>dep[l])
                Addedge(st[Top],st[Top-1]), Top--;
            if(dep[st[Top]]>dep[l]) Addedge(st[Top],l), Top--;
            if(st[Top]!=l) st[++Top]=l;
        }
        st[++Top]=i;
    }
    while(Top>1) Addedge(st[Top],st[Top-1]), Top--;
}
void dfs2(int x,int from) {
    if(sp[x]) {
        p^=1, f[p][0]=0;
        for(int j=1;j<=m;j++) 
            f[p][j]=(f[p^1][j]*max(0ll,j-cnt[x])+f[p^1][j-1])%Mod;
    }
    for(int y:g[x]) if(y!=from) {
        cnt[y]=cnt[x]+sp[x];
        dfs2(y,x);
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q;
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        eg[x].push_back(y), eg[y].push_back(x);
    }
    dfs(1,0), dfs1(1,0);
    while(q--) {
        cin>>k>>m>>r;
        for(int i=1,x;i<=k;i++) cin>>x, nd.push_back(x), sp[x]=1;
        if(!sp[r]) nd.push_back(r);
        if(!sp[1]) nd.push_back(1);
        buildt();

        p=tim=0, f[0][0]=1;
        dfs2(r,0);
        ll ans=0;
        for(int i=1;i<=m;i++) ans=(ans+f[p][i])%Mod;
        cout<<ans<<endl;

        for(int i:node) yep[i]=sp[i]=cnt[i]=0, g[i].clear();
        for(int i=0;i<=1;i++)
            for(int j=0;j<=m;j++) f[i][j]=0;
        nd.clear(), node.clear();
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}