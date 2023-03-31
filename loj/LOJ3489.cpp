#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls (id<<1)
#define rs (id<<1|1)
const int N=2.5e5+10;
int n,m,q,c[N];
struct SegmentTree {
    ll pos,sum,ans;
    SegmentTree operator+(const SegmentTree &q)const {
        SegmentTree p;
        p.pos=pos+q.pos, p.sum=sum+q.sum;
        p.ans=max(ans+q.sum,q.ans);
        return p;
    }
}T[N<<2];
vector<pair<int,ll> > mem[N], query[N];
void Modify(int id,int l,int r,int x,ll val) {
    if(l>x||r<x) return;
    if(l==r) {
        T[id].sum+=val;
        if(T[id].sum>0) T[id].pos=T[id].ans=T[id].sum;
        else T[id].pos=T[id].ans=0;
        return;
    }
    int mid=(l+r)>>1;
    Modify(ls,l,mid,x,val), Modify(rs,mid+1,r,x,val);
    T[id]=T[ls]+T[rs];
}
SegmentTree Query(int id,int l,int r,int x,int y) {
    if(x<=l&&y>=r) return T[id];
    int mid=(l+r)>>1;
    if(y<=mid) return Query(ls,l,mid,x,y);
    else if(x>=mid+1) return Query(rs,mid+1,r,x,y);
    return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
}
int find(int id,int l,int r,ll val) {
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(T[ls].pos<val) return find(rs,mid+1,r,val-T[ls].pos);
    return find(ls,l,mid,val);
}
int out[N];
int main() {
    scanf("%d%d%d",&n,&m,&q);
    int op,l,r; ll k;
    for(int i=1;i<=q;i++) {
        scanf("%d",&op);
        if(op==1) {
            scanf("%d%d%d%lld",&l,&r,&c[i],&k);
            mem[l].emplace_back(i,k);
            mem[r+1].emplace_back(i,-k);
        }
        else if(op==2) {
            scanf("%d%d%lld",&l,&r,&k);
            mem[l].emplace_back(i,-k);
            mem[r+1].emplace_back(i,k);
        }
        else {
            scanf("%d%lld",&l,&k);
            query[l].emplace_back(i,k);
        }
    }
    for(int t=1;t<=n;t++) {
        for(auto now:mem[t])
            Modify(1,1,q,now.first,now.second);
        for(auto now:query[t]) {
            SegmentTree res=Query(1,1,q,1,now.first);
            if(res.ans<now.second) {out[now.first]=-1; continue;}
            ll z=now.second+res.pos-res.ans;
            int fd=find(1,1,q,z);
            out[now.first]=c[fd];
        }
    }
    for(int i=1;i<=q;i++) {
        if(out[i]==0) continue;
        if(out[i]==-1) puts("0");
        else printf("%d\n",out[i]);
    }
    return 0;
}