#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e2+10;
const int M=3e4+10;
const int INF=0x3f3f3f3f;
bool mem1;
int n,m,s,t,head[N],tot=1;
struct Edge {
    int to,nxt,w,cost;
}eg[M];
void Add(int x,int y,int c,int w) {
    eg[++tot]={y,head[x],c,w};
    head[x]=tot;
}
int dis[N],cur[N],vis[N];
bool bfs() {
    memcpy(cur,head,sizeof(cur));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis)); dis[s]=0;
    queue<int> q; q.push(s);
    while(q.size()) {
        int x=q.front(); q.pop();
        vis[x]=0;
        for(int i=head[x];i;i=eg[i].nxt) {
            int y=eg[i].to;
            if(dis[y]>dis[x]+eg[i].cost&&eg[i].w) {
                dis[y]=dis[x]+eg[i].cost;
                if(!vis[y]) q.push(y);
            }
        }
    }
    return (dis[t]!=INF);
}
int dfs(int x,int flow) {
    if(x==t||!flow) return flow;
    int use=0; vis[x]=1;
    for(int i=cur[x];i&&flow;i=eg[i].nxt) {
        cur[x]=i;
        int y=eg[i].to;
        if(!eg[i].w||dis[y]!=dis[x]+eg[i].cost||vis[y]) continue;
        int f=dfs(y,min(flow,eg[i].w));
        if(!f) { vis[y]=1; continue; }
        use+=f, flow-=f, eg[i].w-=f, eg[i^1].w+=f;
    }
    return use;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    s=1,t=n;
    for(int i=1,x,y,c,w;i<=m;i++) {
        cin>>x>>y>>c>>w;
        Add(x,y,c,w), Add(y,x,0,-w);
    }
    int f, ans=0, ans1=0;
    while(bfs()) f=dfs(s,INF), ans+=f, ans1+=f*dis[t];
    cout<<ans<<' '<<ans1<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}