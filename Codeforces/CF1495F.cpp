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
int n,Q,p[N],b[N];
int nxt[N],st[N],top;
vector<PII> vc[N];
set<int> s;
ll ans[N],a[N];
void upd(int x,int t) {
    if(x==1) return;
    auto it=s.lower_bound(x);
    if(*it==x) { // Delete
        auto it1=it,it2=it;
        it1--, it2++, s.erase(it);
        vc[*it1].emplace_back(x,-t);
        vc[x].emplace_back(*it2,-t);
        vc[*it1].emplace_back(*it2,+t);
        // cerr<<"Delete "<<*it1<<" "<<x<<" "<<*it2<<" "<<t<<endl;
    }
    else {
        auto it1=it,it2=it;
        it1--, s.insert(x);
        vc[*it1].emplace_back(x,+t);
        vc[x].emplace_back(*it2,+t);
        vc[*it1].emplace_back(*it2,-t);
        // cerr<<"Add "<<*it1<<" "<<x<<" "<<*it2<<" "<<t<<endl;
    }
}
struct BIT {
    ll v[N];
    int lowbit(int x) { return x&-x; }
    void Add(int x,ll val) {
        for(int i=x;i<N;i+=lowbit(i)) v[i]+=val;
    }
    ll Qry(int x) {
        ll res=0;
        for(int i=x;i;i-=lowbit(i)) res+=v[i];
        return res;
    }
}bt;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>Q;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) cin>>a[i], a[i]+=a[i-1];
    for(int i=1;i<=n;i++) cin>>b[i];
    p[n+1]=INT_MAX, st[++top]=n+1;
    for(int i=n;i>=1;i--) {
        while(top&&p[st[top]]<=p[i]) top--;
        nxt[i]=st[top], st[++top]=i;
    }
    // for(int i=1;i<=n;i++) cout<<nxt[i]<<" "; cout<<endl;
    s.insert(1), s.insert(n+1);
    vc[1].emplace_back(n+1,1);
    for(int i=1,x;i<=Q;i++) { cin>>x; upd(x,i); }
    for(int i=n;i>=1;i--) {
        ll nv=b[i]-(a[nxt[i]-1]-a[i-1]),v=bt.Qry(nxt[i]-1);
        if(nv<v) bt.Add(nxt[i]-1,nv-v);
        for(auto now:vc[i]) {
            int f=1,x=now.second;
            if(x<0) x=-x,f=-f;
            ans[x]+=f*bt.Qry(now.first-1);
            // if(x==2) cerr<<i<<" "<<now.first<<" "<<f*bt.Qry(now.first-1)<<" "<<f<<endl;
        }
    }
    for(int i=1;i<=Q;i++) {
        ans[i]+=ans[i-1];
        cout<<ans[i]+a[n]<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}