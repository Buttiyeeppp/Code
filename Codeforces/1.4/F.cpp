#include<bits/stdc++.h>
using namespace std;
#define ls (id<<1)
#define rs (id<<1|1)
const int N=5e5+10;
const int M=1e6+10;
int n,q,a[N];
struct SegmentTree {
    int cnt,mn,lazy;
    SegmentTree() {cnt=mn=lazy=0;}  
    SegmentTree operator+(const SegmentTree &q)const {
        SegmentTree p;
        p.lazy=0, p.mn=min(mn,q.mn);
        if(mn==q.mn) p.cnt=cnt+q.cnt;
        else if(mn<q.mn) p.cnt=cnt;
        else p.cnt=q.cnt;
        return p;
    }
}t[M<<2];
void pushdown(int id) {
    if(!t[id].lazy) return;
    int val=t[id].lazy; t[id].lazy=0;
    t[ls].lazy+=val, t[rs].lazy+=val;
    t[ls].mn+=val, t[rs].mn+=val;
}
void modify1(int id,int l,int r,int x,int val) {
    if(x>r||x<l) return;
    if(l==r) { t[id].cnt+=val; return; }
    pushdown(id);
    int mid=(l+r)>>1;
    modify1(ls,l,mid,x,val), modify1(rs,mid+1,r,x,val);
    t[id]=t[ls]+t[rs];
}
void modify(int id,int l,int r,int x,int y,int val) {
    if(x>r||y<l) return;
    if(x<=l&&y>=r) {
        t[id].mn+=val;
        t[id].lazy+=val;
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    modify(ls,l,mid,x,y,val), modify(rs,mid+1,r,x,y,val);
    t[id]=t[ls]+t[rs];
}
void xxx(int i,int j,int val) {
    if(a[i]!=a[j])
        modify(1,0,M,min(a[i],a[j]),max(a[i],a[j])-1,val);
}
int query(int id,int l,int r,int x,int y) {
    if(x>r||y<l) return 0;
    if(x<=l&&y>=r) return (t[id].mn==1?t[id].cnt:0);
    pushdown(id);
    int mid=(l+r)>>1;
    return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}
int main() {
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    a[0]=M, a[n+1]=0;
    for(int i=0;i<=n;i++) {
        xxx(i,i+1,1);
        if(i!=0) modify1(1,0,M,a[i],1);
    }
    int i,v;
    while(q--) { 
        scanf("%d%d",&i,&v);
        xxx(i,i+1,-1), xxx(i,i-1,-1), modify1(1,0,M,a[i],-1);
        a[i]=v;
        xxx(i,i+1,1), xxx(i,i-1,1), modify1(1,0,M,a[i],1); printf("%d\n",query(1,0,M,1,M-1));
    }
    return 0;
}