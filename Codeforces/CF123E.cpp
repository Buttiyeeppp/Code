#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
double x[N],y[N],ans,sum;
int n,sz[N];
vector<int> g[N];
void dfs(int u,int from) {
    sz[u]=1;
    for(auto v:g[u]) {
        if(v==from) continue;
        dfs(v,u);
        ans+=x[v]*sz[v]*y[u];
        x[u]+=x[v], sz[u]+=sz[v];
    }
    ans+=(sum-x[u])*y[u]*(n-sz[u]);
}
int main() {
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    double sx=0,sy=0;
    for(int i=1;i<=n;i++) scanf("%lf%lf",&x[i],&y[i]), sx+=x[i], sy+=y[i];
    for(int i=1;i<=n;i++) x[i]/=sx, y[i]/=sy, sum+=x[i];
    dfs(1,0);
    printf("%.10lf",ans);
    return 0;
}