#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=2e3+10;
bool memory1;
int n,q,fa[N],deg[N];
vector<int> eg[N];
void dfs(int x,int from) {
    fa[x]=from;
    for(auto y:eg[x]) if(y!=from) dfs(y,x);
}
void solve() {
    cin>>n>>q;
    for(int i=1;i<=n;i++) eg[i].clear(),deg[i]=0;
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        eg[x].push_back(y),eg[y].push_back(x);
        deg[x]++,deg[y]++;
    }
    dfs(1,0);
    for(int i=1,x,p;i<=q;i++) {
        cin>>x>>p;
        ll ans=0,f=0;
        priority_queue<int> q;
        while(x!=1) {
            if(f) q.push(2ll*(deg[x]-1)),ans+=2ll*(deg[x]-1);
            x=fa[x],f^=1,ans++;
        }
        while(q.size()&&p) p--,ans-=q.top(),q.pop();
        cout<<ans<<endl;
    }
}
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}