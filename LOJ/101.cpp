#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
const int M=1e4+10;
const int INF=0x3f3f3f3f;
bool mem1;
int n,m,s,t,head[N],tot=1;
struct Edge {
    int to,nxt,w;
}eg[M];
void Add(int x,int y,int c) {
    eg[++tot]={y,head[x],c};
    head[x]=tot;
}
int dis[N],cur[N];
bool bfs() {
    memcpy(cur,head,sizeof(cur));
    memset(dis,0x3f,sizeof(dis)); dis[s]=0;
    queue<int> q; q.push(s);
    while(q.size()) {
        int x=q.front(); q.pop();
        for(int i=head[x];i;i=eg[i].nxt) {
            int y=eg[i].to;
            if(dis[y]>dis[x]+1&&eg[i].w) dis[y]=dis[x]+1, q.push(y);
        }
    }
    return (dis[t]!=INF);
}
int dfs(int x,int flow) {
    if(x==t||!flow) return flow;
    int use=0;
    for(int i=cur[x];i&&flow;i=eg[i].nxt) {
        cur[x]=i;
        int y=eg[i].to;
        if(!eg[i].w||dis[y]!=dis[x]+1) continue;
        int f=dfs(y,min(flow,eg[i].w));
        if(!f) { dis[y]=-1; continue; }
        use+=f, flow-=f, eg[i].w-=f, eg[i^1].w+=f;
    }
    return use;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>s>>t;
    for(int i=1,x,y,c;i<=m;i++) {
        cin>>x>>y>>c;
        Add(x,y,c), Add(y,x,0);
    }
    ll ans=0;
    while(bfs()) ans+=dfs(s,INF);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}