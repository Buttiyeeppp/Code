#include<bits/stdc++.h>
using namespace std;
#define ls (id<<1)
#define rs (id<<1|1)
const int N=2e5+10;
int n,m;
struct SegmentTree {
    int mx;
    priority_queue<int> q;
}t[N<<2];
void build(int id,int l,int r) {
    t[id].mx=-1, t[id].q.push(-1);
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls,l,mid), build(rs,mid+1,r);
}
void pushup(int id) {
    t[id].mx=max({t[ls].mx,t[rs].mx,t[id].q.top()});
}
void add(int id,int l,int r,int x,int y,int val) {
    if(x>r||y<l) return;
    if(x<=l&&y>=r) {
        t[id].mx=max(t[id].mx,val);
        t[id].q.push(val);
        return;
    }
    int mid=(l+r)>>1;
    add(ls,l,mid,x,y,val), add(rs,mid+1,r,x,y,val);
    pushup(id);
}
void pushdown(int id,int l,int r,int x,int y,int val) {
    if(x<=l&&y>=r) return;
    int mid=(l+r)>>1;
    if(x>mid) t[ls].mx=max(t[ls].mx,val), t[ls].q.push(val), pushdown(rs,mid+1,r,x,y,val);
    else if(y<=mid) t[rs].mx=max(t[rs].mx,val), t[rs].q.push(val), pushdown(ls,l,mid,x,y,val);
    else pushdown(ls,l,mid,x,y,val), pushdown(rs,mid+1,r,x,y,val);
    pushup(id);
}
void del(int id,int l,int r,int x,int y,int val) {
    if(x>r||y<l) return;
    if(x<=l&&y>=r&&t[id].mx<val) return;
    if(t[id].q.top()==val) {
        t[id].q.pop();
        pushdown(id,l,r,x,y,val);
        if(l==r) t[id].mx=t[id].q.top();
        else pushup(id);
        return;
    }
    int mid=(l+r)>>1;
    del(ls,l,mid,x,y,val), del(rs,mid+1,r,x,y,val);
    pushup(id);
}
int query(int id,int l,int r,int x,int y) {
    if(x>r||y<l) return -1;
    if(x<=l&&y>=r) return t[id].mx;
    int mid=(l+r)>>1;;
    return max({query(ls,l,mid,x,y),query(rs,mid+1,r,x,y),t[id].q.top()});
}
int main() {
    scanf("%d%d",&n,&m);
    build(1,1,n);
    int op,l,r,k;
    while(m--) {
        scanf("%d%d%d",&op,&l,&r);
        if(op==1) {
            scanf("%d",&k);
            add(1,1,n,l,r,k);
        }
        else if(op==2) {
            k=query(1,1,n,l,r);
            if(k!=-1) del(1,1,n,l,r,k);
        }
        else {
            printf("%d\n",query(1,1,n,l,r));
        }
    }
    return 0;
}