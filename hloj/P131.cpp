#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n,m,dfn[N],low[N],choose[N],tim,sta[N],top,col[N],cnt;
vector<int> G[N];
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
        ++cnt;
        while(sta[top]!=x) choose[sta[top]]=1, col[sta[top--]]=cnt;
        choose[sta[top]]=1, col[sta[top--]]=cnt;
    }
    return;
}
vector<pair<int,int>> edge;
int yep[N][N];
bitset<N> to[N],go;
int main() {
    freopen("scc.in","r",stdin);
    freopen("scc.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) {
        scanf("%d%d",&u,&v);
        G[u].emplace_back(v), edge.emplace_back(u,v);
        to[u][v]=1;
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    queue<int> q;
    for(int i=1;i<=n;i++) {
        go.reset(), go[i]=1;
        for(auto now:G[i]) {
            yep[i][now]|=go[now];
            go[now]=1;
            q.emplace(now);
            while(q.size()) {
                int u=q.front(); q.pop();
                bitset<N> b=(~go)&to[u];
                int p;
                while((p=b._Find_first())!=b.size()) go[p]=1, q.emplace(p), b[p]=0;
            }
        }
        reverse(G[i].begin(),G[i].end());
        go.reset(), go[i]=1;
        for(auto now:G[i]) {
            yep[i][now]|=go[now];
            go[now]=1;
            q.emplace(now);
            while(q.size()) {
                int u=q.front(); q.pop();
                bitset<N> b=(~go)&to[u];
                int p;
                while((p=b._Find_first())!=b.size()) go[p]=1, q.emplace(p), b[p]=0;
            }
        }
    }
    for(int i=0;i<(int)edge.size();i++) {
        int u=edge[i].first, v=edge[i].second;
        if((col[u]==col[v]&&!yep[u][v])||(col[u]!=col[v]&&yep[u][v])) puts("1");
        else puts("0");
    }
    return 0;
}