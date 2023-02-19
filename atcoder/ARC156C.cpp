#include<bits/stdc++.h>
using namespace std;
const int N=5e3+10;
int n,deg[N],p[N],vis[N];
vector<int> g[N];
int main() {
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v), g[v].emplace_back(u);
        deg[u]++, deg[v]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++) if(deg[i]==1) q.emplace(i);
    while(q.size()>=2) {
        int u=q.front(); q.pop();
        int v=q.front(); q.pop();
        p[u]=v, p[v]=u, vis[u]=vis[v]=1;
        for(auto to:g[u]) if(!vis[to]) {
            if((--deg[to])==1) q.emplace(to);
        }
        for(auto to:g[v]) if(!vis[to]) {
            if((--deg[to])==1) q.emplace(to);
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",p[i]? p[i]:i);
    return 0;
}