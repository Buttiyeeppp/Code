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
int n,m,a[N],b[N];
vector<PII> seg[N],v[N];
ll f[N];
namespace Segt {
    ll v[N<<2],lz[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void pushdown(int id) {
        if(!lz[id]) return;
        ll val=lz[id]; lz[id]=0;
        v[ls]+=val, lz[ls]+=val;
        v[rs]+=val, lz[rs]+=val;
    }
    void Modify(int id,int l,int r,int x,int y,ll val) {
        if(x<=l&&y>=r) return v[id]+=val, lz[id]+=val, void();
        int mid=(l+r)>>1;
        pushdown(id);
        if(x<=mid) Modify(ls,l,mid,x,y,val);
        if(y>mid) Modify(rs,mid+1,r,x,y,val);
        v[id]=max(v[ls],v[rs]);
    }
    ll Query(int id,int l,int r,int x,int y) {
        if(x<=l&&y>=r) return v[id];
        pushdown(id);
        int mid=(l+r)>>1;
        if(y<=mid) return Query(ls,l,mid,x,y);
        if(x>mid) return Query(rs,mid+1,r,x,y);
        return max(Query(ls,l,mid,x,y),Query(rs,mid+1,r,x,y));
    }
}
bool mem2;
int main() {
    freopen("attack.in","r",stdin);
    freopen("attack.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,l,r,x,y;i<=m;i++) {
        cin>>l>>r>>x>>y;
        seg[l].emplace_back(l-1,-y);
        seg[r+1].emplace_back(l-1,y);
        v[l].emplace_back(x,1), v[r+1].emplace_back(x,0);
    }
    multiset<int> st;
    for(int i=1;i<=n;i++) {
        for(auto now:v[i]) {
            // cerr<<now.first<<" "<<now.second<<endl;
            if(now.second) st.insert(-now.first);
            else st.erase(st.find(-now.first));
        }
        if(st.size()) b[i]=-(*st.begin());
    }
    for(int i=1;i<=n;i++) {
        for(auto now:seg[i]) Segt::Modify(1,0,n,0,now.first,now.second);
        f[i]=Segt::Query(1,0,n,0,i-1)+b[i];
        Segt::Modify(1,0,n,i,i,f[i]);
        Segt::Modify(1,0,n,0,i-1,-a[i]);
    }
    ll ans=-1e18,z=0;
    for(int i=n;i>=1;i--) {
        ans=max(ans,f[i]+z);
        z-=a[i];
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}