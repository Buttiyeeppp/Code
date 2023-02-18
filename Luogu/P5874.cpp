#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls (id<<1)
#define rs (id<<1|1)
const ll Mod=1e9+7;
const int N=5e5+10;
struct SegmentTree {
    double lnmx,lnlazy;
    ll mx,lazy;
    SegmentTree operator+(const SegmentTree q)const {
        return SegmentTree{max(lnmx,q.lnmx),0,(lnmx>q.lnmx? mx:q.mx),1};
    }

}d[N<<2];
int n,m;
double Blc;
ll x[N],y[N],Bc=1;
void build(int id,int l,int r) {
    if(l==r) {
        Blc+=log2(x[l]), Bc=Bc*x[l]%Mod;
        d[id]=SegmentTree{Blc+log2(y[l]),0,Bc*y[l]%Mod,1};
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid), build(rs,mid+1,r);
    d[id]=d[ls]+d[rs];
    return;
}
ll Mul(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return sum;
}
void pushdown(int id) {
    if(d[id].lazy==1) return;
    double Ln=d[id].lnlazy; ll v=d[id].lazy;
    d[id].lnlazy=0, d[id].lazy=1;
    d[ls].lnmx+=Ln, d[ls].lnlazy+=Ln, d[ls].mx=d[ls].mx*v%Mod, d[ls].lazy=d[ls].lazy*v%Mod;
    d[rs].lnmx+=Ln, d[rs].lnlazy+=Ln, d[rs].mx=d[rs].mx*v%Mod, d[rs].lazy=d[rs].lazy*v%Mod;
    return;
}
void Modify(int id,int l,int r,int x,int y,ll val,int op) {
    if(x<=l&&y>=r) {
        double Ln; ll v;
        if(!op) Ln=-log2(val), v=Mul(val,Mod-2);
        else Ln=log2(val), v=val;
        d[id].lnmx+=Ln, d[id].lnlazy+=Ln;
        d[id].mx=d[id].mx*v%Mod, d[id].lazy=d[id].lazy*v%Mod;
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls,l,mid,x,y,val,op);
    if(y>mid) Modify(rs,mid+1,r,x,y,val,op);
    d[id]=d[ls]+d[rs];
    return; 
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&x[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&y[i]);
    build(1,1,n);
    printf("%lld\n",d[1].mx);
    scanf("%d",&m);
    for(int i=1,op,pos;i<=m;i++) {
        ll val;
        scanf("%d%d%lld",&op,&pos,&val), pos++;
        if(op==1) {
            Modify(1,1,n,pos,n,x[pos],0), x[pos]=val;
            Modify(1,1,n,pos,n,x[pos],1);
        }else {
            Modify(1,1,n,pos,pos,y[pos],0), y[pos]=val;
            Modify(1,1,n,pos,pos,y[pos],1);
        }
        printf("%lld\n",d[1].mx);
    }
    return 0;
}