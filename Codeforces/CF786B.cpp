#include <bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PLL=pair<ll,ll>;
const int N=1e5+10;
bool mem1;
int n,q,s,rt[2],pos[2][N],tot,ls[N<<4],rs[N<<4];
vector<PLL> g[N<<4];
void build(int &id,int l,int r,int op) {
    if(!id) id=++tot;
    if(l==r) return pos[op][l]=id, void();
    int mid=(l+r)>>1;
    build(ls[id],l,mid,op), build(rs[id],mid+1,r,op);
}
void rebuild(int id,int l,int r,int op) {
	if(l==r) return;
    if(!op) g[ls[id]].emplace_back(id,0), g[rs[id]].emplace_back(id,0);
    else g[id].emplace_back(ls[id],0), g[id].emplace_back(rs[id],0);
	int mid=(l+r)>>1;
	rebuild(ls[id],l,mid,op), rebuild(rs[id],mid+1,r,op);
}
void Modify(int id,int l,int r,int x,int y,int v,int w,int op) {
    if(x<=l&&y>=r) {
        if(!op) g[v].emplace_back(id,w);
        else g[id].emplace_back(v,w);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls[id],l,mid,x,y,v,w,op); 
    if(y>mid) Modify(rs[id],mid+1,r,x,y,v,w,op);
}
int vis[N<<4];
ll dis[N<<4];
void Dijkstra() {
    memset(dis,0x3f,sizeof(dis));
    priority_queue<PLL,vector<PLL>,greater<PLL>> q;
    dis[pos[0][s]]=0, q.emplace(0,pos[0][s]);
    while(q.size()) {
        int u=q.top().second; q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto to:g[u]) 
			if(dis[to.first]>dis[u]+to.second) {
				dis[to.first]=dis[u]+to.second, q.emplace(dis[to.first],to.first);
			}
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q>>s;
    build(rt[0],1,n,0), build(rt[1],1,n,1);
    rebuild(rt[0],1,n,0), rebuild(rt[1],1,n,1);
    for(int i=1,op,l,r,u,v,w;i<=q;i++) {
        cin>>op;
        if(op==1) {
            cin>>u>>v>>w;
            g[pos[0][u]].emplace_back(pos[1][v],w);
        }
        if(op==2) {
            cin>>u>>l>>r>>w;
            Modify(rt[1],1,n,l,r,pos[0][u],w,0);
        }
        if(op==3) {
            cin>>u>>l>>r>>w;
            Modify(rt[0],1,n,l,r,pos[1][u],w,1);
        }
    }
    for(int i=1;i<=n;i++) 
		g[pos[0][i]].emplace_back(pos[1][i],0), g[pos[1][i]].emplace_back(pos[0][i],0);
    Dijkstra();
	for(int i=1;i<=n;i++)
		cout<<(dis[pos[1][i]]==0x3f3f3f3f3f3f3f3f? -1:dis[pos[1][i]])<<" ";
	
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    return 0;
}