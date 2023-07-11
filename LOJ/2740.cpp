#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define ls (id<<1)
#define rs (id<<1|1)
struct node {
	int x,y;
}a[N],b[N];
vector<int> Pos[N];
int n,mn[N<<2],lazy[N<<2],R[N],pos[N];
void build(int id,int l,int r) {
	if(l==r) { mn[id]=R[l]-l; return; }
	int mid=(l+r)>>1;
	build(ls,l,mid), build(rs,mid+1,r);
	mn[id]=min(mn[ls],mn[rs]);
}
void pushdown(int id) {
	if(!lazy[id]) return;
	int val=lazy[id]; lazy[id]=0;
	mn[ls]+=val, lazy[ls]+=val;
	mn[rs]+=val, lazy[rs]+=val;
}
void modify(int id,int l,int r,int x,int y,int val) {
	if(x>r||y<l||x>y) return;
	if(x<=l&&y>=r) {
		mn[id]+=val, lazy[id]+=val; return;
	}
	pushdown(id);
	int mid=(l+r)>>1;
	modify(ls,l,mid,x,y,val), modify(rs,mid+1,r,x,y,val);
	mn[id]=min(mn[ls],mn[rs]);
}
int main() {
	scanf("%d",&n);
	for(int i=n;i>=1;i--) scanf("%d%d",&b[i].x,&b[i].y);
	for(int i=n;i>=1;i--) scanf("%d%d",&a[i].x,&a[i].y);
	for(int i=1;i<=n;i++) {
		R[i]=R[i-1];
		while(R[i]<n&&b[R[i]+1].y<=a[i].y) R[i]++, pos[R[i]]=i;
	}
	build(1,1,n);
	int ans=n;
	for(int i=1;i<=n;i++) {
		for(int j=R[i-1]+1;j<=R[i];j++) Pos[b[j].x].push_back(j);
		if(Pos[a[i].x].empty()) continue;
		int p=pos[Pos[a[i].x].back()];
		modify(1,1,n,p,i-1,-1);
		if(mn[1]>=0) ans--, Pos[a[i].x].pop_back();
		else modify(1,1,n,p,i-1,1);
	}
	printf("%d",ans);
	return 0;
}
