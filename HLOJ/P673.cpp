#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define int long long
using ll=long long;
using PII=pair<int,int>;
const int N=4e5+10;
const int M=1e6+10;
const int INF=0x3f3f3f3f;
bool mem1;
int n,m,a[M],b[M],c[M];
vector<int> g[N];
int dfn[N],low[N],tim,st[N],top,col[N],cnt,dcnt;
void tarjan(int x) {
    dfn[x]=low[x]=++tim, st[++top]=x;
    for(auto y:g[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(!col[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]) {
        cnt++;
        while(st[top+1]!=x) {
            col[st[top--]]=cnt;
        }
    }
}
int head[N],lw[M],tot=1,v[N];
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
    return (dis[t]!=0x3f3f3f3f3f3f3f3f);
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
int sig[N];
bool mem2;
signed main() {
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        cin>>a[i]>>b[i]>>c[i];
        g[a[i]].push_back(b[i]);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    dcnt=cnt<<1, S=++dcnt, T=++dcnt;
    Addedge(T,S,INF);
    for(int i=1;i<=m;i++) {
        int x=col[a[i]],y=col[b[i]];
        if(x!=y) {
            int a=c[i], b=INF;
            Addedge(x+cnt,y,b-a);
            v[x+cnt]-=a, v[y]+=a;
        }
        else if(c[i]) sig[x]=1;
    }
    for(int i=1;i<=cnt;i++) {
        int a=sig[i], b=INF;
        Addedge(i,i+cnt,b-a);
        v[i]-=a, v[i+cnt]+=a;
    }
    for(int i=1;i<=cnt;i++) {
        Addedge(S,i,INF), Addedge(i+cnt,T,INF);
    }
    s=++dcnt, t=++dcnt;
    int ans=0;
    for(int i=1;i<=(cnt<<1);i++) if(v[i]!=0) {
        if(v[i]<0) Addedge(i,t,-v[i]);
        else Addedge(s,i,v[i]), ans-=v[i];
    }
    while(bfs(s,t)) ans+=dfs(s,INF,t);
    assert(ans==0);
    ans=eg[3].w, eg[2].w=eg[3].w=0;
    while(bfs(T,S)) ans-=dfs(T,INF,S);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}