#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define fi first
#define se second
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,lim,a[N],b[N],q;
struct SegmentTree {
    struct node {
        vector<PII> lv,rv;
        int ans,mx;
        node() { ans=INT_MAX, mx=0; }
        friend node operator+(const node &x,const node &y) {
            node res;
            res.ans=min(x.ans,y.ans);
            res.mx=max(x.mx,y.mx);
            int p=0;
            for(int i=y.lv.size()-1;i>=0;i--) {
                while(p<(int)x.rv.size()&&(y.lv[i].fi|x.rv[p].fi)<lim) p++;
                if(p<(int)x.rv.size()) res.ans=min(res.ans,max(y.lv[i].se,x.rv[p].se));
            }
            res.lv=x.lv, res.rv=y.rv;
            PII now={x.lv.back().fi,x.mx};
            for(auto i:y.lv) {
                if((now.fi|i.fi)!=now.fi) {
                    now={now.fi|i.fi,max(now.se,i.se)};
                    res.lv.push_back(now);
                }
            }
            now={y.rv.back().fi,y.mx};
            for(auto i:x.rv) {
                if((now.fi|i.fi)!=now.fi) {
                    now={now.fi|i.fi,max(now.se,i.se)};
                    res.rv.push_back(now);
                }
            }
            return res;
        }
    }d[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void Build(int id,int l,int r) {
        if(l==r) {
            d[id].lv.clear(), d[id].rv.clear(), d[id].ans=INT_MAX;
            d[id].mx=a[l];
            d[id].lv.emplace_back(b[l],a[l]);
            d[id].rv.emplace_back(b[l],a[l]);
            if(b[l]>=lim) d[id].ans=a[l];
            return;
        }
        int mid=(l+r)>>1;
        Build(ls,l,mid), Build(rs,mid+1,r);
        d[id]=d[ls]+d[rs];
    }
    void Modify(int id,int l,int r,int x,int v) {
        if(l==r) {
            b[l]=v;
            d[id].lv.clear(), d[id].rv.clear(), d[id].ans=INT_MAX;
            d[id].lv.emplace_back(b[l],a[l]);
            d[id].rv.emplace_back(b[l],a[l]);
            if(b[l]>=lim) d[id].ans=a[l];
            return;            
        }
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,v);
        else Modify(rs,mid+1,r,x,v);
        d[id]=d[ls]+d[rs];
    }
    node Query(int id,int l,int r,int x,int y) {
        if(x<=l&&y>=r) return d[id];
        int mid=(l+r)>>1;
        if(y<=mid) return Query(ls,l,mid,x,y);
        if(x>mid) return Query(rs,mid+1,r,x,y);
        return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
    }
    void Modify(int x,int v) { Modify(1,1,n,x,v); }
    int Query(int x,int y) { return Query(1,1,n,x,y).ans; }
}t;
void solve() {
    cin>>n>>lim;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    t.Build(1,1,n);
    cin>>q;
    for(int i=1,op,l,r;i<=q;i++) {
        cin>>op>>l>>r;
        if(op==1) t.Modify(l,r);
        else {
            int res=t.Query(l,r);
            cout<<((res==INT_MAX)? -1:res)<<" ";
        }
    }
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