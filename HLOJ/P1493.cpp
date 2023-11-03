#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const int N=1e5+10;
bool mem1;
ll T,n,m,a[N];
ll _gcd(ll x,ll y) {
    if(!x) return y;
    return _gcd(y%x,x);
}
ll _lcm(ll x,ll y) { return x/_gcd(x,y)*y; }
const int V=1e9;
struct Segt {
    vector<PLL> vl,vr;
    int len;
    Segt() { len=0; }
    void init(int val) {
        vl.clear(), vr.clear();
        vl.push_back({val,1});
        vr.push_back({val,1});
        len=1;
    }
    friend Segt operator+(const Segt &x,const Segt &y) {
        Segt res;
        res.len=x.len+y.len;
        vector<PLL> L,R;
        for(auto i:x.vl) L.push_back(i);
        PII now=L.back();
        if(now.second==x.len) {
            for(auto i:y.vl) {
                ll val=_lcm(now.first,i.first);
                if(val>V) break;
                L.push_back({val,x.len+i.second});
            }
        }
        for(int i=L.size()-1;i>=0;i--)
            if(res.vl.empty()||res.vl.back().first!=L[i].first) res.vl.push_back(L[i]);
        reverse(res.vl.begin(),res.vl.end());

        for(auto i:y.vr) R.push_back(i);
        now=R.back();
        if(now.second==y.len) {
            for(auto i:x.vr) {
                ll val=_lcm(now.first,i.first);
                if(val>V) break;
                R.push_back({val,y.len+i.second});
            }
        }
        for(int i=R.size()-1;i>=0;i--)
            if(res.vr.empty()||res.vr.back().first!=R[i].first) res.vr.push_back(R[i]);
        reverse(res.vr.begin(),res.vr.end());

        return res;
    }
}s[N<<2],emp;
#define ls (id<<1)
#define rs (id<<1|1)
map<int,ll> mp;
void upd(const Segt &l,const Segt &r,int f) {
    for(int i=0;i<(int)l.vr.size();i++)
        for(int j=0;j<(int)r.vl.size();j++) {
            ll l1=l.vr[i].second-(i? l.vr[i-1].second:0),
               l2=r.vl[j].second-(j? r.vl[j-1].second:0),
               val=_lcm(l.vr[i].first,r.vl[j].first);
            if(val>V) break;
            mp[val]+=f*l1*l2;
        }
}
void Build(int id,int l,int r) {
    if(l==r) return mp[a[l]]++, s[id].init(a[l]);
    int mid=(l+r)>>1;
    Build(ls,l,mid), Build(rs,mid+1,r);
    upd(s[ls],s[rs],1);
    s[id]=s[ls]+s[rs];
}
Segt Query(int id,int l,int r,int x,int y) {
    if(x>y) return emp;
    if(x<=l&&y>=r) return s[id];
    int mid=(l+r)>>1;
    if(y<=mid) return Query(ls,l,mid,x,y);
    if(x>mid) return Query(rs,mid+1,r,x,y);
    return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
}
void Modify(int id,int l,int r,int x,int val){
    if(l==r) return s[id].init(val);
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls,l,mid,x,val);
    else Modify(rs,mid+1,r,x,val);
    s[id]=s[ls]+s[rs];
}
void change(int x,int f) {
    Segt l=Query(1,1,n,1,x-1);
    Segt r=Query(1,1,n,x+1,n);
    Segt v; v.init(a[x]);
    if(r.len) v=v+r;
    for(int i=0;i<(int)v.vl.size();i++) {
        ll l1=v.vl[i].second-(i? v.vl[i-1].second:0);
        mp[v.vl[i].first]+=f*l1;
    }
    upd(l,v,f);
}
bool mem2;
int main() {
    freopen("cu.in","r",stdin);
    freopen("cu.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>T>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    Build(1,1,n);
    for(int i=1,op,x,y;i<=m;i++) {
        cin>>op;
        if(op==1) {
            cin>>x>>y;
            change(x,-1);
            Modify(1,1,n,x,y); a[x]=y;
            change(x,+1);
        }
        else cin>>x, cout<<mp[x]<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}