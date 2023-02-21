#include<bits/stdc++.h>
using namespace std;
const int N=2e4+10;
const int M=2e5+10;
int n,m,dfn[N],low[N],tim,sta[N],top,choose[N];
int col[N],tot,a[N],ind[N],A[N],dis[N];
struct Edge {
    int u,v;
}e[M];
vector<int> G[N],g[N];
void tarjan(int x) {
    dfn[x]=low[x]=++tim;
    sta[++top]=x;
    for(auto y:G[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else if(!choose[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]) {
        tot++;
        while(sta[top+1]!=x) choose[sta[top]]=1, A[tot]+=a[sta[top]], col[sta[top--]]=tot;
    }
    return;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1,u,v;i<=m;i++) {
        scanf("%d%d",&u,&v);
        e[i]=Edge{u,v};
        G[u].emplace_back(v);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1,u,v;i<=m;i++) {
        u=col[e[i].u], v=col[e[i].v];
        if(u!=v) g[u].emplace_back(v), ind[v]++;
    }
    queue<int> q;
    for(int i=1;i<=tot;i++) if(!ind[i]) q.emplace(i);
    int ans=0;
    while(q.size()) {
        int u=q.front(); q.pop();
        dis[u]+=A[u];
        ans=max(ans,dis[u]);
        for(auto to:g[u]) {
            dis[to]=max(dis[to],dis[u]);
            ind[to]--;
            if(!ind[to]) q.emplace(to);
        }
    }
    printf("%d\n",ans);
    return 0;
}