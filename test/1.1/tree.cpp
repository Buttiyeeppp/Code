#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3e5+10;
typedef pair<int,int> PII;
int n,d[N];
ll f[N][3];
vector<PII> g[N];
void dfs(int x,int from) {
    for(auto to:g[x]) {
        int y=to.first;
        if(y==from) continue;
        dfs(y,x);
        f[x][0]+=f[y][1], f[x][1]+=f[y][1];
    }
    priority_queue<ll> q;
    while(q.size()) q.pop();
    for(auto to:g[x]) {
        int y=to.first;
        if(y==from) continue;
        if(d[y]) q.push(f[y][0]+to.second-f[y][1]);
    }
    for(int i=1;i<=d[x];i++) {
    	if(q.empty()) break;
		ll val=q.top(); q.pop();
        if(val<0) break;
        f[x][1]+=val;
        if(i<d[x]) f[x][0]+=val;
    }
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    for(int i=1,u,v,w;i<n;i++) {
        scanf("%d%d%d",&u,&v,&w);
        g[u].emplace_back(v,w), g[v].emplace_back(u,w);
    }
    dfs(1,0);
//    for(int i=1;i<=n;i++) cout<<i<<" "<<f[i][1]<<" "<<f[i][0]<<endl;
    printf("%lld",f[1][1]);
    return 0;
}
