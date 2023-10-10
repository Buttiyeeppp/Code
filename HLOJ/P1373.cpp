#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const int INF=1e7;
bool mem1;
int n,a[N],b[N],X[N],tot,v[N];
multiset<int> s;
namespace SegTree {
    int s[N<<2],lz[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void Build(int id,int l,int r) {
        if(l==r) return s[id]=v[l], void();
        int mid=(l+r)>>1;
        Build(ls,l,mid), Build(rs,mid+1,r);
        s[id]=max(s[ls],s[rs]);
    }
    void pushdown(int id) {
        if(!lz[id]) return;
        int v=lz[id]; lz[id]=0;
        s[ls]+=v, lz[ls]+=v;
        s[rs]+=v, lz[rs]+=v;
    }
    void Modify(int id,int l,int r,int x,int y,int v) {
        if(x<=l&&y>=r) return s[id]+=v, lz[id]+=v, void();
        int mid=(l+r)>>1;
        pushdown(id);
        if(x<=mid) Modify(ls,l,mid,x,y,v);
        if(y>mid) Modify(rs,mid+1,r,x,y,v);
        s[id]=max(s[ls],s[rs]);
    }
    int find1(int id,int l,int r,int lim,int v,int mx1) { // [1,pos-1]+1<=v && l>=lim
        if(l==r) return (mx1+1<=v)? l:0;
        int mid=(l+r)>>1;
        pushdown(id);
        if(mid<lim) return find1(rs,mid+1,r,lim,v,max(mx1,s[ls]));
        if(s[ls]+1<=v) return find1(rs,mid+1,r,lim,v,max(mx1,s[ls]));
        return find1(ls,l,mid,lim,v,mx1);
    }
    int find2(int id,int l,int r,int lim,int v,int mx1) { // [1,pos-1]+1<=v && r<=lim
        if(l==r) return (mx1+1<=v)? l:0;
        int mid=(l+r)>>1;
        pushdown(id);
        if(lim<=mid) return find2(ls,l,mid,lim,v,mx1);
        if(s[ls]+1<=v) return find2(rs,mid+1,r,lim,v,max(mx1,s[ls]));
        return find2(ls,l,mid,lim,v,mx1);
    }
    void out(int id,int l,int r) {
        if(l==r) return cout<<s[id]<<" ", void();
        pushdown(id);
        int mid=(l+r)>>1;
        out(ls,l,mid), out(rs,mid+1,r);
    }
}
int tmp;
/*
bool binary(int op,int l,int r) {
    int mem=l;
    multiset<int>::iterator mp;
    while(l+1<r) {
        int mid=(l+r)>>1;
        multiset<int>::iterator p=s.lower_bound(mid);
        if(p==s.end()) { r=mid; continue; }
        int val=*p;
        if(val>1) SegTree::Modify(1,1,tot,1,val-1,1);
        if(tmp==op+SegTree::s[1]) l=mid, mp=p;
        else r=mid;
        if(val>1) SegTree::Modify(1,1,tot,1,val-1,-1);
    }
    if(l>mem) {
        int val=*mp;
        cout<<X[val]<<" ";
        s.erase(mp);
        if(val>1) SegTree::Modify(1,1,tot,1,val-1,1);
        tmp-=op;
        return true;
    }
    return false;
}
*/
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i], X[++tot]=a[i];
    for(int i=1;i<=n;i++) cin>>b[i], X[++tot]=b[i];
    sort(X+1,X+tot+1), sort(b+1,b+n+1);
    tot=unique(X+1,X+tot+1)-X-1;
    for(int i=1;i<=n;i++) {
        a[i]=lower_bound(X+1,X+tot+1,a[i])-X;
        b[i]=lower_bound(X+1,X+tot+1,b[i])-X;
        v[a[i]]++, v[b[i]-1]--;
        s.insert(b[i]);
    }
    for(int i=tot-1;i>=1;i--) v[i]+=v[i+1];
    SegTree::Build(1,1,tot);
    tmp=SegTree::s[1];
    for(int i=1,p;i<=n;i++) {
        SegTree::Modify(1,1,tot,1,a[i],-1);
        multiset<int>::iterator it;
        if(a[i]+1<=tot&&(p=SegTree::find1(1,1,tot,a[i]+1,tmp,-INF))) {
            it=s.upper_bound(p);
            int val=*(--it);
            if(val>=a[i]+1) {
                if(val>1) SegTree::Modify(1,1,tot,1,val-1,1);
                cout<<X[val]<<" ";
                s.erase(it);
                continue;
            }
        }
        tmp--;
        p=SegTree::find2(1,1,tot,a[i],tmp,-INF);
        it=s.upper_bound(p);
        int val=*(--it);
        if(val>1) SegTree::Modify(1,1,tot,1,val-1,1);
        cout<<X[val]<<" ";
        s.erase(it);
    }
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}