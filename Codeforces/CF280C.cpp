#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,dep[N];
vector<int> g[N];
void dfs(int x,int from) {
    dep[x]=dep[from]+1;
    for(auto y:g[x]) {
        if(y!=from) dfs(y,x);
    }
}
int main() {
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    dfs(1,0);
    long double ans=0;
    for(int i=1;i<=n;i++) ans+=1.0/dep[i];
    printf("%.9Lf",ans);
    return 0;
}