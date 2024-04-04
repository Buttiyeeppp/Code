#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e4+10;
const int M=4e5;
const int INF=0x3f3f3f3f;
bool mem1;
int n,m,head[N],low[M],tot=1,v[N];
struct Edge {
    int nxt,to,w;
}eg[M];
void Addedge(int x,int y,int w) {
    eg[++tot]={head[x],y,w}, head[x]=tot;
    eg[++tot]={head[y],x,0}, head[y]=tot;
}
int cur[N],vis[N],dis[N];
bool bfs(int s,int t) {
    memcpy(cur,head,sizeof(cur));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    q.push(s), dis[s]=0, vis[s]=1;
    while(q.size()) {
        int x=q.front(); q.pop();
        vis[x]=0;
        for(int i=head[x];i;i=eg[i].nxt) {
            int y=eg[i].to;
            if(eg[i].w&&dis[y]>dis[x]+1) {
                dis[y]=dis[x]+1;
                if(!vis[y]) q.push(y), vis[y]=1;
            }
        }
    }
    return (dis[t]!=INF);
}
int dfs(int x,int flow,int t) {
    if(x==t||!flow) return flow;
    int use=0;
    for(int i=cur[x];i&&flow;i=eg[i].nxt) {
        cur[x]=i;
        int y=eg[i].to;
        if(vis[y]||!eg[i].w||dis[y]!=dis[x]+1) continue;
        int c=dfs(y,min(flow,eg[i].w),t);
        if(!c) { vis[y]=1; continue; }
        flow-=c, use+=c, eg[i].w-=c, eg[i^1].w+=c;
    }
    return use;
}
int S,T,s,t;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>S>>T;
    Addedge(T,S,INF);
    for(int i=1,x,y,a,b;i<=m;i++) {
        cin>>x>>y>>a>>b;
        low[i]=a, Addedge(x,y,b-a);
        v[x]-=a, v[y]+=a;
    }
    s=n+1, t=n+2;
    int ans=0;
    for(int i=1;i<=n;i++) if(v[i]!=0) {
        if(v[i]<0) Addedge(i,t,-v[i]);
        else Addedge(s,i,v[i]), ans-=v[i];
    }
    while(bfs(s,t)) ans+=dfs(s,INF,t);
    if(ans) return cout<<"please go home to sleep"<<endl, 0;
    ans=eg[3].w, eg[2].w=eg[3].w=0;
    while(bfs(T,S)) ans-=dfs(T,INF,S);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}