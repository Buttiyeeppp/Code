#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const int M=8e5+10;
bool mem1;
int n,m,vis[N];
ll dis[N];
struct Edge {
    int x,y,a;
}eg[M];
vector<PII> g[N];
void dij() {
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    priority_queue<PII,vector<PII>,greater<PII>> q;
    dis[1]=0, q.emplace(0,1);
    while(q.size()) {
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(auto to:g[x]) {
            int y=to.first;
            if(dis[y]>dis[x]+to.second)
                dis[y]=dis[x]+to.second, q.emplace(dis[y],y);
        }
    }
}
int fa[N<<2],fat[N<<2][20],v[N<<2];
ll d[N<<2];
int find(int x) {
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
void solve() {
    cin>>n>>m;
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1,x,y,l,a;i<=m;i++) {
        cin>>x>>y>>l>>a;
        g[x].emplace_back(y,l), g[y].emplace_back(x,l);
        eg[i]={x,y,a};
    }
    dij();
    sort(eg+1,eg+m+1,[](const Edge &q,const Edge &p){ return q.a>p.a; });
    for(int i=1;i<=n;i++) fa[i]=i, d[i]=dis[i];
    int tot=n;
    for(int i=1;i<=m;i++) {
        int x=find(eg[i].x), y=find(eg[i].y);
        if(x==y) continue;
        fat[x][0]=fat[y][0]=fa[x]=fa[y]=++tot, fa[tot]=tot;
        v[tot]=eg[i].a, d[tot]=min(d[x],d[y]);
    }
    for(int j=1;j<20;j++)
        for(int i=1;i<=tot;i++) fat[i][j]=fat[fat[i][j-1]][j-1];
    int q,k,s;
    cin>>q>>k>>s;
    for(int i=1,lst=0,x,p;i<=q;i++) {
        cin>>x>>p;
        x=(x+k*lst-1)%n+1, p=(p+k*lst)%(s+1);
        for(int j=19;j>=0;j--) if(fat[x][j]&&v[fat[x][j]]>p) {
            x=fat[x][j];
        }
        cout<<d[x]<<endl;
        lst=d[x];
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}