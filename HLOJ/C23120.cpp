#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const int N=2e5+10; 
bool mem1;
int n,m,k,d[N],vis[N];
ll dis[N];
priority_queue<ll> now[N];
vector<PLL> eg[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>k;
    priority_queue<PLL,vector<PLL>,greater<PLL>> q;
    memset(dis,0x3f,sizeof(dis));
    for(int i=1,x;i<=k;i++) cin>>x, dis[x]=0, q.emplace(0,x);
    for(int i=1;i<=n;i++) cin>>d[i];
    for(int i=1,x,y,w;i<=m;i++) {
        cin>>x>>y>>w;
        eg[x].emplace_back(y,w), eg[y].emplace_back(x,w);
    }
    while(q.size()) {
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(auto to:eg[x]) if(!vis[to.first]) {
            int y=to.first;
            now[y].push(dis[x]+to.second);
            if((int)now[y].size()>d[y]+1) now[y].pop();
            if((int)now[y].size()==d[y]+1&&now[y].top()<dis[y]) dis[y]=now[y].top(), q.emplace(dis[y],y);
        }
    }
    cout<<((!vis[1])? -1:dis[1])<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}