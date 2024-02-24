#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,m,a[N],p[N],b[N],q[N];
ll sa[N],sb[N],s[N],t[N];
ll ans=0;
vector<PII> f[N];
map<int,ll> mp;
void Add(int x,ll y) {
    int v=x;
    for(auto i=mp.lower_bound(x);y<0&&i->first<=m;) {
        // if(i->first>m) cout<<i->first<<" "<<i->second<<" "<<y<<endl;
        v=i->first, y+=i->second;
        i=mp.erase(i);
    }
    if(y>=0) mp[v]+=y;
}
bool mem2;
int main() {
    freopen("chef.in","r",stdin);
    freopen("chef.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>s[i]>>p[i], sa[i]=sa[i-1]+a[i];
    for(int i=1;i<=m;i++) cin>>b[i]>>t[i]>>q[i], sb[i]=sb[i-1]+b[i];
    for(int i=1;i<=n;i++) if(sa[i]<=s[i]) {
        int j=upper_bound(sb+1,sb+m+1,s[i]-sa[i])-sb;
        ans+=p[i];
        f[i].emplace_back(j,-p[i]);
    }
    for(int j=1;j<=m;j++) if(sb[j]<=t[j]) {
        int i=upper_bound(sa+1,sa+n+1,t[j]-sb[j])-sa;
        if(i>n) { ans+=q[j]; continue; }
        f[i].emplace_back(j,+q[j]);
    }
    mp[m+1]=0x3f3f3f3f3f3f3f3f;
    for(int i=1;i<=n;i++) {
        sort(f[i].begin(),f[i].end(),[](const PII &x,const PII &y) { return x.second>y.second; });
        for(auto j:f[i]) Add(j.first,j.second);
    }
    for(auto i:mp) if(i.first<=m) ans+=i.second;
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}