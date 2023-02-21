#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int M=4e6+10;
int n,m,head[N],tot=1;
struct Edge {
    int to,nxt;
}e[M];
void add(int u,int v) {
    e[++tot]=Edge{v,head[u]};
    head[u]=tot;
}
int dfn[N],low[N],tim,bridge[M];
void tarjan(int x,int from) {
    dfn[x]=low[x]=++tim;
    for(int i=head[x],y=e[i].to;i>1;i=e[i].nxt,y=e[i].to) {
        if((i^1)==from) continue;
        if(!dfn[y]) {
            tarjan(y,i);
            low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x]) bridge[i]=bridge[i^1]=1;
        }else low[x]=min(low[x],dfn[y]);
    }
}
int cnt,vis[N];
vector<int> dcc[N];
void dfs(int x) {
    vis[x]=1; dcc[cnt].emplace_back(x);
    for(int i=head[x],y=e[i].to;i>1;i=e[i].nxt,y=e[i].to) {
        if(!bridge[i]&&!vis[y]) dfs(y);
    }
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) {
        scanf("%d%d",&u,&v);
        add(u,v), add(v,u);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
    for(int i=1;i<=n;i++) if(!vis[i]) cnt++, dfs(i);
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++) {
        printf("%d ",dcc[i].size());
        for(auto now:dcc[i]) printf("%d ",now); puts("");
    }
    return 0;
}