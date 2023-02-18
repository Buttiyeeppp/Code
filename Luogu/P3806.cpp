#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=1e7+10;
typedef pair<int,int> PII;
int n,m,k[N],ans[N];
vector<vector<PII>> G;
int sz[N],vis[N];
PII dfs1(int x,int s,int from) {
    sz[x]=1;
    int mxS=0; PII ans=make_pair(INT_MAX,0);
    for(auto now:G[x]) {
        if(now.first==from||vis[now.first]) continue;
        ans=min(ans,dfs1(now.first,s,x));
        sz[x]+=sz[now.first];
        mxS=max(mxS,sz[now.first]);
    }
    mxS=max(mxS,s-sz[x]);
    return min(ans,PII{mxS,x});
}
int dis[N],cnt[M];
void dfs2(int x,int from) {
    sz[x]=1;
    for(auto y:G[x]) {
        if(y.first==from||vis[y.first]) continue;
        dis[y.first]=dis[x]+y.second;
        dfs2(y.first,x);
        sz[x]+=sz[y.first];
    }
}
void dfs3(int x,int from,int val) {
    if(dis[x]<M) cnt[dis[x]]+=val;
    for(auto y:G[x]) {
        if(y.first==from||vis[y.first]) continue;
        dfs3(y.first,x,val);
    }
}
void dfs4(int x,int from) {
    for(int i=1;i<=m;i++) if(k[i]>=dis[x]) ans[i]|=cnt[k[i]-dis[x]];
    for(auto y:G[x]) {
        if(y.first==from||vis[y.first]) continue;
        dfs4(y.first,x);
    }
}
void sol(int x) {
    dis[x]=0, dfs2(x,0);
    for(auto y:G[x]) {
        if(vis[y.first]) continue;
        dfs3(y.first,x,1);
    }
    for(auto y:G[x]) {
        if(vis[y.first]) continue;
        dfs3(y.first,x,-1);
        dfs4(y.first,x);
        dfs3(y.first,x,1);
    }
    for(auto y:G[x]) {
        if(vis[y.first]) continue;
        dfs3(y.first,x,-1);
    }
    vis[x]=1;
    for(auto y:G[x]) {
        if(vis[y.first]) continue;
        sol(dfs1(y.first,sz[y.first],0).second);
    }
}
int main() {
	scanf("%d%d",&n,&m);
    G.resize(n+1);
	for(int i=1,u,v,w;i<n;i++) {
		scanf("%d%d%d",&u,&v,&w);
		G[u].emplace_back(v,w), G[v].emplace_back(u,w);	
	}
    for(int i=1;i<=m;i++) scanf("%d",&k[i]);
    cnt[0]=1;
    sol(dfs1(1,n,0).second);
    for(int i=1;i<=m;i++) puts(ans[i]? "AYE":"NAY");
    return 0;
}