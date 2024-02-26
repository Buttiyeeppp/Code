#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const int N=3e5+10;
bool mem1;
int n,m,dep[N],p[N];
vector<int> eg[N];
vector<PII> g[N];
set<PLL> v[N];
ll lz[N];
void Insert(int x,PLL i) {
    i.first-=lz[x];
    auto p=v[x].lower_bound(i);
    if(p!=v[x].begin()) {
        p--;
        if((p->second)<i.second) return;
    }
    v[x].insert(i);
    for(auto p=v[x].upper_bound(i);p!=v[x].end()&&(p->second)>=i.second;v[x].erase(p),p=v[x].upper_bound(i));
}
int merge(int x,int y) {
    if(v[x].size()<v[y].size()) swap(x,y);
    for(auto i:v[y]) Insert(x,{i.first+lz[y],i.second});
    return x;
}
void dfs(int x,int from) {
    ll sum=0;
    dep[x]=dep[from]+1, p[x]=x;
    for(auto y:eg[x]) if(y!=from) {
        dfs(y,x);

        if(v[p[y]].empty()) { cout<<-1<<endl; exit(0); }
        ll g=v[p[y]].begin()->first+lz[p[y]];
        sum+=g, lz[p[y]]-=g;

        while(v[p[y]].size()) {
            auto it=v[p[y]].begin();
            if((it->second)>=dep[x]) v[p[y]].erase(it);
            else break;
        }
        if(v[p[y]].size()) p[x]=merge(p[x],p[y]);
    }
    for(auto i:g[x]) if(i.first!=x) {
        PLL v={i.second,dep[i.first]};
        Insert(p[x],v);
    }
    lz[p[x]]+=sum;
    if(x==1) cout<<sum<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        eg[x].push_back(y), eg[y].push_back(x);
    }
    for(int i=1,x,y,c;i<=m;i++) {
        cin>>x>>y>>c;
        g[x].emplace_back(y,c);
    }
    dfs(1,0);

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}