#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,dfn[N],tim,fa[N][20],dep[N];
vector<int> eg[N];
void dfs(int x,int from) {
    dfn[x]=++tim, fa[x][0]=from, dep[x]=dep[from]+1;
    for(int y:eg[x]) if(y!=from) {
        dfs(y,x);
    }
}
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
        if(h&1) x=fa[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) 
        if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
    return fa[x][0];
}
vector<int> nd,g[N],node;
int st[N],top,yep[N],sp[N];
void Addedge(int x,int y) {
    g[x].push_back(y);
    g[y].push_back(x);
    if(!yep[x]) yep[x]=1, node.push_back(x);
    if(!yep[y]) yep[y]=1, node.push_back(y);
}
void buildT() {
    sort(nd.begin(),nd.end(),[](const int &x,const int &y) { return dfn[x]<dfn[y]; });
    st[top=1]=1;
    for(int i:nd) if(i!=1) {
        int l=lca(i,st[top]);
        if(st[top]!=l) {
            while(top>1&&dep[st[top-1]]>dep[l])
                Addedge(st[top],st[top-1]), top--;
            if(top&&dep[st[top]]>dep[l]) Addedge(st[top],l), top--;
            if(st[top]!=l) st[++top]=l;
        }
        st[++top]=i;
    }
    while(top>1) Addedge(st[top],st[top-1]), top--;
}
ll s[N],mn[N],mx[N],cnt[N];
ll Mn,Mx,Sum;
const ll INF=1e15;
void dfs1(int x,int from) {
    cnt[x]=s[x]=mx[x]=0, mn[x]=INF;
    if(sp[x]) cnt[x]=1, mn[x]=0;
    for(int y:g[x]) if(y!=from) {
        dfs1(y,x);
        ll l=dep[y]-dep[x];
        if(cnt[x]&&cnt[y]) {
            Sum+=s[x]*cnt[y]+(s[y]+cnt[y]*l)*cnt[x];
            Mx=max(Mx,mx[x]+mx[y]+l);
            Mn=min(Mn,mn[x]+mn[y]+l);
        }
        if(cnt[y]) {
            mx[x]=max(mx[x],mx[y]+l);
            mn[x]=min(mn[x],mn[y]+l);
        }
        s[x]+=s[y]+cnt[y]*(dep[y]-dep[x]);
        cnt[x]+=cnt[y];
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        eg[x].push_back(y), eg[y].push_back(x);
    }
    dfs(1,0);

    for(int j=1;j<20;j++)
        for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
    int q; cin>>q;
    while(q--) {
        int m; cin>>m;
        for(int i=1,x;i<=m;i++) cin>>x, nd.push_back(x), sp[x]=1;
        buildT();
        Mx=Sum=0, Mn=INF;
        dfs1(1,0);
        cout<<Sum<<" "<<Mn<<" "<<Mx<<endl;
        for(int i:node) g[i].clear(), yep[i]=sp[i]=0;
        nd.clear(), node.clear();
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}