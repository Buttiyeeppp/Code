#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int M=1e6+10; 
vector<int> g[N],G[N];
int n,m,w[N],col[N],cnt,mx[N],mn[N];
int dfn[N],low[N],choose[N],tim,sta[N],top;
void tarjan(int x) {
	dfn[x]=low[x]=++tim;
	sta[++top]=x;
	for(auto y:g[x]) {
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(!choose[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]) {
		choose[x]=1, col[x]=++cnt;
		mx[cnt]=mn[cnt]=w[x];
		while(sta[top]!=x) {
			choose[sta[top]]=1, col[sta[top]]=cnt;
			mx[cnt]=max(mx[cnt],w[sta[top]]), mn[cnt]=min(mn[cnt],w[sta[top]]);
			top--;
		}
		top--;
		
    }
}
int Num_Edge;
struct Edge {
	int u,v;
}e[M];
int ind[N],yep[N],f[N];
int main() {
	// freopen("P1073_2.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1,u,v,op;i<=m;i++) {
		scanf("%d%d%d",&u,&v,&op);
		g[u].push_back(v), e[++Num_Edge]=(Edge){u,v};
		if(op==2) g[v].push_back(u), e[++Num_Edge]=(Edge){v,u};
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	// for(int i=1;i<=n;i++) cout<<"check "<<i<<" "<<col[i]<<" "<<mn[col[i]]<<" "<<mx[col[i]]<<endl;
	// cout<<mn[col[n]]<<" "<<mx[col[n]]<<endl;
	for(int i=1,u,v;i<=Num_Edge;i++) {
		u=col[e[i].u], v=col[e[i].v];
		if(u!=v) G[u].push_back(v), ind[v]++;
	}
	queue<int> q;
	for(int i=1;i<=cnt;i++) if(!ind[i]) q.push(i);
	yep[col[1]]=1;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		// cout<<u<<" "<<yep[u]<<" "<<mn[u]<<" "<<mx[u]<<endl;
		for(auto v:G[u]) {
			yep[v]|=yep[u];
			if(yep[u]) {
				mn[v]=min(mn[v],mn[u]);
				f[v]=max({f[v],f[u],mx[v]-mn[v]});
			}
			ind[v]--;
			if(!ind[v]) q.push(v);
		}
	}
	if(!yep[col[n]]) puts("0");
	else printf("%d",f[col[n]]);
	return 0;
}