 #include<bits/stdc++.h>
using namespace std;
#define ll long long
const int NN=3e7;
const int N=5e3+10;
const int M=2e4+10;
const ll Mod=998244353;
int n,m;
ll two[NN];
void init() {
	two[0]=1;
	for(int i=1;i<NN;i++) two[i]=two[i-1]*2ll%Mod;
}
int head[N],tot=1;
struct Edge {
	int from,to,nxt;
}e[M];
void add(int u,int v) {
	e[++tot]=Edge{u,v,head[u]};
	head[u]=tot;
}
int dfn[N],low[N],tim,bri[M];
void tarjan(int x,int from) {
	dfn[x]=low[x]=++tim;
	for(int i=head[x];i>1;i=e[i].nxt) if((i^1)!=from){
		int y=e[i].to;
		if(!dfn[y]) {
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]) bri[i]=bri[i^1]=1;
		}else low[x]=min(low[x],dfn[y]);
	}
}
int col[N],cnt,eg[N],gs[N];
void _dfs(int x) {
	col[x]=cnt, gs[cnt]++;
	for(int i=head[x];i>1;i=e[i].nxt) {
		if(!bri[i]&&!col[e[i].to]) _dfs(e[i].to);
	}
}
vector<int> g[N];
int sz[N];
ll f[N][N],tmp[N];
void dfs(int x,int from) {
	sz[x]=gs[x], f[x][sz[x]]=1;
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		for(int i=1;i<=sz[x]+sz[y];i++) tmp[i]=0;
		for(int i=1;i<=sz[x];i++)
			for(int j=1;j<=sz[y];j++) {
				tmp[i+j]=(tmp[i+j]+f[x][i]*f[y][j]%Mod*two[i*j-1]%Mod)%Mod;
				tmp[i]=(tmp[i]-f[x][i]*f[y][j]%Mod+Mod)%Mod;
			}
		sz[x]+=sz[y];
		for(int i=1;i<=sz[x];i++) f[x][i]=tmp[i];
	}
}
int main() {
	init();
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v), add(u,v), add(v,u);
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
	for(int i=1;i<=n;i++) if(!col[i]) cnt++, _dfs(i);
	for(int i=2,u,v;i<=m*2;i+=2) {
		u=col[e[i].from], v=col[e[i].to];
		if(u!=v) g[u].emplace_back(v), g[v].emplace_back(u);
		else eg[u]++;
	}
	dfs(1,0);
	ll ans=0, c=1;
	for(int i=1;i<=n;i++) ans=(ans+f[1][i])%Mod;
    for(int i=1;i<=cnt;i++) c=c*two[gs[i]*(gs[i]-1)/2-eg[i]]%Mod;
	printf("%lld\n",ans*c%Mod);
	return 0;
}