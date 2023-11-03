#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,dfn[N],tim,dep[N],fa[N][20],sz[N];
vector<int> eg[N],g[N];
vector<int> nd,node;
void dfs(int x,int from) {
    dfn[x]=++tim, dep[x]=dep[from]+1, fa[x][0]=from, sz[x]=1;
    for(int y:eg[x]) if(y!=from) {
        dfs(y,x);
        sz[x]+=sz[y];
    }
}
void jump(int &x,int h) {
    for(int i=0;h;h>>=1,i++) if(h&1) x=fa[x][i];
}
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    jump(x,dep[x]-dep[y]);
    if(x==y) return x;
    for(int i=19;i>=0;i--)
        if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
    return fa[x][0];
}
int st[N],top,yep[N];
void Addedge(int x,int y) {
    g[x].push_back(y), g[y].push_back(x);
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
            if(dep[st[top]]>dep[l]) Addedge(st[top],l), top--;
            if(st[top]!=l) st[++top]=l;
        }
        st[++top]=i;
    }
    while(top>1) Addedge(st[top],st[top-1]), top--;
}
void buildt() {
    nd.push_back(1);
    sort(nd.begin(),nd.end(),[](const int &x,const int &y) { return dfn[x]<dfn[y]; });
    int m=nd.size();
    for(int i=1;i<m;i++) nd.push_back(lca(nd[i],nd[i-1]));
    sort(nd.begin(),nd.end(),[](const int &x,const int &y) { return dfn[x]<dfn[y]; });
    nd.erase(unique(nd.begin(),nd.end()),nd.end());
    for(int i=1;i<(int)nd.size();i++) Addedge(lca(nd[i-1],nd[i]),nd[i]);
}
int ne[N];
int dis(int x,int y) { return dep[x]+dep[y]-2*dep[lca(x,y)]; }
void dfs1(int x,int from) {
    for(int y:g[x]) if(y!=from) {
        dfs1(y,x);
        if(ne[y]) {
            if(!ne[x]) ne[x]=ne[y];
            else {
                int d1=dis(x,ne[y]), d2=dis(x,ne[x]);
                if((d1<d2||(d1==d2&&ne[y]<ne[x]))) ne[x]=ne[y];
            }
        }
    }
}
void dfs2(int x,int from) {
    for(int y:g[x]) if(y!=from) {
        if(!ne[y]) ne[y]=ne[x];
        else {
            int d1=dis(y,ne[y]), d2=dis(y,ne[x]);
            if(d1>d2||(d1==d2&&ne[x]<ne[y])) ne[y]=ne[x];
        }
        dfs2(y,x);
    }
}
int ans[N];
void dfs3(int x,int from) {
    int siz=sz[x];
    for(int y:g[x]) if(y!=from) {
        dfs3(y,x);
        int jp=y; jump(jp,dep[y]-dep[x]-1);
        siz-=sz[jp];
        int p=y, dd1=dis(y,ne[y]), dd2=dis(x,ne[x]);
        for(int i=19;i>=0;i--) {
            // int d1=dis(ne[y],fa[p][i]), d2=dis(ne[x],fa[p][i]);
            int d1=dd1+dep[y]-dep[fa[p][i]], d2=dd2+dep[fa[p][i]]-dep[x];
            if(fa[p][i]&&(d1<d2||(d1==d2&&ne[y]<ne[x]))) p=fa[p][i];
        }
        ans[ne[x]]+=sz[jp]-sz[p];
        ans[ne[y]]+=sz[p]-sz[y];
    }
    ans[ne[x]]+=siz;
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
        for(int i=1,x;i<=m;i++) cin>>x, nd.push_back(x), ne[x]=x;
        vector<int> mem=nd;
        buildt();
        dfs1(1,0);
        dfs2(1,0);
        dfs3(1,0);
        for(int i:mem) cout<<ans[i]<<" ";
        cout<<endl;
        for(int i:node) yep[i]=ans[i]=ne[i]=0, g[i].clear();
        node.clear(), nd.clear();
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}