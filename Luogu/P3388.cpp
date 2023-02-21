#include<bits/stdc++.h>
using namespace std;
const int N=2e4+10;
int n,m,dfn[N],low[N],tim,cut[N],rt;
vector<int> G[N];
void tarjan(int x) {
    dfn[x]=low[x]=++tim;
    int son=0;
    for(auto y:G[x]) {
        if(!dfn[y]) {
            son++;
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(x!=rt&&low[y]>=dfn[x]) cut[x]=1;
        }else low[x]=min(low[x],dfn[y]);
    }
    if(x==rt&&son>=2) cut[x]=1;
    return;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) {
        scanf("%d%d",&u,&v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) rt=i, tarjan(i);
    int cnt=0;
    for(int i=1;i<=n;i++) if(cut[i]) cnt++;
    printf("%d\n",cnt);
    for(int i=1;i<=n;i++) if(cut[i]) printf("%d ",i);
    return 0;
}