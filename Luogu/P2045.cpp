#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const int N=1e4+10;
const int M=1e5+10;
int n,k,a[52][52],id[52][52],s,t;
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
            if(dis[to]>dis[u]-E[i].cost&&E[i].w) {
                dis[to]=dis[u]-E[i].cost;
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
		if(!E[i].w||dis[to]!=dis[x]-E[i].cost||vis[to]) continue;
		c=dfs(to,min(flow,E[i].w));
		if(!c) { vis[to]=1; continue; }
		flow-=c, use+=c, E[i].w-=c, E[i^1].w+=c;
	}
	return use;
}
int main() {
	scanf("%d%d",&n,&k);
	s=2*n*n+1, t=s+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) scanf("%d",&a[i][j]), id[i][j]=2*(i*n-n+j-1)+1;
	add(s,id[1][1],k,0), add(id[n][n]+1,t,k,0);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) {
			add(id[i][j],id[i][j]+1,1,a[i][j]);
			add(id[i][j],id[i][j]+1,k-1,0);
			if(i<n) add(id[i][j]+1,id[i+1][j],k,0);
			if(j<n) add(id[i][j]+1,id[i][j+1],k,0);
		}
	int ans=0;
	while(spfa()) ans-=dis[t]*dfs(s,INF);
	printf("%d",ans);
	return 0;
}