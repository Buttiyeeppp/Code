#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,sz[N],dfn[N],tim,ind[N];
vector<int> eg[N];
int hs(int x,int y) { return (x-1)*m+y; }
void Addedge(int x,int y) {
    ind[y]++;
    eg[x].push_back(y);
}
string a[N];
void dfs(int x) {
    sz[x]=1, dfn[x]=++tim;
    for(auto y:eg[x]) {
        dfs(y);
        sz[x]+=sz[y];
    }
}
struct Operation {
    int l,r,op;
};
vector<Operation> opt[N];
void Add(int x,int y) {
    opt[dfn[x]].push_back({dfn[y],dfn[y]+sz[y]-1,1});
    opt[dfn[x]+sz[x]].push_back({dfn[y],dfn[y]+sz[y]-1,-1});
}
struct SegmentTree {
    ll v[N<<2],s[N<<2],lz[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void update(int id,int l,int r) {
        if(v[id]) s[id]=r-l+1;
        else {
            if(l!=r) s[id]=s[ls]+s[rs];
            else s[id]=0;
        }
    }
    void Modify(int id,int l,int r,int x,int y,ll val) {
        if(x<=l&&y>=r) {
            v[id]+=val;
            update(id,l,r);
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,y,val);
        if(y>mid) Modify(rs,mid+1,r,x,y,val);
        update(id,l,r);
    }
}sg;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i], a[i]=" "+a[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            if(j<m&&a[i][j]=='L'&&a[i][j+1]=='R') {
                if(j+2<=m) Addedge(hs(i,j+2),hs(i,j));
                if(j-1>=1) Addedge(hs(i,j-1),hs(i,j+1));
            }
            if(i<n&&a[i][j]=='U'&&a[i+1][j]=='D') {
                if(i+2<=n) Addedge(hs(i+2,j),hs(i,j));
                if(i-1>=1) Addedge(hs(i-1,j),hs(i+1,j));
            }
        }
    for(int i=1;i<=n*m;i++) if(!ind[i]) dfs(i);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            if(j<m&&a[i][j]=='L'&&a[i][j+1]=='R') {
                if((i&1)==(j&1)) Add(hs(i,j),hs(i,j+1));
                else Add(hs(i,j+1),hs(i,j));
            }
            if(i<n&&a[i][j]=='U'&&a[i+1][j]=='D') {
                if((i&1)==(j&1)) Add(hs(i,j),hs(i+1,j));
                else Add(hs(i+1,j),hs(i,j));
            }
        }
    ll ans=0;
    for(int i=1;i<=n*m;i++) {
        for(auto q:opt[i]) sg.Modify(1,1,n*m,q.l,q.r,q.op);
        ans+=sg.s[1];
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}