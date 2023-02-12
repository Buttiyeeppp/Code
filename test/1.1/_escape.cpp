#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+10;
const ll INF=1e17;
int n,s,q,e,ok[N];
struct Edge {
    int u,v;
}edge[N];
vector<pair<int,int> > g[N];
int dep[N],dfn[N],tim,mx[N],fa[N][20];
ll f[N],dis[N],fa_mn[N][20],len[N];
void dfs(int x,int from,ll distance) {
    if(ok[x]) f[x]=0, distance=0;
    mx[x]=dfn[x]=++tim, dep[x]=dep[from]+1;
    fa[x][0]=from, dis[x]=distance;
    for(auto to:g[x]) {
        int y=to.first;
        if(y==from) continue;
        len[y]=len[x]+to.second;
        dfs(y,x,(distance==INF?INF:distance+to.second));
        mx[x]=max(mx[x],mx[y]);
        f[x]=min(f[x],f[y]+to.second);
    }
    for(auto to:g[x]) {
        int y=to.first;
        if(y==from) continue;
        fa_mn[y][0]=f[x]-len[x];
	}
}
int main() {
    freopen("escape.in","r",stdin);
    freopen("escape.out","w",stdout);
    scanf("%d%d%d%d",&n,&s,&q,&e);
    for(int i=1,u,v,w;i<n;i++) {
        scanf("%d%d%d",&u,&v,&w);
        g[u].emplace_back(v,w), g[v].emplace_back(u,w);
        edge[i]=(Edge){u,v};
    }
    for(int i=1,u;i<=s;i++) {
        scanf("%d",&u);
        ok[u]=1;
    }
    memset(f,0x3f,sizeof(f)); 
    dfs(e,0,INF);
    for(int i=1;i<20;i++)
        for(int j=1;j<=n;j++) 
            fa[j][i]=fa[fa[j][i-1]][i-1], fa_mn[j][i]=min(fa_mn[j][i-1],fa_mn[fa[j][i-1]][i-1]);
//    for(int i=1;i<=n;i++) cout<<"CHeck "<<i<<" "<<dfn[i]<<" "<<mx[i]<<endl; 
    int id, u;
    while(q--) {
        scanf("%d%d",&id,&u);
        if(dep[edge[id].u]<dep[edge[id].v]) swap(edge[id].u,edge[id].v);
        int v=edge[id].u;
        if(dfn[u]<dfn[v]||dfn[u]>mx[v]) {puts("escaped"); continue;}
//        cout<<"Query "<<u<<" "<<f[u]<<" "<<dis[u]<<" "<<fa_mn[u][0]<<endl;
        ll ans=f[u], mn=INF;
        if(dis[u]<=len[u]-len[v]) ans=min(ans,dis[u]);
        for(int h=dep[u]-dep[v],i=0,node=u;h;h>>=1,i++) {
            if(h&1) mn=min(mn,fa_mn[node][i]), node=fa[node][i];
        }
        // cout<<"MN "<<mn<<" "<<len[u]<<endl;
        ans=min(ans,mn+len[u]);
        if(ans>1e14) puts("oo");
        else printf("%lld\n",ans);
    }
    return 0;
}
