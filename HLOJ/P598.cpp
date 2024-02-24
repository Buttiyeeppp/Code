#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const int M=152;
bool mem1;
int n,m,a[M][M],w[M][M],h[M][M],l[M][M],tot,head[N],cnt=1;
int id(int x,int y) { return (x-1)*m+y; }
struct Edge {
    int to,nxt,w,c;
}eg[N];
void Addedge(int x,int y,int w,int c) {
    // cout<<"Addedge "<<x<<" "<<y<<" "<<w<<" "<<c<<endl;
    eg[++cnt]={y,head[x],w,+c}, head[x]=cnt;
    eg[++cnt]={x,head[y],0,-c}, head[y]=cnt;
}
int st,ed;
int dis[N],cur[N],vis[N];
bool bfs() {
    memcpy(cur,head,sizeof(cur));
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(st), dis[st]=0, vis[st]=1;
    while(q.size()) {
        int x=q.front(); q.pop();
        vis[x]=0;
        for(int i=head[x];i;i=eg[i].nxt) {
            int y=eg[i].to;
            if(eg[i].w&&dis[y]>dis[x]+eg[i].c) {
                dis[y]=dis[x]+eg[i].c;
                if(!vis[y]) q.push(y), vis[y]=1;
            }
        }
    }
    return (dis[ed]!=0x3f3f3f3f);
}
int dfs(int x,int f) {
    if(x==ed||!f) return f;
    vis[x]=1;
    int flow=0;
    for(int i=cur[x];i&&f;i=eg[i].nxt) {
        cur[x]=i;
        int y=eg[i].to;
        if(vis[y]||!eg[i].w||dis[y]!=dis[x]+eg[i].c) continue;
        int c=dfs(y,min(f,eg[i].w));
        if(!c) {vis[y]=1; continue;}
        f-=c, eg[i].w-=c, eg[i^1].w+=c, flow+=c;
    }
    return flow;
}
bool mem2;
int main() {
    freopen("puzzle.in","r",stdin);
    freopen("puzzle.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin>>a[i][j];
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            cin>>w[i][j];
            if(!a[i][j]) ans+=w[i][j];
        }
    tot=n*m;
    st=++tot, ed=++tot;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) if(!a[i][j]) h[i][j]=++tot, l[i][j]=++tot;
    int d1=0, d2=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) if(!a[i][j]) {
            if((i&1)==(j&1)) {
                Addedge(st,id(i,j),2,0), d1++;

                Addedge(id(i,j),h[i][j],1,0);
                Addedge(id(i,j),h[i][j],1,w[i][j]);
                if(i>1&&!a[i-1][j]) Addedge(h[i][j],h[i-1][j],1,0);
                if(i<n&&!a[i+1][j]) Addedge(h[i][j],h[i+1][j],1,0);

                Addedge(id(i,j),l[i][j],1,0);
                Addedge(id(i,j),l[i][j],1,w[i][j]);
                if(j>1&&!a[i][j-1]) Addedge(l[i][j],l[i][j-1],1,0);
                if(j<m&&!a[i][j+1]) Addedge(l[i][j],l[i][j+1],1,0);
            }
            else {
                Addedge(id(i,j),ed,2,0), d2++;

                Addedge(h[i][j],id(i,j),1,0);
                Addedge(h[i][j],id(i,j),1,w[i][j]);

                Addedge(l[i][j],id(i,j),1,0);
                Addedge(l[i][j],id(i,j),1,w[i][j]);
            }
        }
    int res=0;
    while(bfs()) {
        int c=dfs(st,INT_MAX);
        ans-=c*dis[ed], res+=c;
    }
    cout<<((d1!=d2||res!=d1*2)? -1:ans)<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}