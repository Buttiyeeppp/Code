#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
const int M=1e6+10;
const int INF=0x3f3f3f3f;
bool mem1;
int n,m,head[N],tot;
struct Edge {
    int to,nxt,w,col;
}eg[M<<1];
void Add(int x,int y,int w,int col) {
    eg[++tot]={y,head[x],w,col};
    head[x]=tot;
}
int dis[N],cur[N],vis[N],s,t;
bool bfs() {
    memcpy(cur,head,sizeof(cur));
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;
    queue<int> q; q.emplace(s);
    while(q.size()) {
        int x=q.front(); q.pop();
        vis[x]=0;
        for(int i=head[x];i;i=eg[i].nxt) {
            int y=eg[i].to;
            if(dis[y]>dis[x]+1&&eg[i].w) {
                dis[y]=dis[x]+1;
                if(!vis[y]) q.push(y), vis[y]=1;
            }
        }
    }
    return (dis[t]!=0x3f3f3f3f);
}
int dfs(int x,int flow) {
    if(x==t||!flow) return flow;
    int use=0;
    for(int i=cur[x];i&&flow;i=eg[i].nxt) {
        cur[x]=i;
        int y=eg[i].to;
        if(vis[y]||!eg[i].w||dis[y]!=dis[x]+1) continue;
        int c=dfs(y,min(flow,eg[i].w));
        if(!c) { vis[y]=1; continue; }
        eg[i].w-=c, eg[i^1].w+=c, use+=c, flow-=c;
    }
    return use;
}
int vi[N][2],vist[N][2],st[N],top;
bool find(int x,int f) {
    if(vist[x][f^1]) {
        while(1) {
            eg[st[top]].w^=1, eg[st[top]^1].w^=1;
            if(eg[st[top]^1].to==x) break;
            top--;
        }
        return true;
    }
    if(vi[x][f]) return false;
    vist[x][f]=1, vi[x][f]=1;
    for(int i=head[x];i;i=eg[i].nxt) if(eg[i].w) {
        int y=eg[i].to;
        st[++top]=i;
        if(find(y,f^eg[i].col)) return true;
        st[top--]=0;
    }
    vist[x][f]=0;
    return false;
}
void solve() {
    cin>>n>>m;
    s=2*n+1, t=2*n+2, tot=1;
    for(int i=1;i<=2*n+2;i++) head[i]=0;
    for(int i=1,x,y,c;i<=m;i++) {
        cin>>x>>y>>c;
        Add(x,y,1,c), Add(y,x,0,c);
    }
    for(int i=1;i<=n;i++) {
        Add(s,i,1,0), Add(i,s,0,0);
        Add(i+n,t,1,0), Add(t,i+n,0,0);
    }
    int flow=0;
    while(bfs()) flow+=dfs(s,INF);
    if(flow!=n) return cout<<-1<<endl, void();
    int cnt=0;
    for(int i=1;i<=m;i++) if(!eg[i*2].w) cnt+=eg[i*2].col;
    if(!(cnt&1)) {
        for(int i=1;i<=m;i++) if(!eg[i*2].w) cout<<i<<" ";
        cout<<endl;
        return;
    }
    memset(vi,0,sizeof(vis));
    memset(vist,0,sizeof(vist));
    memset(st,0,sizeof(st));
    top=0;
    for(int i=1;i<=n;i++) {
        if(find(i,0)) {
            for(int i=1;i<=m;i++) if(!eg[i*2].w) cout<<i<<" ";
            cout<<endl;
            return;
        }
    }
    cout<<-1<<endl;
}
bool mem2;
int main() {
    // freopen("t.in","r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}