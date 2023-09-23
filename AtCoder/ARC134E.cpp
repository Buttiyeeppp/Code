#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=998244353;
bool mem1;
int n,m,a[N];
vector<int> v[500];
bool dfs(vector<int> val) {
    if(!val.size()) return true;
    if(val.size()==1&&val[0]<=2) return false;
    for(int i=1;i<=val.back();i++) {
        vector<int> now;
        for(auto v:val)
            if(v%i) now.push_back(v%i);
        sort(now.begin(),now.end());
        now.erase(unique(now.begin(),now.end()),now.end());
        if(!dfs(now)) return true;
    }
    return false;
}
ll f[N],g[N];
void Add(ll &x,ll y) {
    return x=(x+y>=Mod? x+y-Mod:x+y), void();
}
ll calc(int x) {
    int l=v[x].size();
    if(l>n) return 0;
    memset(f,0,sizeof(f));
    f[0]=1;
    for(int i=1;i<=n;i++) {
        for(int s=0;s<(1<<l);s++) g[s]=0;
        for(int s=0;s<(1<<l);s++) 
            for(int j=0;j<l;j++) if(a[i]>=v[x][j])
                Add(g[s|(1<<j)],f[s]);
        for(int s=0;s<(1<<l);s++) f[s]=g[s];
    }
    return f[(1<<l)-1];
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    v[++m].push_back(1), v[++m].push_back(2);
    v[++m].push_back(4), v[m].push_back(8);
    int k=200/12;
    for(int s=0;s<(1<<k);s++) {
        vector<int> val;
        for(int i=0;i<k;i++) if((1<<i)&s) val.push_back(12*(i+1));
        if(!dfs(val)) v[++m]=val;
    }
    cin>>n;
    ll ans=1;
    for(int i=1;i<=n;i++) cin>>a[i], ans=ans*a[i]%Mod;
    for(int i=1;i<=m;i++) Add(ans,(Mod-calc(i))%Mod);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}