#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const int N=4e2+10;
const int M=2e4+10;
int n,m,s,t;
int head[N],tot=1;
struct Edge {
    int to,w,nxt,cost;
}E[M<<1];
void add(int u,int v,int w,int cost) {
    E[++tot]=Edge{v,w,head[u],cost};
    head[u]=tot;
}
int dis[N],cur[N],vis[N];
bool bfs() {
    memset(vis,0,sizeof(vis));
    memset(dis,INF,sizeof(dis));
    memcpy(cur,head,sizeof(head));
    priority_queue<PII,vector<PII>,greater<PII>> q;
    q.emplace(0,s), dis[s]=0;
    while(q.size()) {
        int u=q.top().second; q.pop();
        for(int i=head[u],to=E[i].to;i>1;i=E[i].nxt,to=E[i].to) {
            if(dis[to]>dis[u]+E[i].cost&&E[i].w) dis[to]=dis[u]+E[i].cost, q.emplace(dis[to],to);
        }
    }
    return (dis[t]!=INF);
}
int dfs(int x,int flow) {
    if(x==t||!flow) return flow; 
    vis[x]=1;
    int use=0;
    for(int i=cur[x],to=E[i].to;i>1;i=E[i].nxt,to=E[i].to) {
        cur[x]=i;
        if(dis[to]<dis[x]+E[i].cost||!E[i].w||vis[to]) continue;
        int c=dfs(to,min(flow,E[i].w));
        if(!c) { vis[to]=1; continue; }
        flow-=c, use+=c, E[i].w-=c, E[i^1].w+=c;
    }
    return use;
}
int main() {
    scanf("%d%d",&n,&m);
    s=1,t=n;
    for(int i=1,u,v,w,cost;i<=m;i++) {
        scanf("%d%d%d%d",&u,&v,&w,&cost);
        add(u,v,w,cost), add(v,u,0,-cost);
    }
    int ans=0,cst=0,f;
    while(bfs()) f=dfs(s,INT_MAX), ans+=f, cst+=dis[t]*f;
    printf("%d %d",ans,cst);
    return 0;
}