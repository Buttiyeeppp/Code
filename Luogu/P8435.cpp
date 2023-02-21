#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,m,dfn[N],low[N],tim,cut[N],rt,sta[N],top,tot;
vector<int> G[N],ans[N];
void tarjan(int x) {
    sta[++top]=x;
    dfn[x]=low[x]=++tim;
    int son=0;
    for(auto y:G[x]) {
        if(!dfn[y]) {
            son++;
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]) {
                // cerr<<"Oh!\n";
                ans[++tot].emplace_back(x);
                while(sta[top+1]!=y) ans[tot].emplace_back(sta[top--]);
            }
        }else low[x]=min(low[x],dfn[y]);
    }
    if(x==rt&&son==0) ans[++tot].emplace_back(x);
    return;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) {
        scanf("%d%d",&u,&v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) rt=i, tarjan(i);
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++) {
        printf("%d ",ans[i].size());
        for(auto now:ans[i]) printf("%d ",now); puts("");
    }
    return 0;
}