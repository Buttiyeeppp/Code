#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,h,a[N],b[N],mn[N<<1],lz[N<<1],p[N];
void Build(int id,int l,int r) {
	if(l==r) return mn[id]=-l, void();
	int mid=(l+r)>>1;
	Build(ls,l,mid), Build(rs,mid+1,r);
	mn[id]=min(mn[ls],mn[rs]);
}
void pushdown(int id) {
	if(!lz[id]) return;
	int v=lz[id]; lz[id]=0;
	mn[ls]+=v, lz[ls]+=v;
	mn[rs]+=v, lz[rs]+=v;
}
void Modify(int id,int l,int r,int x,int y,int v) {
	if(x<=l&&y>=r) return mn[id]+=v, lz[id]+=v, void();
	pushdown(id);
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x,y,v);
	if(y>mid) Modify(rs,mid+1,r,x,y,v);
	mn[id]=min(mn[ls],mn[rs]);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>h;
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++) cin>>a[i], p[i]=lower_bound(b+1,b+m+1,h-a[i])-b;
	Build(1,1,m);
	for(int i=1;i<=m;i++) if(p[i]<=m) Modify(1,1,m,p[i],m,1);
	int ans=(mn[1]>=0);
	for(int i=m+1;i<=n;i++) {
		if(p[i]<=m) Modify(1,1,m,p[i],m,1);
		if(p[i-m]<=m) Modify(1,1,m,p[i-m],m,-1);
		ans+=(mn[1]>=0);
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}

