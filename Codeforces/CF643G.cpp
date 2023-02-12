#include<bits/stdc++.h>
using namespace std;
#define ls (id<<1)
#define rs (id<<1|1)
const int N=2e5+10;
int n,p,m,a[N];
struct SegmentTree {
    int z[6],cnt[6],tot,tag;
    SegmentTree operator+(const SegmentTree &q)const {
        SegmentTree res;
        res.tot=q.tot;
        for(int i=1;i<=res.tot;i++) res.z[i]=q.z[i], res.cnt[i]=q.cnt[i];
        for(int i=1;i<=tot;i++) {
            int ok=0;
            for(int j=1;j<=res.tot;j++)
                if(res.z[j]==z[i]) {res.cnt[j]+=cnt[i], ok=1; break;}
            if(ok) continue;
            if(res.tot<p) 
                {res.tot++, res.z[res.tot]=z[i], res.cnt[res.tot]=cnt[i]; continue;}
            int k=1;
            for(int j=2;j<=res.tot;j++) {
                if(res.cnt[j]<res.cnt[k]) k=j;
            }
            if(cnt[i]<res.cnt[k])
                for(int j=1;j<=res.tot;j++) res.cnt[j]-=cnt[i];
            else {
                int sum=res.cnt[k];
                res.cnt[k]=cnt[i], res.z[k]=z[i];
                for(int j=1;j<=res.tot;j++) res.cnt[j]-=sum;
            }
        }
        return res;
    }
}t[N<<2];
void build(int id,int l,int r) {
    if(l==r) {
        t[id].tag=0, t[id].tot=1;
        t[id].z[1]=a[l], t[id].cnt[1]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid), build(rs,mid+1,r);
    t[id]=t[ls]+t[rs];
}
void xxx(int id,int l,int r,int val) {
    t[id].tot=1, t[id].tag=val;
    t[id].z[1]=val, t[id].cnt[1]=r-l+1;
}
void pushdown(int id,int l,int r) {
    if(!t[id].tag) return;
    int val=t[id].tag; t[id].tag=0;
    int mid=(l+r)>>1;
    xxx(ls,l,mid,val), xxx(rs,mid+1,r,val);
}
void Modify(int id,int l,int r,int x,int y,int val) {
    if(x>r||y<l) return;
    if(x<=l&&y>=r) {
        xxx(id,l,r,val);
        return;
    }
    pushdown(id,l,r);
    int mid=(l+r)>>1;
    Modify(ls,l,mid,x,y,val), Modify(rs,mid+1,r,x,y,val);
    t[id]=t[ls]+t[rs];
}
SegmentTree Query(int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return t[id];
	int mid=(l+r)>>1;
	pushdown(id,l,r);
	if(y<=mid) return Query(ls,l,mid,x,y);
	if(x>=mid+1) return Query(rs,mid+1,r,x,y);
	return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
}
int main() {
    scanf("%d%d%d",&n,&m,&p); p=100/p;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1,op,l,r,id;i<=m;i++) {
        scanf("%d%d%d",&op,&l,&r);
        if(op==1) {
            scanf("%d",&id);
            Modify(1,1,n,l,r,id);
        }
        else {
            SegmentTree Ans=Query(1,1,n,l,r);
            printf("%d ",Ans.tot);
            for(int i=1;i<=Ans.tot;i++) printf("%d ",Ans.z[i]); puts("");
        }
    }
    return 0;
}
