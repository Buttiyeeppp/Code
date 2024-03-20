#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define fi first
#define se second
using ll=long long;
using PLL=pair<ll,ll>;
const int N=4e5+10;
bool mem1;
ll n,q,a[N],X[N],tot,z,m;
struct node {
    ll cnt,s1,s2; // 个数，x[i], i*x[i]
    node() { cnt=s1=s2=0; }
    friend node operator+(const node &x,const node &y) {
        node res;
        res.cnt=x.cnt+y.cnt;
        res.s1=x.s1+y.s1;
        res.s2=x.s2+y.s2+y.s1*x.cnt;
        return res;
    }
};
struct SegmentTree {
    node d[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void Modify(int id,int l,int r,int x,int f) {
        if(l==r) {
            d[id].cnt+=f;
            d[id].s1=d[id].cnt*X[x];
            d[id].s2=(1+d[id].cnt)*d[id].cnt/2*X[x];
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,f);
        else Modify(rs,mid+1,r,x,f);
        d[id]=d[ls]+d[rs];
    }
    node Query(int id,int l,int r,ll x) {
        if(l==r) {
            ll tot=min((ll)x,d[id].cnt);
            node res;
            res.cnt=tot;
            res.s1=tot*X[l];
            res.s2=(1+tot)*tot/2*X[l];
            return res; 
        }
        int mid=(l+r)>>1;
        if(d[ls].cnt<x) return d[ls]+Query(rs,mid+1,r,x-d[ls].cnt);
        return Query(ls,l,mid,x);
    }
}t;
struct Operation {
    ll op,x;
}opt[N];
ll F(ll x) {
    return t.Query(1,1,tot,x+1).s1-(z-t.Query(1,1,tot,m-x).s1);
}
void upd(ll x,int f) {
    m+=f, z+=f*x;
    int p=lower_bound(X+1,X+tot+1,x)-X;
    t.Modify(1,1,tot,p,f);
}
ll calc() {
    int l=0, r=m/2;
    while(l+1<r) {
        int mid=(l+r)>>1;
        if(F(mid)>=0) l=mid;
        else r=mid;
    }
    if(m<=1) return 0;
    node r1=t.Query(1,1,tot,l+1), r2=t.Query(1,1,tot,m-l), r3=t.Query(1,1,tot,m);
    ll res=(l+2)*r1.s1-r1.s2+((m-l)*r3.s1-r3.s2)-((m-l)*r2.s1-r2.s2);
    res<<=1;
    if(m&1) res+=max(0ll,F(m/2));
    return z-res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i], X[++tot]=a[i];
    for(int i=1;i<=q;i++) cin>>opt[i].op>>opt[i].x, X[++tot]=opt[i].x;
    sort(X+1,X+tot+1);
    tot=unique(X+1,X+tot+1)-X-1;
    for(int i=1;i<=n;i++) upd(a[i],+1);
    cout<<calc()<<endl;
    for(int i=1;i<=q;i++) {
        upd(opt[i].x,((opt[i].op==1)? +1:-1));
        cout<<calc()<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}