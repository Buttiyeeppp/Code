#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll Mod=998244353;
bool mem1;
int n,m,dep[N];
ll f[N],sum[N];
vector<int> g[N],nd[N];
set<int> s[2];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        g[x].push_back(y), g[y].push_back(x);
    }
    for(int i=2;i<=n;i++) s[0].insert(i);
    nd[1].push_back(1); dep[1]=1;
    int d=1, op=0;
    while(s[op].size()) {
        for(auto i:nd[d]) {
            for(auto to:g[i]) if(!dep[to]) {
                s[op].erase(to), s[op^1].insert(to);
            }
            for(auto now:s[op]) dep[now]=d+1, nd[d+1].push_back(now);
            s[op].clear(), op^=1;
        }
        d++;
        if(nd[d].empty()) break;
    }
    f[1]=sum[1]=1;
    for(int i=2;i<=d;i++) {
        for(auto u:nd[i]) {
            f[u]=sum[i-1];
            for(auto to:g[u]) if(dep[to]==dep[u]-1) f[u]=(f[u]-f[to]+Mod)%Mod;
            sum[i]=(sum[i]+f[u])%Mod;
        }
    }
    cout<<(f[n]? f[n]:-1)<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}