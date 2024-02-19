#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLI=pair<ll,int>;
const int N=1e6+10;
bool mem1;
int n,fa[N][20],dep[N],Log[N],pos[N][20];
ll val[N];
int sz[N],son[N],top[N];
vector<int> eg[N];
void dfs(int x,int from) {
    dep[x]=dep[from]+1, sz[x]=1;
    fa[x][0]=from, pos[x][0]=x;
    for(int j=1;j<20;j++) {
        fa[x][j]=fa[fa[x][j-1]][j-1];
        pos[x][j]=(val[pos[x][j-1]]>val[pos[fa[x][j-1]][j-1]])? pos[x][j-1]:pos[fa[x][j-1]][j-1];
    }
    for(auto y:eg[x]) if(y!=from) {
        dfs(y,x);
        sz[x]+=sz[y];
        if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
    }
}
void dfs1(int x,int from) {
    if(son[x]) top[son[x]]=top[x], dfs1(son[x],x);
    for(auto y:eg[x]) if(y!=from&&y!=son[x]) {
        top[y]=y, dfs1(y,x);
    }
}
int jump(int x,int v) {
    for(int i=0;v;i++,v>>=1)
        if(v&1) x=fa[x][i];
    return x;
}
int qpos(int x,int y) {
    int len=dep[x]-dep[y]+1, lg=Log[len], jp=dep[x]-dep[y]+1-(1<<lg);
    int nx=jump(x,jp);
    return (val[pos[x][lg]]>val[pos[nx][lg]])? pos[x][lg]:pos[nx][lg];
}
vector<PII> seg;
priority_queue<PLI> q;
void insert(int x,int y) {
    q.emplace(val[qpos(x,y)],seg.size());
    seg.emplace_back(x,y);
}
void lca(int x,int y) {
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        insert(x,top[x]), x=fa[top[x]][0];
    }
    if(dep[x]>dep[y]) swap(x,y);
    insert(y,x);
}
vector<ll> c;
ll nxt() {
    if(q.empty()) return 0;
    ll val=q.top().first;
    int id=q.top().second; q.pop();
    int a=seg[id].first, b=seg[id].second;
    int p=qpos(a,b);
    if(dep[p]<dep[a]) insert(a,son[p]);
    if(dep[b]<dep[p]) insert(fa[p][0],b);
    return val;
}
ll sol(int x,int y,int m) {
    seg.clear(), c.clear();
    while(q.size()) q.pop();
    lca(x,y);
    int pd=1;
    ll ans=0;
    for(ll i=61;i>=0;i--) {
        int cnt=0;
        for(auto j:c) if((1ll<<i)&j) cnt++;
        while(cnt<m&&pd) {
            ll val=nxt();
            if((val&ans)!=ans) { pd=0; break; }
            c.push_back(val);
            if((1ll<<i)&val) cnt++;
            else break;
        }
        if(cnt>=m) {
            ans+=(1ll<<i);
            vector<ll> nc;
            for(auto j:c) if((1ll<<i)&j) nc.push_back(j);
            c=nc;
        }
    }
    return ans;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for(int i=2;i<N;i++) Log[i]=Log[i>>1]+1;
    cin>>n;
    for(int i=1,x,y;i<n;i++) 
        cin>>x>>y, eg[x].push_back(y), eg[y].push_back(x);
    for(int i=1;i<=n;i++) cin>>val[i];
    top[1]=1, dfs(1,0), dfs1(1,0);
    ll Q,lst=0,x,y,m; cin>>Q;
    while(Q--) {
        cin>>x>>y>>m;
        x=(x^lst)%n+1, y=(y^lst)%n+1;
        lst=sol(x,y,m);
        cout<<lst<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}