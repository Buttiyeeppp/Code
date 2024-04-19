#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,k,a[N];
vector<int> eg[N];
struct node {
    int x,y;
    node operator+(const node& p) {
        return (node){x+p.x,y+p.y};
    }
    bool operator<(const node &p) {
        return (x==p.x)? y<p.y:x<p.x;
    }
};
node max(node x,node y) { return (y<x? x:y); }
node f[N][2];
void dfs(int x,int from) {
    f[x][a[x]&1]={0,a[x]}, f[x][(a[x]&1)^1]={INT_MIN,0};
    int res=0;
    for(auto y:eg[x]) if(y!=from) {
        dfs(y,x);
        res+=max(f[y][0].x,f[y][1].x);
        node v0=f[x][0],v1=f[x][1];
        f[x][0]=max(f[x][0],v0+f[y][0]), f[x][0]=max(f[x][0],v1+f[y][1]);
        f[x][1]=max(f[x][1],v1+f[y][0]), f[x][1]=max(f[x][1],v0+f[y][1]);
    }
    f[x][0]=max(f[x][0],{res,0});
    if(f[x][k&1].y>=k) f[x][0]=max(f[x][0],{f[x][k&1].x+1,0});
}
void solve() {
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i], eg[i].clear();
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        eg[x].push_back(y), eg[y].push_back(x);
    }
    dfs(1,0);
    cout<<max(f[1][0].x,f[1][1].x)<<endl;
}
bool mem2;
int main() {
    freopen("linkcut.in","r",stdin);
    freopen("linkcut.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}