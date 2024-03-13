#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll INF=1e15;
bool mem1;
int n,m,q[N],p[N];
ll w[N],k,f[N];
ll calc(int x,int v) {
    if(x>=m) return f[x]=(q[x]>=v)? 0:INF;
    ll ls=calc(x<<1,v), rs=calc(x<<1|1,v);
    f[x]=ls+min(rs,w[x]);
    return f[x];
}
vector<ll> val[N];
pair<ll,vector<int>> sol(int rt,ll k) {
    // cout<<"Sol "<<rt<<" "<<k<<endl;
    int l=0,r=val[rt].size();
    while(l+1<r) {
        int mid=(l+r)>>1;
        if(calc(rt,val[rt][mid])<=k) l=mid;
        else r=mid;
    }
    l=val[rt][l];
    calc(rt,l);
    ll use=0;
    int x=p[l];
    while(x!=rt) {
        // cout<<x<<endl;
        if(x&1) use+=f[x^1];
        else use+=min(f[x^1],w[x>>1]);
        x>>=1;
    }
    vector<int> ans;
    ans.push_back(l);
    x=p[l];
    while(x!=rt) {
        if(x&1) use-=f[x^1];
        else use-=min(f[x^1],w[x>>1]);
        pair<ll,vector<int>> res=sol(x^1,k-use);
        if(res.second[0]<l) use+=w[x>>1], res=sol(x^1,k-use);
        use+=res.first, x>>=1;
        for(auto i:res.second) ans.push_back(i);
    }
    return {use,ans};
}
void solve() {
    cin>>n>>k;
    m=1<<n;
    for(int i=1;i<m;i++) cin>>w[i];
    for(int i=m;i<=2*m-1;i++) cin>>q[i], p[q[i]]=i;

    for(int i=m;i<=2*m-1;i++) val[i].clear(), val[i].push_back(q[i]);
    for(int i=m-1;i>=1;i--) {
        val[i]=val[i<<1];
        for(auto j:val[i<<1|1]) val[i].push_back(j);
        sort(val[i].begin(),val[i].end());
    }

    vector<int> ans=sol(1,k).second;
    for(auto i:ans) cout<<i<<" ";
    cout<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}