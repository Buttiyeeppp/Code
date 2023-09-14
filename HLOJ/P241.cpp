#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=1e9+7;
bool mem1;
int n,m,deg[N];
ll cnt[N],tot[N],a[N];
vector<int> g[N],eg[N];
bool mem2;
int main() {
    // freopen("3.in","r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        g[x].push_back(y), g[y].push_back(x);
        deg[x]++, deg[y]++;
    }
    for(int x=1;x<=n;x++) 
        for(auto y:g[x]) 
            if(deg[x]<deg[y]||(deg[x]==deg[y]&&x<y)) eg[x].push_back(y);
    ll ans=0;
    for(int i=1;i<=n;i++) {
        for(auto j:g[i]) for(auto k:eg[j]) if(k!=i)
            if(deg[i]<deg[k]||(deg[i]==deg[k]&&i<k)) {
                // cerr<<i<<" "<<j<<" "<<k<<endl;
                ans=(ans+cnt[k]+a[j]*tot[k])%Mod;
                cnt[k]=(cnt[k]+a[i]+a[j]+a[k])%Mod, tot[k]++;
            }
        for(auto j:g[i]) for(auto k:eg[j]) cnt[k]=0, tot[k]=0;
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}