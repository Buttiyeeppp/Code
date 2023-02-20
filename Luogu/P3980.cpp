#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const int N=2e3+10;
const int M=3e4+10;
int n,m,s,t;
int head[N],tot=1;
struct Edge {
	int to,w,cost,nxt;
}E[M];
void add(int u,int v,int w,int c) {
	E[++tot]=Edge{v,w,c,head[u]};
	head[u]=tot;
	E[++tot]=Edge{u,0,-c,head[v]};
	head[v]=tot;
}
int cur[N],vis[N],dis[N],in[N];
bool spfa() {
    memset(vis,0,sizeof(vis));
    memset(dis,INF,sizeof(dis));
    memcpy(cur,head,sizeof(head));
    priority_queue<PII,vector<PII>,greater<PII>> q;
    q.emplace(0,s), dis[s]=0;
    while(q.size()) {
        int u=q.top().second; q.pop();
        in[u]=0;
        for(int i=head[u],to=E[i].to;i>1;i=E[i].nxt,to=E[i].to) {
            if(dis[to]>dis[u]+E[i].cost&&E[i].w) {
                dis[to]=dis[u]+E[i].cost;
                if(!in[to]) q.emplace(dis[to],to), in[to]=1;
            }
        }
    }
    return (dis[t]!=INF);
}
int dfs(int x,int flow) {
	if(x==t||!flow) return flow;
	vis[x]=1;
	int use=0,c;
	for(int i=cur[x],to=E[i].to;i>1;i=E[i].nxt,to=E[i].to) {
		cur[x]=i;
		if(!E[i].w||dis[to]!=dis[x]+E[i].cost||vis[to]) continue;
		c=dfs(to,min(flow,E[i].w));
		if(!c) { vis[to]=1; continue; }
		flow-=c, use+=c, E[i].w-=c, E[i^1].w+=c;
	}
	return use;
}
int main() {
    scanf("%d%d",&n,&m);
    s=n+2, t=n+1;
    add(s,1,INF,0);
    for(int i=1,x;i<=n;i++) scanf("%d",&x), add(i,i+1,INF-x,0);
    for(int i=1,s,t,c;i<=m;i++) {
        scanf("%d%d%d",&s,&t,&c);
        add(s,t+1,INF,c);
    }
	int ans=0;
	while(spfa()) ans+=dis[t]*dfs(s,INF);
	printf("%d",ans);
	return 0;
}