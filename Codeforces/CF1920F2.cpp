#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e6+10;
bool mem1;
int n,m,Q,v[N];
int fx[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
string a[N];
vector<int> d[N];
int id(int x,int y,int f) { return f*n*m+(x-1)*m+y; }
int f[N],l[N],r[N],dep[N],fa[N][25];
int find(int x) {
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}
void dfs(int x) {
    if(l[x]) {
        dep[l[x]]=dep[r[x]]=dep[x]+1;
        dfs(l[x]), dfs(r[x]);
    }
}
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=0,h=dep[x]-dep[y];h;i++,h>>=1)
        if(h&1) x=fa[x][i];
    if(x==y) return x;
    for(int i=24;i>=0;i--)
        if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
    return fa[x][0];
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>Q;
    for(int i=1;i<=n;i++) cin>>a[i], a[i]=" "+a[i];
    queue<PII> q;
    int px=-1, py=-1;
    for(int i=1;i<=n;i++) {
        d[i].resize(m+1,0x3f3f3f3f);
        for(int j=1;j<=m;j++) {
            if(a[i][j]=='v') d[i][j]=0, q.emplace(i,j);
            if(a[i][j]=='#'&&j>py) px=i, py=j;
        }
    }
    while(q.size()) {
        PII now=q.front(); q.pop();
        int x=now.first, y=now.second;
        for(int k=0;k<4;k++) {
            int nx=x+fx[k][0], ny=y+fx[k][1];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m)
                if(d[nx][ny]>d[x][y]+1) {
                    d[nx][ny]=d[x][y]+1, q.emplace(nx,ny);
                }
        }
    }
    vector<pair<PII,int>> nd;
    for(int x=1;x<=n;x++)
        for(int y=1;y<=m;y++) if(a[x][y]!='#') {
            for(int k=0;k<=1;k++) {
               int nx=x+fx[k][0], ny=y+fx[k][1];
                if(nx>=1&&nx<=n&&ny>=1&&ny<=m) {
                    if(a[nx][ny]=='#') continue;
                    int f=(x==px-1&&nx==px&&y>py)? 1:0;
                    // cout<<x<<" "<<y<<" "<<nx<<" "<<ny<<" "<<f<<endl;
                    nd.push_back({{id(x,y,0),id(nx,ny,f^0)},min(d[x][y],d[nx][ny])});
                    nd.push_back({{id(x,y,1),id(nx,ny,f^1)},min(d[x][y],d[nx][ny])});
                }
            }
        }
    sort(nd.begin(),nd.end(),[](const pair<PII,int> &x,const pair<PII,int> &y) 
        { return x.second>y.second; });
    int tot=2*n*m;
    for(int i=1;i<=tot;i++) f[i]=i;
    for(auto i:nd) {
        PII now=i.first;
        int fx=find(now.first), fy=find(now.second);
        if(fx!=fy) {
            f[fx]=f[fy]=++tot, f[tot]=tot;
            v[tot]=i.second;
            l[tot]=fx, r[tot]=fy;
            fa[fx][0]=tot, fa[fy][0]=tot;
        }
    }
    for(int j=1;j<25;j++)
        for(int i=1;i<=tot;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
    dfs(tot);
    while(Q--) {
        int x,y; cin>>x>>y;
        // cout<<lca(id(x,y,0),id(x,y,1))<<endl;
        cout<<v[lca(id(x,y,0),id(x,y,1))]<<endl;
    }
    
    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}