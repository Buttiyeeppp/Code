#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int INF=0x3f3f3f3f;
const int N=1e2+10;
const int M=5e3+10;
int n,m,s,t;
int head[N],tot=1;
struct Edge {
    int to,w,nxt;
}E[M<<1];
void add(int u,int v,int w) {
    E[++tot]=Edge{v,w,head[u]};
    head[u]=tot;
}
int dis[N],cur[N];
bool bfs() {
    queue<int> q;
    memset(dis,INF,sizeof(dis));
    memcpy(cur,head,sizeof(head));
    q.emplace(s), dis[s]=0;
    while(q.size()) {
        int u=q.front(); q.pop();
        for(int i=head[u],to=E[i].to;i>1;i=E[i].nxt,to=E[i].to) {
            if(dis[to]==INF&&E[i].w) dis[to]=dis[u]+1, q.emplace(to);
        }
    }
    return (dis[t]!=INF);
}
int dfs(int x,int flow) {
    if(x==t||!flow) return flow; 
    int use=0;
    for(int i=cur[x],to=E[i].to;i>1;i=E[i].nxt,to=E[i].to) {
        cur[x]=i;
        if(dis[to]!=dis[x]+1||!E[i].w) continue;
        int c=dfs(to,min(flow,E[i].w));
        if(!c) { dis[to]=-1; continue; }
        flow-=c, use+=c, E[i].w-=c, E[i^1].w+=c;
    }
    return use;
}
int main() {
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1,u,v,c;i<=m;i++) {
        scanf("%d%d%d",&u,&v,&c);
        add(u,v,c), add(v,u,0);
    }
    ll ans=0;
    while(bfs()) ans+=dfs(s,INT_MAX);
    printf("%lld",ans);
    return 0;
}